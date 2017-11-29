#include "render_quad.h"

using namespace core;

RenderQuad::RenderQuad()
{
	size_t num_vertices = GetNumQuadVertices();
	size_t num_indices = GetNumQuadIndices();

	auto vertex_size = sizeof(GetQuadVertices()[0]);
	auto index_size = sizeof(GetQuadIndices()[0]);
	auto vertices_size = num_vertices * vertex_size;
	auto indices_size = num_indices * index_size;

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, GetQuadVertices(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, GetQuadIndices(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLint attrib_index = 0;
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

	// Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (GLsizei)vertex_size, 0);
	glVertexAttribDivisor(0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RenderQuad::~RenderQuad()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}

void RenderQuad::Begin() const
{
	glBindVertexArray(vao_);
}

void RenderQuad::End() const
{
	glBindVertexArray(0);
}

void RenderQuad::DrawElements() const
{
	glDrawElements(GL_TRIANGLES, GetNumQuadIndices(), GL_UNSIGNED_INT, 0);
}
