//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "shader.h"

namespace nes {

Shader::Shader() = default;

Shader::~Shader() {
  glDeleteProgram(program_id_);
  glDeleteShader(vertex_id_);
  glDeleteShader(fragment_id_);
}

void Shader::Load(const std::string &vertex_source, const std::string &fragment_source) {
  Compile(GL_VERTEX_SHADER, vertex_source, &vertex_id_);
  Compile(GL_FRAGMENT_SHADER, fragment_source, &fragment_id_);

  program_id_ = glCreateProgram();

  glAttachShader(program_id_, vertex_id_);
  glAttachShader(program_id_, fragment_id_);

  // TODO: Test if the program links successfully.
  glLinkProgram(program_id_);
}

void Shader::Bind() const {
  glUseProgram(program_id_);
}

void Shader::Compile(i32 type, const std::string &source, u32 *out) {
  auto id = glCreateShader(type);
  auto str = source.c_str();

  // Attach the source, and compile the shader.
  glShaderSource(id, 1, &str, nullptr);
  glCompileShader(id);

  // Check the status of the shader.
  i32 is_compiled = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled != GL_TRUE) {
    GLsizei log_length = 0;
    GLchar message[1024];

    glGetShaderInfoLog(id, 1024, &log_length, message);
    printf("Error: %s\n", message);
    exit(1);
  }

  *out = id;
}

void Shader::SetMatrix4f(const std::string &name, const glm::mat4 &matrix) const {
  glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

}