#pragma once
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <functional>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/connect.hpp>


class client_chat
{
public:
	client_chat();
	~client_chat();

	inline boost::asio::ip::tcp::socket& getSocket() { return m_Socket; }
	void connect(const std::string& ip, const std::string& port);
	void writer(std::string message);
	void SetCallbackMessageFuntion(std::function<void(std::string)> function);
	void run();

protected:
	void OnMessage(std::string message);
	boost::asio::awaitable<void> reader();
private:
	void stop();

	boost::asio::io_context m_io_context;
	std::thread m_ThreadContext;
	boost::asio::ip::tcp::resolver m_Resolver;
	boost::asio::ip::tcp::socket m_Socket;
	std::function<void(std::string)> m_CallbackMessageFunction;
};