#pragma once

#include "map_data.h"

namespace game {

	class MapView
	{

		MapData &map_;

	public:

		MapView(MapData &map);

		~MapView();

		void Initialize();
		
		void Update(float delta_time);
	};
}
