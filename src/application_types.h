#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "abstract_core_system.h"

namespace core {

	enum class SystemFlagBit : uint8_t
	{
		Audio = 1 << 0,
		Graphics = 1 << 1,
		Input = 1 << 2,
		Entity = 1 << 3,
		Gui = 1 << 4,
		Resource = 1 << 5,
	};

	inline SystemFlagBit operator | (SystemFlagBit a, SystemFlagBit b)
	{
		return static_cast<SystemFlagBit>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
	}

	using SystemsMap = std::unordered_map<SystemFlagBit, std::unique_ptr<AbstractCoreSystem>>;
}
