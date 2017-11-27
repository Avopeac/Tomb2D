#pragma once

#include <vector>
#include <memory>

namespace core {

	template <typename EventData> class EventSubscriber
	{

	public:

		EventSubscriber() = default;

		virtual ~EventSubscriber() = default;

		virtual void Update(const EventData &data) = 0;

	};

	template <typename EventData> class Event
	{

		std::vector<std::weak_ptr<EventSubscriber<EventData>>> subscribers_;

	public:

		Event() = default;

		~Event() = default;

		void Publish(const EventData &data)
		{
			
			for (auto it = subscribers_.begin(); it != subscribers_.end(); ++it)
			{
				if (auto shared = it->lock())
				{
					shared->Update(data);
				}
				else
				{
					it = subscribers_.erase(it);
				}
			}
		}

		void Subscribe(const std::shared_ptr<EventSubscriber<EventData>> &subscriber)
		{
			subscribers_.push_back(subscriber);
		}

	};
}
