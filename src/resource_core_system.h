#pragma once

#include <memory>

#include "abstract_core_system.h"

#include "blend_mode.h"
#include "frame_buffer.h"
#include "sampler.h"
#include "shader.h"
#include "texture.h"
#include "font.h"
#include "text.h"
#include "sound.h"

namespace core
{

	class ResourceCoreSystem : public AbstractCoreSystem
	{
		std::unique_ptr<BlendCache> blend_cache_;
		std::unique_ptr<FrameBufferCache> frame_buffer_cache_;
		std::unique_ptr<SamplerCache> sampler_cache_;
		std::unique_ptr<ProgramCache> program_cache_;
		std::unique_ptr<TextureCache> texture_cache_;
		std::unique_ptr<FontCache> font_cache_;
		std::unique_ptr<SoundCache> sound_cache_;
		std::unique_ptr<TextCache> text_cache_;

	public:

		ResourceCoreSystem();

		~ResourceCoreSystem();

		void StartUp(const Config &config) override;

		void CleanUp() override;

		inline BlendCache &GetBlendCache() { return *blend_cache_.get(); }

		inline FrameBufferCache &GetFrameBufferCache() { return *frame_buffer_cache_.get(); }

		inline SamplerCache &GetSamplerCache() { return *sampler_cache_.get(); }

		inline ProgramCache &GetProgramCache() { return *program_cache_.get(); }

		inline TextureCache &GetTextureCache() { return *texture_cache_.get(); }

		inline FontCache &GetFontCache() { return *font_cache_.get(); }

		inline SoundCache &GetSoundCache() { return *sound_cache_.get(); }

		inline TextCache &GetTextCache() { return *text_cache_.get(); }
	};
}
