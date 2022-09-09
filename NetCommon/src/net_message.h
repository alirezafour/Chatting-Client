#pragma once
#include "net_common.h"

namespace four::net
{
	template<typename T>
	struct message_header
	{
		T id{};
		uint32_t size = 0;
	};

	template<typename T>
	struct message
	{
		message_header<T> header{};
		std::vector<uint8_t> body;

		// return size of message in bytes
		size_t size() const
		{
			return sizeof(message_header<T>) + body.size();
		}

		// std::cout compatibility
		friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
		{
			os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size;
			return os;
		}

		template<typename DataType>
		friend message<T>& operator << (message<T>& msg, const DataType& data)
		{
			// check if data copyable
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector.");

			// cache
			size_t i = msg.body.size();

			// resize the vector to size of data
			msg.body.resize(msg.body.size() + sizeof(DataType)); // it resize to bigger so it has some over head

			// physically copy data to vector
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

			// recalculate the message size
			msg.header.size = static_cast<uint32_t>(msg.size());

			return msg;
		}

		template<typename DataType>
		friend message<T>& operator >> (message<T>& msg, DataType& data)
		{
			//Check data copyable
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector.");

			// cache toward the end of the vector
			size_t i = msg.body.size() - sizeof(DataType);

			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

			msg.body.resize(i); // because it resize to smaller size it doesn't allocate new space so no over head

			return msg;
		}
	};

	// forward declaration
	template<typename T>
	class Connection;

	template<typename T>
	struct owned_message
	{
		std::shared_ptr<Connection<T>> remote = nullptr;
		message<T> msg;

		friend std::ostream& operator << (std::ostream& os, const owned_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}