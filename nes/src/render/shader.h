//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_RENDER_SHADER_H_
#define NES_NES_SRC_RENDER_SHADER_H_

#include "../util/types.h"

#include <glad/gl.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace nes {

class Shader {
 public:
	explicit Shader();
	~Shader();

	// Takes the shader source, and compiles it using OpenGL. A new program is automatically created with
	// the newly compiled shaders attached.
	void Load(const std::string &vertex_source, const std::string &fragment_source);

	// Binds the program with through OpenGL.
	void Bind() const;

	void SetMatrix4f(const std::string &name, const glm::mat4 &matrix) const;

 private:
	static void Compile(i32 type, const std::string &source, u32 *out);

 private:
	u32 vertex_id_ = 0, fragment_id_ = 0, program_id_ = 0;
};

}

#endif //NES_NES_SRC_RENDER_SHADER_H_
