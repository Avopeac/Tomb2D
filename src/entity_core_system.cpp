#include "entity_core_system.h"

using namespace core;

EntityCoreSystem::EntityCoreSystem() : entity_unique_id_counter_(0), systems_counter_(0) 
{

}

EntityCoreSystem::~EntityCoreSystem()
{
	for (size_t i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities_.at(i))
		{
			for (size_t j = 0; j < MAX_COMPONENTS; ++j)
			{
				if (entity_components_.at(i)[j])
				{
					delete entity_components_.at(i)[j];
				}
			}

			delete entities_.at(i);
		}
	}

	for (size_t i = 0; i < MAX_SYSTEMS; ++i)
	{
		if (component_systems_[i])
		{
			delete component_systems_[i];
		}
	}
}

void EntityCoreSystem::StartUp(const Config & config)
{
	// Nothing here
}

void EntityCoreSystem::Update(float delta_time)
{
	for (auto * system : component_systems_)
	{
		if (system)
		{
			for (auto it = entities_.begin(); it != entities_.end(); ++it)
			{
				system->TryUpdate(it->second, delta_time);
			}
		}
	}
}

void EntityCoreSystem::CleanUp()
{
	// Nothing here
}

void EntityCoreSystem::AddSystem(AbstractSystem * system)
{
	if (systems_counter_ + 1 < MAX_SYSTEMS)
	{
		component_systems_[systems_counter_++] = system;
	}
	else
	{
		SDL_assert(false && "Added too many component systems.");
	}
}

const Entity * const EntityCoreSystem::CreateEntity(const std::string &name)
{

	SDL_assert(!(entity_unique_id_counter_ >= MAX_ENTITIES &&
		entity_unique_id_counter_queue_.empty()));

	size_t id;
	if (!entity_unique_id_counter_queue_.empty())
	{
		id = entity_unique_id_counter_queue_.front();
		entity_unique_id_counter_queue_.pop();
	}
	else
	{
		id = entity_unique_id_counter_++;
	}

	Entity * entity = new Entity(id);
	entities_.insert({ id, entity });
	entity_name_map_.insert({ id, name });
	return entity;
}

const std::string * const EntityCoreSystem::GetEntityNameById(EntityId id) const
{
	return entity_name_map_.find(id) != entity_name_map_.cend() ?
		&entity_name_map_.at(id) : nullptr;
}

const Entity * const EntityCoreSystem::GetEntityByName(const std::string & name) const
{
	for (auto &it = entity_name_map_.cbegin(); it != entity_name_map_.cend(); ++it)
	{
		if (it->second == name)
		{
			return entities_.at(it->first);
		}
	}

	return nullptr;
}

const Entity * const EntityCoreSystem::GetEntityById(EntityId id) const
{
	return id < MAX_ENTITIES ? entities_.at(id) : nullptr;
}

void EntityCoreSystem::DeleteEntity(EntityId id)
{
	if (id < MAX_ENTITIES && entities_.at(id))
	{
		delete entities_.at(id);
		entity_name_map_.erase(id);
		entity_unique_id_counter_queue_.push(id);
	}
}