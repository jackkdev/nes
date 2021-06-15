//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_QUAD_H_
#define NES_NES_SRC_RENDER_QUAD_H_

#include <glm/glm.hpp>

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

#include "../util/types.h"

namespace nes {

// Represents a render-able quad.
class Quad {
 public:
	struct Vertex {
		glm::vec2 position;
		glm::vec3 color;
	};

 public:
	Quad(i32 x, i32 y, i32 width, i32 height);
	~Quad() = default;

	void Draw() const;

 private:
	i32 x_ = 0, y_ = 0, width_ = 0, height_ = 0;

 private:
	VertexBuffer vertex_buffer_;
	IndexBuffer index_buffer_;
	VertexArray vertex_array_;
};

}

#endif //NES_NES_SRC_RENDER_QUAD_H_
