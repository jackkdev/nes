//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_VERTEX_BUFFER_H_
#define NES_NES_SRC_RENDER_VERTEX_BUFFER_H_

#include "../util/types.h"

#include <glad/gl.h>

#include <vector>

namespace nes {

class VertexBuffer {
 public:
  VertexBuffer();
  ~VertexBuffer();

  void SetData(void *vertices, i32 vertices_size, i32 draw_mode) const;
  void Bind() const;

 private:
  u32 buffer_id_ = 0;
};

}

#endif //NES_NES_SRC_RENDER_VERTEX_BUFFER_H_
