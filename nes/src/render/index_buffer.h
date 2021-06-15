//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_INDEX_BUFFER_H_
#define NES_NES_SRC_RENDER_INDEX_BUFFER_H_

#include "../util/types.h"

#include <glad/gl.h>

namespace nes {

class IndexBuffer {
 public:
	IndexBuffer();
	~IndexBuffer();

	void SetData(void *data, i32 data_size, i32 draw_mode) const;
	void Bind() const;

 private:
	u32 index_buffer_id_ = 0;
};

}

#endif //NES_NES_SRC_RENDER_INDEX_BUFFER_H_
