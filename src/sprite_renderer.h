#pragma once

#include <vector>
#include <unordered_map>
#include <GL/glew.h>
#include "data_pipe_hub.h"
#include "resource_core_system.h"
#include "graphics_core_system.h"

namespace core 
{
	constexpr size_t MAX_SPRITE_INSTANCES{ 8192 };

	constexpr size_t MAX_SPRITE_LAYERS{ 32 };

	class SpriteRenderer
	{
		const glm::vec2 sharp_hexagon_vertices_[7] =
		{
			glm::vec2(0.0f, 1.0f), // Top vertex
			glm::vec2(1.0f, 0.5f), // Top right vertex
			glm::vec2(1.0f, -0.5f), // Bottom right vertex
			glm::vec2(0.0f, -1.0f), // Bottom vertex
			glm::vec2(-1.0f, -0.5f), // Bottom left vertex
			glm::vec2(-1.0f, 0.5f), // Top left vertex
			glm::vec2(0.0f, 0.0f), // Center vertex
		};

		const glm::vec2 flat_hexagon_vertices_[7] =
		{
			glm::vec2(-1.0f, 0.0f), // Left vertex
			glm::vec2(-0.5f, 1.0f), // Top left vertex
			glm::vec2(0.5f, 1.0f), // Top right vertex
			glm::vec2(1.0f, 0.0f), // Right vertex
			glm::vec2(0.5f, -1.0f), // Bottom right vertex
			glm::vec2(-0.5f, -1.0f), // Bottom left vertex
			glm::vec2(0.0f, 0.0f), // Center vertex
		};

		const Uint32 hexagon_indices_[18] = {
			0, 6, 1,
			1, 6, 2,
			2, 6, 3,
			3, 6, 4,
			4, 6, 5,
			5, 6, 0,
		};

		const glm::vec2 quad_vertices_[4] =
		{
			glm::vec2(-1.0f, -1.0f),
			glm::vec2(1.0f, -1.0f),
			glm::vec2(-1.0f,  1.0f),
			glm::vec2(1.0f,  1.0f),
		};

		const glm::vec2 isometric_quad_vertices_[4]{
			glm::vec2(-1.0f, 0.0f),
			glm::vec2(0.0f, -1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
		};

		const Uint32 quad_indices_[6] =
		{
			0, 1, 2,
			2, 1, 3
		};

		struct BatchElement
		{
			glm::mat4 sprite_transform;
			glm::vec4 sprite_color;
			glm::vec4 sprite_animation;
			uint32_t sprite_layer;
		};

		struct Batch
		{
			size_t texture_hash;
			size_t blend_hash;
			size_t sampler_hash;
			uint32_t layer;
			std::vector<BatchElement> elements;
		};

		struct BatchObject
		{
			GLuint vertex_array = 0;
			GLuint vertex_buffer = 0;
			GLuint element_buffer = 0;
			size_t num_indices = 0;
			size_t num_vertices = 0;
		};

		GLuint instance_buffer_ = 0;

		std::vector<Batch> quad_batches_;
		std::vector<Batch> isometric_quad_batches_;
		std::vector<Batch> flat_hex_batches_;
		std::vector<Batch> sharp_hex_batches_;

		BatchObject isometric_quad_batch_object_;
		BatchObject quad_batch_object_;
		BatchObject flat_hex_batch_object_;
		BatchObject sharp_hex_batch_object_;

		ProgramPipeline pipeline_;
		Program * default_vert_program_;
		Program * default_frag_program_;

		ResourceCoreSystem &resource_core_;
		GraphicsCoreSystem &graphics_core_;
		
	public:

		SpriteRenderer(ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core);

		~SpriteRenderer();

		void Draw(float delta_time);

	private:

		void CreateInstanceBuffer();

		void DeleteInstanceBuffer();

		void CreateBatchObject(BatchObject &object, const glm::vec2 * const vertices,
			Uint32 num_vertices, const Uint32 * const indices, Uint32 num_indices);

		void DeleteBatchObject(BatchObject &object);

		void PushToBatchObject(std::vector<Batch> &batches, const SpriteData &data);

		void DrawBatchObject(BatchObject &object, size_t start, size_t end, std::vector<Batch> &batches);
	};
}
