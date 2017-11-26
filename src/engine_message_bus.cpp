#include "engine_message_bus.h"

#include "logger.h"

using namespace engine;

EngineMessageBus::EngineMessageBus()
{
}

EngineMessageBus::~EngineMessageBus()
{
}

void EngineMessageBus::RegisterSystem(const std::string &system_name, const std::shared_ptr<AbstractEngineSystem>& system)
{
	registry_mutex_.lock();

	if (systems_.find(system_name) != systems_.end())
	{
		debug::Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_APPLICATION, "Trying to register a new system with an existing system name.");
	}
	else
	{
		systems_.insert({ system_name, system });
	}

	registry_mutex_.unlock();
}

void EngineMessageBus::RegisterMessage(const std::string & message, size_t message_size)
{

	registry_mutex_.lock();

	if (message_types_.find(message) != message_types_.end())
	{
		debug::Log(SDL_LOG_PRIORITY_ERROR, SDL_LOG_CATEGORY_APPLICATION, "Trying to register a new message type with an existing message name.");
	}
	else
	{
		message_types_.insert({ message, message_size });
	}

	registry_mutex_.unlock();
}

bool EngineMessageBus::PollMessages(EngineMessage * message)
{
	queue_mutex_.lock();
	if (!messages_.empty())
	{
		message = messages_.front();
		messages_.pop();
		return true;
	}
	queue_mutex_.unlock();
	return false;
}

void EngineMessageBus::PushMessage(EngineMessage * const message)
{
	for (auto it : systems_)
	{
		if (auto shared = it.second.lock())
		{
			shared->HandleMessage(message);
		}
	}
}

void EngineMessageBus::PostMessage(EngineMessage * const message)
{
	queue_mutex_.lock();
	messages_.push(message);
	queue_mutex_.unlock();
}

void EngineMessageBus::PostImmediateMessage(EngineMessage * const message)
{
	for (auto it : systems_)
	{
		if (auto shared = it.second.lock())
		{
			shared->HandleMessage(message);
		}
	}
}
