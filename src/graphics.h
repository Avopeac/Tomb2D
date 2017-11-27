#pragma once

#include <memory>

#include "SDL.h"

#include "glm/glm.hpp"

#include "config.h"
#include "orthographic_camera.h"

namespace graphics
{
	class GraphicsBase
	{
		SDL_Window * window_;
		SDL_GLContext context_;

		Uint32 window_width_;
		Uint32 window_height_;
		
		const glm::vec2 quad_vertices_[4] =
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f,  1.0f),
			glm::vec2(1.0f,  1.0f),
		};

		const Uint32 quad_indices_[6] =
		{
			0, 1, 2,
			2, 1, 3
		};

		std::unique_ptr<OrthographicCamera> camera_;

	public:

		GraphicsBase(const core::Config &config);

		~GraphicsBase();

		inline SDL_Window * GetWindow() const { return window_; }

		inline Uint32 GetBackbufferWidth() const { return window_width_; }

		inline Uint32 GetBackbufferHeight() const { return window_height_; }

		inline Uint32 GetNumQuadVertices() const { return sizeof(quad_vertices_) / sizeof(quad_vertices_[0]); }

		inline Uint32 GetNumQuadIndices() const { return sizeof(quad_indices_) / sizeof(quad_indices_[0]); }

		inline const Uint32 * const GetQuadIndices() const { return quad_indices_; }

		inline const glm::vec2 * const GetQuadVertices() const { return quad_vertices_; }

		inline AbstractCamera * GetOrthographicCamera() const { return camera_.get(); }

		inline float GetAspectRatio() const { return float(window_width_) / window_height_; }

		glm::vec2 PixelsToScaleAspect(const glm::uvec2 &pixels) const;

		glm::vec2 PixelsToScale(const glm::uvec2 &pixels) const;
	};
}
