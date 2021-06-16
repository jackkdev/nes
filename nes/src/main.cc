//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#pragma warning(disable : 4103)

#include "emulator/asm/assembler.h"
using namespace nes;

#include <fstream>
#include <cstdlib>

int main(int argc, char **argv) {
	std::ifstream stream("test.asm");
	std::string buffer;
	std::string source;
	while (std::getline(stream, buffer))
		source += buffer + "\n";


	Assembler assembler;
	auto tokens = assembler.Tokenize("FF00Q:$(),#");
	for (auto &token : tokens)
		printf("[%s: %s]\n", Assembler::TypeToString(token.type).c_str(), token.data.c_str());

	return EXIT_SUCCESS;
}