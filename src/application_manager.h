#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <functional>

#include "application_types.h"
#include "renderer.h"

namespace core {


	class ApplicationManager
	{
		Config config_;
		SystemsMap systems_map_;
		uint8_t system_flag_bits_;
		std::unique_ptr<Renderer> renderer_;
		std::function<bool(const SystemsMap &, const Config &, float)> run_hook_;
		std::function<bool(const SystemsMap &, const Config &)> start_up_hook;

	public:

		ApplicationManager(uint8_t system_flag_bits);

		~ApplicationManager();

		void StartUp(const std::string &config_path);
		
		void Run();

		void CleanUp();

		void SetStartUpHook(std::function<bool(const SystemsMap &, const Config &)> hook);

		void SetRunHook(std::function<bool(const SystemsMap &, const Config &, float)> hook);

	};
}
