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
	// Clear old batches
	for (auto it = quad_batches_.begin(); it != quad_batches_.end(); ++it)
	{
		it->clear();
	}
	
	// Push sprites to batch
	SpriteData data{};
	while (queue_.TryPop(data))
	{
		if (data.sprite_layer > MAX_SPRITE_LAYERS)
		{
			data.sprite_layer = MAX_SPRITE_LAYERS;
		}
		
		PushToBatchObject(quad_batches_[data.sprite_layer], data);
	}

	FrameBuffer * render_target = resource_core_.GetFrameBufferCache().
		GetFromName(Renderer::render_target_name);
	render_target->BindDraw(GL_COLOR_BUFFER_BIT, 0.0f, 0.0f, 0.0f, 0.0f);

	int texture_index = 0;
	default_vert_program_->SetUniform("u_viewproj",
		(void*)glm::value_ptr(graphics_core_.GetOrthographicCamera()->GetViewProj()));
	default_frag_program_->SetUniform("u_texture",
		(void*)&texture_index); 
	
	pipeline_.Bind();

	for (auto it = quad_batches_.rbegin(); it != quad_batches_.rend(); ++it)
	{
		if (!it->empty())
		{
			DrawBatchObject(quad_batch_object_, *it);
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

void SpriteRenderer::PushToBatchObject(std::unordered_map<size_t, Batch> &batches, const SpriteData & data)
{
	BatchElement element;
	element.sprite_color = data.sprite_color;
	element.sprite_transform = data.sprite_transform;
	element.sprite_animation = data.sprite_animation;

	size_t batch_id =
		data.texture_hash ^
		data.blend_hash ^
		data.sampler_hash;

	if (batches.find(batch_id) == batches.end())
	{
		// Add sprite data to new sprite batch
		Batch batch;
		batch.texture_hash = data.texture_hash;
		batch.blend_hash = data.blend_hash;
		batch.sampler_hash = data.sampler_hash;
		batches[batch_id] = batch;
	}

	batches.at(batch_id).elements.push_back(element);
}

void SpriteRenderer::DrawBatchObject(BatchObject & object, std::unordered_map<size_t, Batch> &batches)
{
	glBindVertexArray(object.vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, instance_buffer_);

	for (auto it = batches.begin(); it != batches.end(); ++it)
	{
		
		// Especially for isometric tiles we need to draw higher y-coordinates first
		std::sort(it->second.elements.begin(), it->second.elements.end(),
			[](BatchElement &a, BatchElement &b) { return a.sprite_transform[3][1] > b.sprite_transform[3][1]; });

		// Set blend mode for batch
		resource_core_.GetBlendCache().GetFromHash(it->second.blend_hash)->Set();

		// Set sampler and texture if present
		if (it->second.sampler_hash && it->second.texture_hash)
		{
			resource_core_.GetSamplerCache().GetFromHash(it->second.sampler_hash)->Bind(0);
			resource_core_.GetTextureCache().GetFromHash(it->second.texture_hash)->Bind(0);
		}

		// Re-upload subdata for instance buffer
		size_t instance_size = it->second.elements.size() * sizeof(BatchElement);
		glInvalidateBufferSubData(GL_ARRAY_BUFFER, 0, instance_size);
		glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, (GLsizei)instance_size, &it->second.elements[0]);
	
		// Draw all sprites for the batch
		glDrawElementsInstanced(GL_TRIANGLES,
			(GLsizei)object.num_indices, GL_UNSIGNED_INT, 0,
			(GLsizei)it->second.elements.size());
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
