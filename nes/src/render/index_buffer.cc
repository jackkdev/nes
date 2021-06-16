//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "index_buffer.h"

namespace nes {

IndexBuffer::IndexBuffer() {
  glCreateBuffers(1, &index_buffer_id_);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &index_buffer_id_);
}

void IndexBuffer::SetData(void *data, i32 data_size, i32 draw_mode) const {
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, draw_mode);
}

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
}

}