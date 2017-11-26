#pragma once

#include <string>

struct EngineMessage
{
	std::string name;
	size_t size;
	void * data;
};