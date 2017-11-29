#pragma once

#include "map_data.h"
#include "entity_core_system.h"
#include "graphics_core_system.h"

namespace game {

	class MapView
	{

		MapData &map_;

		core::GraphicsCoreSystem &graphics_core_;

		core::EntityCoreSystem &entity_core_;

	public:

		MapView(MapData &map, core::GraphicsCoreSystem &graphics_core, core::EntityCoreSystem &entity_core);

		~MapView();

		void Initialize();
		
		void Update(float delta_time);
	};
}
