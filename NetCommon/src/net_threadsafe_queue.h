#pragma once
#include "net_common.h"

namespace four::net
{
	template<typename T>
	class ThreadSafeQueue
	{
	public:
		ThreadSafeQueue() = default;
		ThreadSafeQueue(const ThreadSafeQueue<T>&) = delete;
		virtual ~ThreadSafeQueue() { clear(); }

		const T& front()
		{
			std::scoped_lock lock(mutexDeqQueue);
			return deqQueue.front();
		}

		const T& back()
		{
			std::scoped_lock lock(mutexDeqQueue);
			return deqQueue.back();
		}

		void push_back(const T& item)
		{
			std::scoped_lock lock(mutexDeqQueue);
			deqQueue.emplace_back(std::move(item));

			std::unique_lock<std::mutex> ul(mutexBlocking);
			cvBlocking.notify_one();
		}

		void push_front(const T& item)
		{
			std::scoped_lock lock(mutexDeqQueue);
			deqQueue.emplace_front(std::move(item));

			std::unique_lock<std::mutex> ul(mutexBlocking);
			cvBlocking.notify_one();
		}

		bool empty()
		{
			std::scoped_lock lock(mutexDeqQueue);
			return deqQueue.empty();
		}

		size_t count() const
		{
			std::scoped_lock lock(mutexDeqQueue);
			return deqQueue.size();
		}

		void clear()
		{
			std::scoped_lock lock(mutexDeqQueue);
			deqQueue.clear();
		}

		T pop_front()
		{
			std::scoped_lock lock(mutexDeqQueue);
			auto temp = std::move(deqQueue.front());
			deqQueue.pop_front();
			return temp;
		}

		T pop_back()
		{
			std::scoped_lock lock(mutexDeqQueue);
			auto temp = std::move(deqQueue.back());
			deqQueue.pop_back();
			return temp;
		}

		void wait()
		{
			while (empty())
			{
				std::unique_lock<std::mutex> ul(mutexBlocking);
				cvBlocking.wait(ul);
			}
		}


	protected:
		std::deque<T> deqQueue;
		std::mutex mutexDeqQueue;

		std::condition_variable cvBlocking;
		std::mutex mutexBlocking;
	};
	
}