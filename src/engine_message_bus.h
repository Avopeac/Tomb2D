#pragma once

#include <unordered_map>

#include <memory>

#include <mutex>

#include <queue>

#include "abstract_engine_system.h"

#include "engine_message.h"

namespace engine {
	
	class EngineMessageBus
	{

		std::unordered_map<std::string, size_t> message_types_;
		
		std::unordered_map<std::string, std::weak_ptr<AbstractEngineSystem>> systems_;

		std::mutex queue_mutex_;

		std::mutex registry_mutex_;

		std::queue<EngineMessage *> messages_;

	public:

		EngineMessageBus();

		~EngineMessageBus();

		void RegisterSystem(const std::string &system_name, const std::shared_ptr<AbstractEngineSystem> &system);

		void RegisterMessage(const std::string &message, size_t message_size);

		bool PollMessages(EngineMessage * message);

		void PushMessage(EngineMessage * const message);

		void PostMessage(EngineMessage * const message);

		void PostImmediateMessage(EngineMessage * const message);
	};
}