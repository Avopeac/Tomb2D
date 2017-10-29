#include "sprite_renderer.h"

#include "renderer.h"

#include "glm/gtc/type_ptr.hpp"

#include <algorithm>

using namespace graphics;

SpriteRenderer::SpriteRenderer(const GraphicsBase &graphics_base) :
	graphics_base_(graphics_base)
{
	default_vert_program_ = ResourceManager::Get().GetProgramCache().GetFromFile("default_sprite.vert", GL_VERTEX_SHADER, "assets/shaders/default_sprite.vert");
	default_frag_program_ = ResourceManager::Get().GetProgramCache().GetFromFile("default_sprite.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_sprite.frag");

	pipeline_.SetStages(*default_vert_program_);
	pipeline_.SetStages(*default_frag_program_);

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
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Draw(float delta_time)
{
	auto &data = DataPipeHub::Get().GetSpriteDataPipe().GetData();
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		switch (it->sprite_shape)
		{
			case SpriteShape::FlatHex: { PushToBatchObject(flat_hex_batches_, *it); } break;
			case SpriteShape::SharpHex: { PushToBatchObject(sharp_hex_batches_, *it); } break;
			case SpriteShape::Quad: { PushToBatchObject(quad_batches_, *it); } break;
			default:
			{
				debug::Log(SDL_LOG_PRIORITY_CRITICAL,
					SDL_LOG_CATEGORY_RENDER, "Trying to render unknown sprite shape."); 
				assert(false);
			}
		}
	}

	DataPipeHub::Get().GetSpriteDataPipe().Flush();


	FrameBuffer * render_target = 
		ResourceManager::Get().GetFrameBufferCache().GetFromName(Renderer::render_target_name);

	render_target->BindDraw(GL_COLOR_BUFFER_BIT, 0.0f, 0.0f, 0.0f, 0.0f);

	pipeline_.Bind();

	int texture_index = 2;

	default_vert_program_->SetUniform("u_viewproj", 
		(void*)glm::value_ptr(graphics_base_.GetOrthographicCamera()->GetViewProj()));
	default_frag_program_->SetUniform("u_texture",
		(void*)&texture_index); 

	DrawBatchObject(sharp_hex_batch_object_, sharp_hex_batches_);
	DrawBatchObject(flat_hex_batch_object_, flat_hex_batches_);
	DrawBatchObject(quad_batch_object_, quad_batches_);

	pipeline_.Unbind();
}

void SpriteRenderer::CreateBatchObject(BatchObject & object, const glm::vec2 * const vertices, Uint32 num_vertices, const Uint32 * const indices, Uint32 num_indices)
{
	object.num_vertices = num_vertices;
	object.num_indices = num_indices;

	auto vertex_size = sizeof(vertices[0]);
	auto index_size = sizeof(indices[0]);
	auto vertices_size = object.num_vertices * vertex_size;
	auto indices_size = object.num_indices * index_size;
	auto instance_size = sizeof(BatchElement);

	glGenBuffers(1, &object.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &object.instance_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object.instance_buffer);
	glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES_PER_BATCH * instance_size, nullptr, GL_DYNAMIC_DRAW);
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

	glBindBuffer(GL_ARRAY_BUFFER, object.instance_buffer);

	// Transform attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)instance_size, (const void *)(0 * sizeof(glm::vec4)));
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++;

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)instance_size, (const void *)(1 * sizeof(glm::vec4)));
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++;

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)instance_size, (const void *)(2 * sizeof(glm::vec4)));
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++;

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)instance_size, (const void *)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++;

	// Color attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, (GLsizei)instance_size, (const void *)(4 * sizeof(glm::vec4)));
	glVertexAttribDivisor(attrib_index, 1);
	attrib_index++;

	// Layer attribute

	glEnableVertexAttribArray(attrib_index);
	glVertexAttribPointer(attrib_index, 1, GL_UNSIGNED_INT, GL_FALSE, (GLsizei)instance_size, (const void *)(5 * sizeof(glm::vec4)));
	glVertexBindingDivisor(attrib_index, 1);
	attrib_index++;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DeleteBatchObject(BatchObject & object)
{
	glDeleteVertexArrays(1, &object.vertex_array);
	glDeleteBuffers(1, &object.vertex_buffer);
	glDeleteBuffers(1, &object.element_buffer);
	glDeleteBuffers(1, &object.instance_buffer);
}

void SpriteRenderer::PushToBatchObject(std::vector<Batch> &batches, const SpriteData & data)
{

	BatchElement element;
	element.sprite_color = data.sprite_color;
	element.sprite_transform = data.sprite_transform;

	if (batches.empty() ||
		data.texture_hash != batches.back().texture_hash ||
		data.blend_hash != batches.back().blend_hash ||
		data.sampler_hash != batches.back().sampler_hash)
	{
		// Add sprite data to new sprite batch
		Batch batch;
		batch.texture_hash = data.texture_hash;
		batch.blend_hash = data.blend_hash;
		batch.sampler_hash = data.sampler_hash;
		batch.elements.push_back(element);

		batches.push_back(batch);
	}
	else
	{
		// Add sprite data to old sprite batch
		batches.back().elements.push_back(element);
	}
}

void SpriteRenderer::DrawBatchObject(BatchObject & object, std::vector<Batch> &batches)
{

	auto & blend_cache = ResourceManager::Get().GetBlendCache();
	auto & sampler_cache = ResourceManager::Get().GetSamplerCache();
	auto & texture_cache = ResourceManager::Get().GetTextureCache();

	glBindVertexArray(object.vertex_array);

	for (auto &batch : batches)
	{
		// Sort by layer within batch
		std::sort(batch.elements.begin(), batch.elements.end(), 
			[](const BatchElement &a, const BatchElement &b)
		{
			return a.sprite_layer < b.sprite_layer;
		});

		// Set blend mode for batch
		blend_cache.GetFromHash(batch.blend_hash)->Set();

		// Set sampler and texture if present
		if (batch.sampler_hash && batch.texture_hash)
		{
			sampler_cache.GetFromHash(batch.sampler_hash)->Bind(2);
			texture_cache.GetFromHash(batch.texture_hash)->Bind(2);
		}

		// Re-upload subdata for instance buffer
		glBindBuffer(GL_ARRAY_BUFFER, object.instance_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizei)(batch.elements.size() * sizeof(BatchElement)),
			&batch.elements[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Draw all sprites for the batch
		glDrawElementsInstanced(GL_TRIANGLES,
			(GLsizei)object.num_indices, GL_UNSIGNED_INT, 0,
			(GLsizei)batch.elements.size());

		batch.elements.clear();
	}

	glBindVertexArray(0);
}
