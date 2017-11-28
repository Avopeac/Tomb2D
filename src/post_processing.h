#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <GL/glew.h>

#include "core.h"

namespace core
{
	class PostProcessEffect
	{

	public:

		PostProcessEffect() {};

		virtual ~PostProcessEffect() {};

		virtual void Init() = 0;

		virtual void Apply() = 0;

		void Render();
	};

	class PostProcessing
	{		

		std::vector<std::unique_ptr<PostProcessEffect>> effects_;

	public:
		
		PostProcessing();

		~PostProcessing();

		void Add(std::unique_ptr<PostProcessEffect> effect);

		void Process();

	};
}
