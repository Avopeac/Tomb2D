#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <functional>

#include "application_types.h"
#include "application.h"
#include "application_system_server.h"
#include "gui_tree.h"
#include "renderer.h"

namespace core {


	class ApplicationManager
	{
		Config config_;

		Application * application_;
		
		uint8_t system_flag_bits_;
		SystemPtrs system_ptrs_;
		SystemsMap systems_map_;
		std::unique_ptr<ApplicationSystemServer> system_server_;
		
		std::unique_ptr<Renderer> renderer_;
		std::unique_ptr<GuiTree> gui_tree_;

		std::function<bool(const ApplicationSystemServer &, const Config &, float)> run_hook_;
		std::function<bool(const ApplicationSystemServer &, const Config &)> start_up_hook;

	public:

		ApplicationManager(Application * application, uint8_t system_flag_bits);

		~ApplicationManager();

		void StartUp(const std::string &config_path);
		
		void Run();

		void CleanUp();

	};
}
