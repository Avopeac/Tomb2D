#pragma once

#include "SDL.h"

#include "glm/glm.hpp"

#include "GL/glew.h"

namespace core
{
	class RenderQuad
	{
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

		GLuint vao_, vbo_, ebo_;

	public:

		RenderQuad();

		~RenderQuad();

		void Begin() const;

		void End() const;

		void DrawElements() const;

		inline Uint32 GetNumQuadVertices() const { return sizeof(quad_vertices_) / sizeof(quad_vertices_[0]); }

		inline Uint32 GetNumQuadIndices() const { return sizeof(quad_indices_) / sizeof(quad_indices_[0]); }

		inline const Uint32 * const GetQuadIndices() const { return quad_indices_; }

		inline const glm::vec2 * const GetQuadVertices() const { return quad_vertices_; }

	};
}
