//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "quad.h"

namespace nes {

Quad::Quad(i32 x, i32 y, i32 width, i32 height) {
	auto white = glm::vec3(1.0f);
	std::vector<Vertex> vertices = {
			{
					glm::vec2(x, y),
					white,
			},
			{
					glm::vec2(x + width, y),
					white,
			},
			{
					glm::vec2(x, y + height),
					white,
			},
			{
					glm::vec2(x + width, y + height),
					white,
			}
	};

	vertex_buffer_.SetData(vertices.data(), (4 * (2 + 3)) * sizeof(float), GL_DYNAMIC_DRAW);
	vertex_array_.SetLayout(
			{
					{
							.size = 2,
							.type = GL_FLOAT,
							.normalized = false,
					},
					{
							.size = 3,
							.type = GL_FLOAT,
							.normalized = false,
					}
			}
	);

	u32 indices[] = {
			0, 1, 2,
			1, 2, 3,
	};

	index_buffer_.SetData(indices, 6 * sizeof(u32), GL_DYNAMIC_DRAW);
}

void Quad::Draw() const {
	vertex_array_.Bind();
	index_buffer_.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

}