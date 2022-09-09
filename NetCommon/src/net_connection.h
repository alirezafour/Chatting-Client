#pragma once

#include "net_common.h"
#include "net_threadsafe_queue.h"
#include "net_message.h"

namespace four::net
{
	template<typename T>
	class ServerInterface;

	template<typename T>
	class Connection : public std::enable_shared_from_this<Connection<T>>
	{
	public:
		enum class owner
		{
			server,
			client
		};

		Connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, ThreadSafeQueue<owned_message<T>>& queueMessagesIn)
			: m_AsioContext(asioContext), m_Socket(std::move(socket)), m_QueueMessagesIn(queueMessagesIn)
		{
			m_OwnerType = parent;

			if (m_OwnerType == owner::server)
			{
				m_HandshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

				// pre calculate the result
				m_HandshakeCheck = scramble(m_HandshakeOut);
			}
			else
			{
				m_HandshakeIn = 0;
				m_HandshakeOut = 0;
			}
		}

		virtual ~Connection()
		{}

		void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints)
		{
			if (m_OwnerType == owner::client)
			{
				asio::async_connect(m_Socket, endpoints,
					[this](std::error_code errorCode, asio::ip::tcp::endpoint endpoint)
					{
						if (!errorCode)
						{
							//ReadHeader();
							ReadValidation();
						}
					});
			}
		}

		void Disconnect()
		{
			if (IsConnected())
				asio::post(m_AsioContext, [this](){ m_Socket.close(); });
		}

		bool IsConnected() const 
		{
			return m_Socket.is_open();
		}

		void SendMessage(const message<T>& msg)
		{
			asio::post(m_AsioContext,
				[this, msg]()
				{
					bool bWriteMessage = !m_QueueMessagesOut.empty();
					m_QueueMessagesOut.push_back(msg);
					if (!bWriteMessage)
					{
						WriteHeader();
					}
				});
		}

		uint32_t GetID() const
		{
			return m_ID;
		}

		void ConnectToClient(four::net::ServerInterface<T>* server, uint32_t uId = 0)
		{
			if (m_OwnerType == owner::server)
			{
				if (IsConnected())
				{
					m_ID = uId;
					//ReadHeader();

					WriteValidation();

					ReadValidation(server);
				}
			}
		}


	private:
		// #ASYNC
		void ReadHeader()
		{
			asio::async_read(m_Socket, asio::buffer(&m_MsgTemporaryIn.header, sizeof(message_header<T>)),
				[this](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						if (m_MsgTemporaryIn.header.size > 0)
						{
							m_MsgTemporaryIn.body.resize(m_MsgTemporaryIn.header.size);
							ReadBody();
						}
						else
						{
							AddToIncommingMessageQueue();
						}
					}
					else
					{
						std::cout << "[" << m_ID << "] Read header failed.\n[" << errorCode.message() << "]\n";
						m_Socket.close();
					}
				});
		}

		// #ASYNC
		void ReadBody()
		{
			asio::async_read(m_Socket, asio::buffer(m_MsgTemporaryIn.body.data(), m_MsgTemporaryIn.body.size()),
				[this](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						AddToIncommingMessageQueue();
					}
					else
					{
						std::cout << "[" << m_ID << "] Read body failed.\n[" << errorCode.message() << "]\n";
						m_Socket.close();
					}
				});
		}

		// #ASYNC
		void WriteHeader()
		{
			asio::async_write(m_Socket, asio::buffer(&m_QueueMessagesOut.front().header, sizeof(message_header<T>)),
				[this](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						if (m_QueueMessagesOut.front().body.size() > 0)
						{
							WriteBody();
						}
						else
						{
							m_QueueMessagesOut.pop_front();

							if (!m_QueueMessagesOut.empty())
							{
								WriteHeader(); // if message not empty queue up another write
							}
						}
					}
					else
					{
						std::cout << "[" << m_ID << "] Write header failed.\n[" << errorCode.message() << "]\n";
						m_Socket.close();
					}
				});
		}

		// #ASYNC
		void WriteBody()
		{
			asio::async_write(m_Socket, asio::buffer(m_QueueMessagesOut.front().body.data(), m_QueueMessagesOut.front().body.size()),
				[this](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						m_QueueMessagesOut.pop_front();

						if (!m_QueueMessagesOut.empty())
						{
							WriteHeader();
						}
					}
					else
					{
						std::cout << "[" << m_ID << "] Write body failed.\n[" << errorCode.message() << "]\n";
						m_Socket.close();
					}

				});
		}

		void AddToIncommingMessageQueue()
		{
			if (m_OwnerType == owner::server)
				m_QueueMessagesIn.push_back({ this->shared_from_this(), m_MsgTemporaryIn });
			else
				m_QueueMessagesIn.push_back({ nullptr, m_MsgTemporaryIn });

			ReadHeader(); // add another task after finishing to asio read and not finish his task
		}

		// #Encrypt data kapa
		uint64_t scramble(uint64_t input)
		{
			uint64_t out = input ^ 0xEADFECCEEADFEC;
			out = (out & 0xF0F0F0F0F0F0F0F0) >> 4 | (out & 0x0F0F0F0F0F0F0F0F) << 4;
			return out ^ 0xEADFE3C1AADFE0;
		}

		// #ASYNC
		void WriteValidation()
		{
			asio::async_write(m_Socket, asio::buffer(&m_HandshakeOut, sizeof(uint64_t)),
				[this](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						if (m_OwnerType == owner::client)
						{
							ReadHeader();
						}
					}
					else
					{
						std::cout << "[" << errorCode.message() << "]\n";
						m_Socket.close();
					}
				});
		}

		void ReadValidation(four::net::ServerInterface<T>* server = nullptr)
		{
			asio::async_read(m_Socket, asio::buffer(&m_HandshakeIn, sizeof(uint64_t)),
				[this, server](std::error_code errorCode, std::size_t length)
				{
					if (!errorCode)
					{
						if (m_OwnerType == owner::server)
						{
							if (m_HandshakeIn == m_HandshakeCheck) // validate handshake
							{
								std::cout << "Client Validated.\n";
								server->OnClientValidated(this->shared_from_this());

								ReadHeader();
							}
							else
							{
								std::cout << "Client failed to validate.\n";
								m_Socket.close();
							}
						}
						else
						{
							m_HandshakeOut = scramble(m_HandshakeIn);

							WriteValidation();
						}
					}
					else
					{
						std::cout << "Client Disconnected (ReadValidation)\n" << errorCode.message() << "\n";
						m_Socket.close();
					}
				});
		}

	protected:
		// each connection have its own socket
		asio::ip::tcp::socket m_Socket;

		// provided by the client
		asio::io_context& m_AsioContext;

		// this queue holds all messages to be send out
		ThreadSafeQueue<message<T>> m_QueueMessagesOut;

		// holds all messages that have been received from remote
		ThreadSafeQueue<owned_message<T>>& m_QueueMessagesIn;

		// Incoming messages are constructed asynchronously, so we will
		// store the part assembled message here, until it is ready
		message<T> m_MsgTemporaryIn;

		owner m_OwnerType = owner::server;

		uint32_t m_ID = 0;

		// Handshakes validation
		uint64_t m_HandshakeOut = 0;
		uint64_t m_HandshakeIn = 0;
		uint64_t m_HandshakeCheck = 0;
	};
}
