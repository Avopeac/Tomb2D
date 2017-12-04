#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "sprite_renderer.h"
#include "renderer.h"

using namespace core;

SpriteRenderer::SpriteRenderer(SpriteDataMessageQueue &sprite_queue,
	ResourceCoreSystem &resource_core, GraphicsCoreSystem &graphics_core) : 
	queue_(sprite_queue), resource_core_(resource_core), graphics_core_(graphics_core)
{
	default_vert_program_ = resource_core.GetProgramCache().GetFromFile("default_sprite.vert", GL_VERTEX_SHADER, "assets/shaders/default_sprite.vert");
	default_frag_program_ = resource_core.GetProgramCache().GetFromFile("default_sprite.frag", GL_FRAGMENT_SHADER, "assets/shaders/default_sprite.frag");

	pipeline_.SetStages(*default_vert_program_);
	pipeline_.SetStages(*default_frag_program_);

	CreateInstanceBuffer();

	CreateBatchObject(quad_batch_object_,
		quad_vertices_, sizeof(quad_vertices_) / sizeof(quad_vertices_[0]),
		quad_indices_, sizeof(quad_indices_) / sizeof(quad_indices_[0]));
}

SpriteRenderer::~SpriteRenderer()
{
	DeleteInstanceBuffer();
}

void SpriteRenderer::Draw(float delta_time)
{
	// Clear old batch
	quad_batches_.clear();

	// Push sprites to batch
	SpriteData data{};
	while (queue_.TryPop(data))
	{
		PushToBatchObject(quad_batches_, data);
	}

	FrameBuffer * render_target = resource_core_.GetFrameBufferCache().
		GetFromName(Renderer::render_target_name);
	render_target->BindDraw(GL_COLOR_BUFFER_BIT, 0.0f, 0.0f, 0.0f, 0.0f);

	pipeline_.Bind();

	int texture_index = 0;
	default_vert_program_->SetUniform("u_viewproj", (void*)glm::value_ptr(graphics_core_.GetOrthographicCamera()->GetViewProj()));
	default_frag_program_->SetUniform("u_texture",	(void*)&texture_index); 
	
	// Sort by layer
	std::sort(quad_batches_.begin(), quad_batches_.end(), [](const Batch &a, const Batch &b) { return a.layer < b.layer; });

	size_t quad_start = 0;

	for (size_t layer = 0; layer < MAX_SPRITE_LAYERS; ++layer)
	{
		int quad_layer_count = 0;

		for (size_t j = quad_start; j < quad_batches_.size(); ++j)
		{
			if (quad_batches_[j].layer == layer)
			{
				quad_layer_count++;
			}
		}

		if (quad_layer_count != 0)
		{
			DrawBatchObject(quad_batch_object_, quad_start, quad_start + quad_layer_count, quad_batches_);

			quad_start += quad_layer_count;
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

	glBindVertexArray(object.vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_);

	for (size_t i = start; i < end; ++i)
	{
		
		// Especially for isometric tiles we need to draw higher y-coordinates first
		std::sort(batches[i].elements.begin(), batches[i].elements.end(),
			[](BatchElement &a, BatchElement &b) { return a.sprite_transform[3][1] > b.sprite_transform[3][1]; });

		// Set blend mode for batch
		resource_core_.GetBlendCache().GetFromHash(batches[i].blend_hash)->Set();

		// Set sampler and texture if present
		if (batches[i].sampler_hash && batches[i].texture_hash)
		{
			resource_core_.GetSamplerCache().GetFromHash(batches[i].sampler_hash)->Bind(0);
			resource_core_.GetTextureCache().GetFromHash(batches[i].texture_hash)->Bind(0);
		}

		// Re-upload subdata for instance buffer
		size_t instance_size = batches[i].elements.size() * sizeof(BatchElement);
		glInvalidateBufferSubData(GL_ARRAY_BUFFER, 0, instance_size);
		glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, (GLsizei)instance_size, &batches[i].elements[0]);
	
		// Draw all sprites for the batch
		glDrawElementsInstanced(GL_TRIANGLES,
			(GLsizei)object.num_indices, GL_UNSIGNED_INT, 0,
			(GLsizei)batches[i].elements.size());
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
