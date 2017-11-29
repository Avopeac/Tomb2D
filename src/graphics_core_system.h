#pragma once

#include <memory>

#include "SDL.h"

#include "glm/glm.hpp"

#include "abstract_core_system.h"

#include "orthographic_camera.h"

namespace core {

	class GraphicsCoreSystem : AbstractCoreSystem
	{
		SDL_Window * window_;
		SDL_GLContext context_;

		Uint32 window_width_;
		Uint32 window_height_;

		std::unique_ptr<OrthographicCamera> camera_;

	public:

		GraphicsCoreSystem(); 

		~GraphicsCoreSystem();

		void StartUp(const Config &config) override;

		void CleanUp() override;

		inline SDL_Window * GetWindow() const { return window_; }

		inline Uint32 GetBackbufferWidth() const { return window_width_; }

		inline Uint32 GetBackbufferHeight() const { return window_height_; }

		inline float GetAspectRatio() const { return float(window_width_) / window_height_; }

		inline AbstractCamera * GetOrthographicCamera() const { return camera_.get(); }

		glm::vec2 PixelsToScaleAspect(const glm::uvec2 &pixels) const;

		glm::vec2 PixelsToScale(const glm::uvec2 &pixels) const;
	};
}
