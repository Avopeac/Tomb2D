#pragma once

#include "map_data.h"
#include "entity_manager.h"
#include "graphics_core_system.h"

namespace game {

	class MapView
	{

		MapData &map_;

		core::GraphicsCoreSystem &graphics_core_;

		core::EntityManager &entity_manager_;

	public:

		MapView(MapData &map, core::GraphicsCoreSystem &graphics_core, core::EntityManager &entity_manager);

		~MapView();

		void Initialize();
		
		void Update(float delta_time);
	};
}
