#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace game
{
	enum TileType
	{
		Empty,
		Floor,
		TopLeftFloor,
		TopRightFloor,
		BottomLeftFloor,
		BottomRightFloor,
		TopFloor,
		BottomFloor,
		LeftFloor,
		RightFloor,
	};

	struct Tile
	{
		TileType type;
	};

	class AbstractMap
	{

		const glm::ivec2 size_;

		const glm::ivec2 tile_size_;

	protected:

		std::vector<Tile> tiles_;

	public:

		AbstractMap(const glm::ivec2 &size, const glm::ivec2 &tile_size) :
			size_(size), tile_size_(tile_size)
		{
		};

		virtual ~AbstractMap() = default;

		virtual void Create() = 0;

		virtual void Destroy() = 0;

		const std::vector<Tile> &GetTiles() const { return tiles_; }

		const glm::ivec2 &GetSize() const { return size_; }

		const glm::ivec2 &GetTileSize() const { return tile_size_; }

	};
	
}
