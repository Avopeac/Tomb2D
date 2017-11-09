#pragma once

#include "abstract_map.h"

namespace game {

	class DefendMap : public AbstractMap
	{

		const glm::ivec2 size_{ 24, 24 };

		const glm::ivec2 tile_size_{ 32, 32 };

	public:

		DefendMap();

		virtual ~DefendMap();

		// Inherited via AbstractMap
		virtual void Create() override;
		virtual void Destroy() override;
	};

}
