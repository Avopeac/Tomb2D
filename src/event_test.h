#pragma once

#include <string>

#include <iostream>

#include "event.h"

namespace util {

	struct EventTestData
	{
		float a;
		uint32_t b;
		std::string c;
	};

	class EventTestSubscriber : public EventSubscriber<EventTestData>
	{
		std::string name_;

	public:

		EventTestSubscriber(const std::string &name) : name_(name) {}

		virtual ~EventTestSubscriber() = default;

		virtual void Update(const EventTestData &data) override
		{
			std::cout << "Published to " << name_ << ": " << data.a << " " << data.b << " " << data.c << "." << std::endl;
		}
	};

	class EventTest
	{

	public:

		EventTest() = default;

		~EventTest() = default;

		void Run()
		{
			auto sub_0 = std::make_shared<EventTestSubscriber>("Olaf");
			auto sub_1 = std::make_shared<EventTestSubscriber>("Jens");
			auto sub_2 = std::make_shared<EventTestSubscriber>("Urban");
			auto sub_3 = std::make_shared<EventTestSubscriber>("Ronja");

			EventTestData data_0;
			data_0.a = 2.0f;
			data_0.b = 5;
			data_0.c = "Urgent Message";

			Event<EventTestData> e;

			e.Subscribe(sub_0);
			e.Subscribe(sub_1);

			e.Publish(data_0);

			e.Subscribe(sub_2);
			e.Subscribe(sub_3);

			data_0.a = 1.0;
			data_0.b = 1000;
			data_0.c = "Unimportant Message";

			e.Publish(data_0);
		}
	};
}
