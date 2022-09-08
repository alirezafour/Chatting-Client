#pragma once
#include "four_net.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage
};

class Client : public four::net::ClientInterface<CustomMsgTypes>
{
public:
	void PingServer();
	void MessageAll(const std::string_view& msgToSend);
};