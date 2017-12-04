#pragma once

#include "map_data.h"
#include "application_system_server.h"

namespace game {

	class MapView
	{

		MapData &map_;

		const core::ApplicationSystemServer &application_system_server_;

	public:

		MapView(MapData &map, const core::ApplicationSystemServer &server);

		~MapView();

		void Initialize();
		
		void Update(float delta_time);
	};
}
