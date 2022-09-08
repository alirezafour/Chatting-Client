#pragma once

#include "net_common.h"
#include "net_threadsafe_queue.h"
#include "net_message.h"
#include "net_connection.h"

namespace four::net
{
	template<typename T>
	class ServerInterface
	{
	public:
		ServerInterface(uint16_t port)
			: m_AsioAcceptor(m_AsioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
		{

		}

		virtual ~ServerInterface()
		{
			Stop();
		}

		bool Start()
		{
			try
			{
				WaitForClientConnection();

				m_ThreadContext = std::thread([this]() {m_AsioContext.run(); });
			}
			catch (const std::exception& e)
			{
				std::cerr << "[Server] Exception: " << e.what() << "\n";
				return false;
			}

			std::cout << "[Server] Started!\n";
			return true;
		}

		void Stop()
		{
			m_AsioContext.stop();
			if (m_ThreadContext.joinable())
				m_ThreadContext.join();

			std::cout << "[Server] Stopped!\n";
		}

		// #ASYNC
		void WaitForClientConnection()
		{
			m_AsioAcceptor.async_accept(
				[this](std::error_code errorCode, asio::ip::tcp::socket socket)
				{
					if (!errorCode)
					{
						std::cout << "[Server] New Connection: " << socket.remote_endpoint() << "\n";

						std::shared_ptr<Connection<T>> newConnection = std::make_shared<Connection<T>>(Connection<T>::owner::server,
							m_AsioContext, std::move(socket), m_QueueMessagesIn);

						if (OnClientConnect(newConnection))
						{
							m_deqConnections.push_back(std::move(newConnection));

							m_deqConnections.back()->ConnectToClient(m_IDCounter++);

							std::cout << "[" << m_deqConnections.back()->GetID() << "] Connection Approved.\n";
						}
						else
						{
							std::cout << "[ === ] Connection Denied\n";
						}
					}
					else
					{
						std::cout << "[Server] New Connection Error: " << errorCode.message() << "\n";
					}

					WaitForClientConnection();
				});
		}

		// message to specific client
		void MessageClient(std::shared_ptr<Connection<T>> client, const message<T>& msg)
		{
			if (client && client->IsConnected())
			{
				client->SendMessage(msg);
			}
			else
			{
				OnClientDisconected(client);
				client->reset();
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end()); // expensive call
			}
		}

		// broadcast message to all clients
		void MessageAllClients(const message<T>& msg, std::shared_ptr<Connection<T>> ignoreClient = nullptr)
		{
			bool bInvalidClientExists = false;
			for (auto& client : m_deqConnections)
			{
				if (client && client->IsConnected())
				{
					if(client != ignoreClient)
						client->SendMessage(msg);
				}
				else
				{
					OnClientDisconected(client);
					client.reset();
					bInvalidClientExists = true;
				}
			}
			if (bInvalidClientExists)
			{
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end());
			}
		}

		void Update(size_t maxMessages = -1, bool bWait = false) // set unsigned int to maximum number possible
		{
			if (bWait)
				m_QueueMessagesIn.wait();

			size_t messageCount = 0;
			while (messageCount < maxMessages && !m_QueueMessagesIn.empty())
			{
				auto msg = m_QueueMessagesIn.pop_front();
				
				OnMessage(msg.remote, msg.msg);

				messageCount++;
			}
		}

	protected:
		virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client)
		{
			return false;
		}

		virtual void OnClientDisconected(std::shared_ptr<Connection<T>> client)
		{

		}

		virtual void OnMessage(std::shared_ptr<Connection<T>> client, message<T>& msg)
		{

		}

	protected:
		ThreadSafeQueue<owned_message<T>> m_QueueMessagesIn;

		std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

		asio::io_context m_AsioContext;
		std::thread m_ThreadContext;

		asio::ip::tcp::acceptor m_AsioAcceptor;

		// Clients ID
		uint32_t m_IDCounter = 10000;
	};
}