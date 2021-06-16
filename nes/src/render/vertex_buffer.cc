//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "vertex_buffer.h"

namespace nes {

VertexBuffer::VertexBuffer() {
  glCreateBuffers(1, &buffer_id_);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &buffer_id_);
}

void VertexBuffer::SetData(void *vertices, i32 vertices_size, i32 draw_mode) const {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, draw_mode);
}

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
}

}