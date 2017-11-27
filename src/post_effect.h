#pragma once

#include "post_processing.h"

namespace graphics
{
	class PostEffect : public PostProcessEffect
	{
		const std::string v_name_ = "postfx.vert"; 
		const std::string f_name_ = "postfx.frag";
		const std::string v_path_ = "assets/shaders/postfx.vert";
		const std::string f_path_ = "assets/shaders/postfx.frag";

		core::Program * vertex_shader_;
		core::Program * fragment_shader_;

		core::ProgramPipeline pipeline_;

		core::FrameBuffer * fbo0_;

	public:

		PostEffect();

		~PostEffect();

		// Inherited via PostProcessEffect
		virtual void Init() override;

		virtual void Apply() override;

	};
}

