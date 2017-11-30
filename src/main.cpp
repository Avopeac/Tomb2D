#include "application_manager.h"
#include "sample_game_application.h"

Sint32 main(Sint32 argc, char * argv[])
{
	game::SampleGameApplication game_application;

	core::ApplicationManager application_manager(&game_application, 
		static_cast<uint8_t>(core::SystemFlagBit::Audio |
		core::SystemFlagBit::Entity |
		core::SystemFlagBit::Graphics |
		core::SystemFlagBit::Input |
		core::SystemFlagBit::Resource));


	application_manager.StartUp("assets/scripts/config.chai");

	application_manager.Run();

	application_manager.CleanUp();

	return 0;
}