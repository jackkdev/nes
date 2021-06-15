//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

// GLM breaks shit.
#pragma warning(disable : 4103)

#include "render/window.h"
#include "render/shader.h"
#include "render/quad.h"

using namespace nes;

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cstdlib>
#include <fstream>

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;
};

std::string GetShaderSource(const std::string &path) {
	std::ifstream stream(path);

	std::string contents;
	std::string buffer;
	while (std::getline(stream, buffer)) {
		contents += buffer + "\n";
	}

	return contents;
}

int main(int argc, char **argv) {
	Window::Options options = {
			.title = "Hello, world!",
			.width = 800,
			.height = 600,
	};
	Window window(options);

	std::vector<Vertex> vertices = {
			{
				glm::vec2(0.0f, 0.0f),
				glm::vec3(1.0f, 0.0f, 0.0f),
			},
			{
				glm::vec2(100.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
			},
			{
				glm::vec2(100.0f, 100.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
			},
	};

	auto *shader = new Shader();
	shader->Load(GetShaderSource("res/shaders/basic.vert"), GetShaderSource("res/shaders/basic.frag"));
	shader->Bind();

	auto model = glm::mat4(1.0f);
	auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

	shader->SetMatrix4f("model", model);
	shader->SetMatrix4f("projection", projection);

	auto *quad = new Quad(0, 0, 100, 100);

	while (!window.ShouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		quad->Draw();

		Window::PollEvents();
		window.SwapBuffers();
	}

	delete shader;
	delete quad;

	return EXIT_SUCCESS;
}