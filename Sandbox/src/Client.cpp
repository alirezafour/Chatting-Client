#include "Client.h"

#include <boost/bind.hpp>


using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::redirect_error;
using boost::asio::use_awaitable;

client_chat::client_chat() 
	: m_io_context{}
	, m_Resolver{ m_io_context }
	, m_Socket{ m_io_context }
{
}

client_chat::~client_chat()
{
	stop();
}

void client_chat::connect(const std::string& ip, const std::string& port)
{
	tcp::resolver::results_type endpoints = m_Resolver.resolve("127.0.0.1", "6000");
	boost::asio::connect(m_Socket, endpoints);
}

awaitable<void> client_chat::reader()
{
	try
	{
		for (std::string read_msg;;)
		{
			std::size_t n = co_await boost::asio::async_read_until(m_Socket,
				boost::asio::dynamic_buffer(read_msg, 1024), "\n", use_awaitable);

			OnMessage(read_msg);
			std::cout << "message size [" << n << "]: " << read_msg << "\n";
			read_msg.erase(0, n);
		}
	}
	catch (std::exception&)
	{
		stop();
	}
}


void client_chat::writer(std::string message)
{
	if (m_Socket.is_open())
	{
		message += "\n";
		boost::asio::async_write(m_Socket, boost::asio::buffer(message), [this](std::error_code errorCode, size_t length)
			{
				if (!errorCode)
				{
					std::cout << "Message sent.\n";
				}
				else
				{
					std::cout << "Error : " << errorCode.message() << "\n";
				}
			});
	}
}

void client_chat::OnMessage(std::string message)
{
	if (m_CallbackMessageFunction) 
	{
		m_CallbackMessageFunction(message);
	}
	else
		std::cout << "Callback function is not valid \n";
}

void client_chat::SetCallbackMessageFuntion(std::function<void(std::string)> function)
{
	m_CallbackMessageFunction = function;
}

void client_chat::run()
{
	co_spawn(m_io_context,
		[this] { return reader(); },
		detached);
	m_ThreadContext = std::thread([this]() { m_io_context.run(); });
}

void client_chat::stop()
{
	m_Socket.close();
}
