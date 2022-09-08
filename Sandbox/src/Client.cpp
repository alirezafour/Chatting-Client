#include "Client.h"

void Client::PingServer()
{
	four::net::message<CustomMsgTypes> msg;
	msg.header.id = CustomMsgTypes::ServerPing;

	// Caution with this...
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

	msg << timeNow;
	SendMessage(msg);
}

void Client::MessageAll(const std::string_view& msgToSend)
{
	four::net::message<CustomMsgTypes> msg;
	msg.header.id = CustomMsgTypes::MessageAll;
	
	for (auto& each : msgToSend)
	{
		msg.body.push_back(each);
	}
	
	SendMessage(msg);
}

