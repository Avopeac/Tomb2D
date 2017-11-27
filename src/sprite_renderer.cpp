#include "sprite_renderer.h"

#include "renderer.h"

#include "glm/gtc/type_ptr.hpp"

#include <algorithm>

using namespace graphics;

SpriteRenderer::SpriteRenderer(const GraphicsBase &graphics_base) :
	graphics_base_(graphics_base)
{
	default_vert_program_ = core::Core::GetResourceSystem()->GetProgramCache().GetFromFile("default_sprite.vert", GL_VERTEX_SHADER, "assets/shaders/default_sprite.vert");
	default_frag_program_ = core::Core::GetResourceSystem()->GetProgramCache().GetFromFile("default_sprite.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_sprite.frag");

	pipeline_.SetStages(*default_vert_program_);
	pipeline_.SetStages(*default_frag_program_);

	CreateInstanceBuffer();

	CreateBatchObject(flat_hex_batch_object_,
		flat_hexagon_vertices_, sizeof(flat_hexagon_vertices_) / sizeof(flat_hexagon_vertices_[0]),
		hexagon_indices_, sizeof(hexagon_indices_) / sizeof(hexagon_indices_[0])
	);

	CreateBatchObject(sharp_hex_batch_object_,
		sharp_hexagon_vertices_, sizeof(sharp_hexagon_vertices_) / sizeof(sharp_hexagon_vertices_[0]),
		hexagon_indices_, sizeof(hexagon_indices_) / sizeof(hexagon_indices_[0])
	);

	CreateBatchObject(quad_batch_object_,
		quad_vertices_, sizeof(quad_vertices_) / sizeof(quad_vertices_[0]),
		quad_indices_, sizeof(quad_indices_) / sizeof(quad_indices_[0])
	);

	CreateBatchObject(isometric_quad_batch_object_,
		isometric_quad_vertices_, sizeof(isometric_quad_vertices_) / sizeof(isometric_quad_vertices_[0]),
		quad_indices_, sizeof(quad_indices_) / sizeof(quad_indices_[0])
	);
}

SpriteRenderer::~SpriteRenderer()
{
	DeleteInstanceBuffer();
}

