//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "vertex_array.h"

namespace nes {

VertexArray::VertexArray() {
	glCreateVertexArrays(1, &vertex_array_id_);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vertex_array_id_);
}

static i32 GetSizeFromType(i32 type) {
	switch (type) {
		case GL_FLOAT:
		case GL_INT:
		case GL_UNSIGNED_INT:
			return 4;

		default:
			return 0;
	}
}

void VertexArray::SetLayout(const std::vector<Layout> &layouts) const {
	Bind();

	i32 index = 0;
	i32 stride = 0;
	for (auto &layout : layouts)
		stride += GetSizeFromType(layout.type) * layout.size;

	i64 offset = 0;
	for (auto &layout : layouts) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index++, layout.size, layout.type, layout.normalized, stride, reinterpret_cast<void *>(offset));

		offset += GetSizeFromType(layout.type) * layout.size;
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(vertex_array_id_);
}

}