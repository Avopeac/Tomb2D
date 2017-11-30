#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <functional>

#include "application_types.h"
#include "renderer.h"
#include "application.h"

namespace core {


	class ApplicationManager
	{
		Application * application_;
		Config config_;
		SystemPtrs system_ptrs_;
		SystemsMap systems_map_;
		uint8_t system_flag_bits_;
		std::unique_ptr<Renderer> renderer_;
		std::function<bool(const SystemsMap &, const Config &, float)> run_hook_;
		std::function<bool(const SystemsMap &, const Config &)> start_up_hook;

	public:

		ApplicationManager(Application * application, uint8_t system_flag_bits);

		~ApplicationManager();

		void StartUp(const std::string &config_path);
		
		void Run();

		void CleanUp();

	};
}