void SpriteRenderer::Draw(float delta_time)
{

	flat_hex_batches_.clear();
	sharp_hex_batches_.clear();
	quad_batches_.clear();
	isometric_quad_batches_.clear();

	auto &data = DataPipeHub::Get().GetSpriteDataPipe().GetData();
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		switch (it->sprite_shape)
		{
			case SpriteShape::FlatHex: { PushToBatchObject(flat_hex_batches_, *it); } break;
			case SpriteShape::SharpHex: { PushToBatchObject(sharp_hex_batches_, *it); } break;
			case SpriteShape::Quad: { PushToBatchObject(quad_batches_, *it); } break;
			case SpriteShape::IsometricQuad: { PushToBatchObject(isometric_quad_batches_, *it); } break;
			default:
			{
				debug::Log(SDL_LOG_PRIORITY_CRITICAL,
					SDL_LOG_CATEGORY_RENDER, "Trying to render unknown sprite shape."); 
				assert(false);
			}
		}
	}

	DataPipeHub::Get().GetSpriteDataPipe().Flush();

	core::FrameBuffer * render_target = 
		core::Core::GetResourceSystem()->GetFrameBufferCache().GetFromName(Renderer::render_target_name);

	render_target->BindDraw(GL_COLOR_BUFFER_BIT, 0.0f, 0.0f, 0.0f, 0.0f);

	pipeline_.Bind();

	int texture_index = 0;
	default_vert_program_->SetUniform("u_viewproj", 
		(void*)glm::value_ptr(graphics_base_.GetOrthographicCamera()->GetViewProj()));
	default_frag_program_->SetUniform("u_texture",
		(void*)&texture_index); 
	
	// Sort by layer
	std::sort(sharp_hex_batches_.begin(), sharp_hex_batches_.end(), [](const Batch &a, const Batch &b) { return a.layer < b.layer; });
	std::sort(flat_hex_batches_.begin(), flat_hex_batches_.end(), [](const Batch &a, const Batch &b) { return a.layer < b.layer; });
	std::sort(quad_batches_.begin(), quad_batches_.end(), [](const Batch &a, const Batch &b) { return a.layer < b.layer; });
	std::sort(isometric_quad_batches_.begin(), isometric_quad_batches_.end(), [](const Batch &a, const Batch &b) { return a.layer < b.layer; });

	size_t sharp_hex_start = 0;
	size_t flat_hex_start = 0;
	size_t quad_start = 0;
	size_t isometric_quad_start = 0;

	for (size_t layer = 0; layer < MAX_SPRITE_LAYERS; ++layer)
	{
		int sharp_hex_layer_count = 0;
		for (size_t j = sharp_hex_start; j < sharp_hex_batches_.size(); ++j)
		{
			if (sharp_hex_batches_[j].layer == layer)
			{
				sharp_hex_layer_count++;
			}
		}

		int flat_hex_layer_count = 0;
		for (size_t j = flat_hex_start; j < flat_hex_batches_.size(); ++j)
		{
			if (flat_hex_batches_[j].layer == layer)
			{
				flat_hex_layer_count++;
			}
		}

		int quad_layer_count = 0;
		for (size_t j = quad_start; j < quad_batches_.size(); ++j)
		{
			if (quad_batches_[j].layer == layer)
			{
				quad_layer_count++;
			}
		}

		int isometric_quad_layer_count = 0;
		for (size_t j = isometric_quad_start; j < isometric_quad_batches_.size(); ++j)
		{
			if (isometric_quad_batches_[j].layer == layer)
			{
				isometric_quad_layer_count++;
			}
		}

		if (sharp_hex_layer_count != 0)
		{
			DrawBatchObject(sharp_hex_batch_object_, sharp_hex_start, sharp_hex_layer_count, sharp_hex_batches_);
			sharp_hex_start += sharp_hex_layer_count;
		}
		
		if (flat_hex_layer_count != 0)
		{
			DrawBatchObject(flat_hex_batch_object_, flat_hex_start, flat_hex_start + flat_hex_layer_count, flat_hex_batches_);
			flat_hex_start += flat_hex_layer_count;
		}
		
		if (quad_layer_count != 0)
		{
			DrawBatchObject(quad_batch_object_, quad_start, quad_start + quad_layer_count, quad_batches_);
			quad_start += quad_layer_count;
		}

		if (isometric_quad_layer_count != 0)
		{
			DrawBatchObject(isometric_quad_batch_object_, isometric_quad_start, 
				isometric_quad_start + isometric_quad_layer_count, isometric_quad_batches_);
			isometric_quad_start += isometric_quad_layer_count;
		}
	}

	pipeline_.Unbind();
}

