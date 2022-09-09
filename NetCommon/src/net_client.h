#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_threadsafe_queue.h"
#include "net_connection.h"

namespace four::net
{
	template<typename T>
	class ClientInterface
	{
	public:
		ClientInterface()
			: m_Socket(m_Context)
		{
			// init socket and io context
		}
		virtual ~ClientInterface()
		{
			// if client destroyed try to disconnect
			Disconnect();
		}

		bool Connect(const std::string& host, const uint16_t port)
		{
			try
			{
				// resolve hostname/ip-address
				asio::ip::tcp::resolver resolver(m_Context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				// create connection
				m_Connection = std::make_unique<Connection<T>>(
					Connection<T>::owner::client,
					m_Context,
					asio::ip::tcp::socket(m_Context), m_QueueMessagesIn);

				m_Connection->ConnectToServer(endpoints);

				m_ThreadContext = std::thread([this]() { m_Context.run(); });


			}
			catch (std::exception& e)
			{
				std::cerr << "Client Exception: " << e.what() << "\n";
				return false;
			}
			
			return true;
		}

		void Disconnect()
		{
			if (IsConnected())
			{
				m_Connection->Disconnect();
			}

			m_Context.stop();
			if (m_ThreadContext.joinable())
				m_ThreadContext.join();

			m_Connection.release();
		}

		void Send(const message<T>& msg)
		{
			if (IsConnected())
				m_Connection->SendMessage(msg);
		}

		bool IsConnected() const 
		{
			if (m_Connection)
				return m_Connection->IsConnected();

			return false;
		}

		ThreadSafeQueue<owned_message<T>>& Incomming()
		{
			return m_QueueMessagesIn;
		}

	protected:
		asio::io_context m_Context;

		std::thread m_ThreadContext;

		asio::ip::tcp::socket m_Socket;

		std::unique_ptr<Connection<T>> m_Connection;
	private:
		ThreadSafeQueue<owned_message<T>> m_QueueMessagesIn;
	};
}