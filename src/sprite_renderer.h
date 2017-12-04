#pragma once

#include <vector>
#include <array>
#include <unordered_map>
#include <GL/glew.h>

#include "resource_core_system.h"
#include "graphics_core_system.h"
#include "sprite_data_message_queue.h"

namespace core 
{
	constexpr size_t MAX_SPRITE_INSTANCES{ 1024 };

	constexpr size_t MAX_SPRITE_LAYERS{ 16 };

	class SpriteRenderer
	{
		const glm::vec2 quad_vertices_[4] =
		{
			glm::vec2(-1.0f, -1.0f),
			glm::vec2(1.0f, -1.0f),
			glm::vec2(-1.0f,  1.0f),
			glm::vec2(1.0f,  1.0f),
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
			std::vector<BatchElement> elements;
		};

		struct BatchObject
		{
			GLuint vertex_array = 0;
			GLuint vertex_buffer = 0;
			GLuint element_buffer = 0;
			size_t num_indices = 0;
			size_t num_vertices = 0;
		} quad_batch_object_;

		GLuint instance_buffer_ = 0;

		std::array<std::unordered_map<size_t, Batch>, MAX_SPRITE_LAYERS> quad_batches_;

		Program * default_vert_program_;
		Program * default_frag_program_;
		ProgramPipeline pipeline_;

		ResourceCoreSystem &resource_core_;
		GraphicsCoreSystem &graphics_core_;

		SpriteDataMessageQueue &queue_;
		
	public:

		SpriteRenderer(SpriteDataMessageQueue &sprite_queue, 
			ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core);

		~SpriteRenderer();

		void Draw(float delta_time);

	private:

		void CreateInstanceBuffer();

		void DeleteInstanceBuffer();

		void CreateBatchObject(BatchObject &object, const glm::vec2 * const vertices,
			Uint32 num_vertices, const Uint32 * const indices, Uint32 num_indices);

		void DeleteBatchObject(BatchObject &object);

		void PushToBatchObject(std::unordered_map<size_t, Batch> &batches, const SpriteData &data);

		void DrawBatchObject(BatchObject &object, std::unordered_map<size_t, Batch> &batches);
	};
}