void SpriteRenderer::CreateInstanceBuffer()
{
	glGenBuffers(1, &instance_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_);
	glBufferData(GL_ARRAY_BUFFER, MAX_SPRITE_INSTANCES * sizeof(BatchElement), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void SpriteRenderer::DeleteInstanceBuffer()
{
	glDeleteBuffers(1, &instance_buffer_);
}

void SpriteRenderer::CreateBatchObject(BatchObject & object, const glm::vec2 * const vertices, Uint32 num_vertices, const Uint32 * const indices, Uint32 num_indices)
{
	object.num_vertices = num_vertices;
	object.num_indices = num_indices;

	auto vertex_size = sizeof(vertices[0]);
	auto index_size = sizeof(indices[0]);
	auto vertices_size = object.num_vertices * vertex_size;
	auto indices_size = object.num_indices * index_size;

	glGenBuffers(1, &object.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &object.element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLint attrib_index = 0;
	glGenVertexArrays(1, &object.vertex_array);
	glBindVertexArray(object.vertex_array);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.element_buffer);

	// Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, object.vertex_buffer);

	// Position attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 2, GL_FLOAT, GL_FALSE, (GLsizei)vertex_size, 0);
	glVertexAttribDivisor(attrib_index, 0);
	attrib_index++;

	// Instance data

	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_);

	// Transform attribute
	
	size_t attribute_offset = 0;

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);

	// Color attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);
	 
	// Animation attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexBindingDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(glm::vec4);

	// Layer attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 1, GL_UNSIGNED_INT, GL_FALSE, (GLsizei)sizeof(BatchElement), (const void *)attribute_offset);
	glVertexBindingDivisor(attrib_index, 1);
	attrib_index++; attribute_offset += sizeof(uint32_t);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DeleteBatchObject(BatchObject & object)
{
	glDeleteVertexArrays(1, &object.vertex_array);
	glDeleteBuffers(1, &object.vertex_buffer);
	glDeleteBuffers(1, &object.element_buffer);
}

void SpriteRenderer::PushToBatchObject(std::vector<Batch> &batches, const SpriteData & data)
{
	// Reverse order of sprite layers
	uint32_t data_sprite_layer = uint32_t((MAX_SPRITE_LAYERS - 1) - data.sprite_layer);

	BatchElement element;
	element.sprite_color = data.sprite_color;
	element.sprite_transform = data.sprite_transform;
	element.sprite_animation = data.sprite_animation;
	element.sprite_layer = data_sprite_layer;

	if (batches.empty() ||
		data_sprite_layer != batches.back().layer || 
		data.texture_hash != batches.back().texture_hash ||
		data.blend_hash != batches.back().blend_hash ||
		data.sampler_hash != batches.back().sampler_hash)
	{
		// Add sprite data to new sprite batch
		Batch batch;
		batch.texture_hash = data.texture_hash;
		batch.blend_hash = data.blend_hash;
		batch.sampler_hash = data.sampler_hash;
		batch.layer = data_sprite_layer;
		batch.elements.push_back(element);

		batches.push_back(batch);
	}
	else
	{
		// Add sprite data to old sprite batch
		batches.back().elements.push_back(element);
	}
}

void SpriteRenderer::DrawBatchObject(BatchObject & object, size_t start, size_t end, std::vector<Batch> &batches)
{

	auto & blend_cache = core::Core::GetResourceSystem()->GetBlendCache();
	auto & sampler_cache = core::Core::GetResourceSystem()->GetSamplerCache();
	auto & texture_cache = core::Core::GetResourceSystem()->GetTextureCache();

	glBindVertexArray(object.vertex_array);

	for (size_t i = start; i < end; ++i)
	{
		
		// Especially for isometric tiles we need to draw higher y-coordinates first
		std::sort(batches[i].elements.begin(), batches[i].elements.end(),
			[](BatchElement &a, BatchElement &b) { return a.sprite_transform[3][1] > b.sprite_transform[3][1]; });

		// Set blend mode for batch
		blend_cache.GetFromHash(batches[i].blend_hash)->Set();

		// Set sampler and texture if present
		if (batches[i].sampler_hash && batches[i].texture_hash)
		{
			sampler_cache.GetFromHash(batches[i].sampler_hash)->Bind(0);
			texture_cache.GetFromHash(batches[i].texture_hash)->Bind(0);
		}

		// Re-upload subdata for instance buffer
		size_t instance_size = batches[i].elements.size() * sizeof(BatchElement);
		glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_);
		glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, (GLsizei)instance_size, &batches[i].elements[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Draw all sprites for the batch
		glDrawElementsInstanced(GL_TRIANGLES,
			(GLsizei)object.num_indices, GL_UNSIGNED_INT, 0,
			(GLsizei)batches[i].elements.size());

		batches[i].elements.clear();
	}

	glBindVertexArray(0);
}
