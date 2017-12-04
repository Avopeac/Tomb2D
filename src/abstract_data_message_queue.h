#pragma once

#include <queue>

namespace core {

	template <typename T> class AbstractDataMessageQueue
	{
		std::queue<T> message_data_;

	public:

		AbstractDataMessageQueue() = default;

		virtual ~AbstractDataMessageQueue() = default;

		bool TryPop(T &message_data)
		{
			if (!message_data_.empty())
			{
				message_data = std::move(message_data_.front());
				message_data_.pop();

				return true;
			}

			return false;
		}

		void Push(const T &message_data)
		{
			message_data_.push(message_data);
		}
	};
}