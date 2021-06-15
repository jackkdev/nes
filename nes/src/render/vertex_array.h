//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_VERTEX_ARRAY_H_
#define NES_NES_SRC_RENDER_VERTEX_ARRAY_H_

#include "../util/types.h"

#include <glad/gl.h>

#include <vector>

namespace nes {

class VertexArray {
 public:
	struct Layout {
		i32 size;
		i32 type;
		bool normalized;
	};

 public:
	VertexArray();
	~VertexArray();

	void SetLayout(const std::vector<Layout> &layouts) const;
	void Bind() const;

 private:
	u32 vertex_array_id_ = 0;
};

}

#endif //NES_NES_SRC_RENDER_VERTEX_ARRAY_H_
