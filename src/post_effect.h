#pragma once

#include "post_processing.h"

#include "resource_core_system.h"

namespace core
{
	class PostEffect : public PostProcessEffect
	{
		const std::string v_name_ = "postfx.vert"; 
		const std::string f_name_ = "postfx.frag";
		const std::string v_path_ = "assets/shaders/postfx.vert";
		const std::string f_path_ = "assets/shaders/postfx.frag";

		Program * vertex_shader_;
		Program * fragment_shader_;
		ProgramPipeline pipeline_;
		FrameBuffer * fbo0_;

	public:

		PostEffect();

		~PostEffect();

		// Inherited via PostProcessEffect
		virtual void Init(ResourceCoreSystem &resource_core) override;

		virtual void Apply(RenderQuad &quad, ResourceCoreSystem &resource_core, 
			GraphicsCoreSystem &graphics_core) override;

	};
}

