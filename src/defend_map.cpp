#include "defend_map.h"

using namespace game;

DefendMap::DefendMap() :
	AbstractMap(size_, tile_size_)
{
}

DefendMap::~DefendMap()
{
}

void DefendMap::Create()
{
	glm::ivec2 size = GetSize();

	tiles_.resize(size.x * size.y);

	for (int y = 0; y < size.y; ++y)
	{

		for (int x = 0; x < size_.x; ++x)
		{
			auto & tile = tiles_[x + y * size.x];
		}
	}
}

void DefendMap::Destroy()
{

}
