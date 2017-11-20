#pragma once

#include "map_data.h"

#include "graphics.h"

namespace game {

	class MapView
	{

		MapData &map_;

		const graphics::GraphicsBase &graphics_base_;

	public:

		MapView(const graphics::GraphicsBase &graphics_base, MapData &map);

		~MapView();

		void Initialize();
		
		void Update(float delta_time);
	};
}
