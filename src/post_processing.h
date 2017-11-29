#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <GL/glew.h>

#include "render_quad.h"
#include "resource_core_system.h"
#include "graphics_core_system.h"

namespace core
{
	class PostProcessEffect
	{

	public:

		PostProcessEffect() {};

		virtual ~PostProcessEffect() {};

		virtual void Init(ResourceCoreSystem &resource_core) = 0;

		virtual void Apply(RenderQuad &quad, ResourceCoreSystem &resource_core, 
			GraphicsCoreSystem &graphics_core) = 0;

	};

	class PostProcessing
	{		

		std::vector<std::unique_ptr<PostProcessEffect>> effects_;

		ResourceCoreSystem &resource_core_;

		GraphicsCoreSystem &graphics_core_;
		
		RenderQuad &quad_;

	public:
		
		PostProcessing(RenderQuad &quad, ResourceCoreSystem &resource_core,
			GraphicsCoreSystem &graphics_core);

		~PostProcessing();

		void Add(std::unique_ptr<PostProcessEffect> effect);

		void Process();

	};
}
