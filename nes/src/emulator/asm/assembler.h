//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

// Assembler Stages:
// 1. Tokenize -> Turn everything into tokens for easy syntax validation.
// 2. Syntax Validation -> Validate the syntax (aka. check that all addressing modes make sense).
// 3. Output -> Take each token and convert into a binary representation.

#ifndef NES_NES_SRC_EMULATOR_ASSEMBLER_H_
#define NES_NES_SRC_EMULATOR_ASSEMBLER_H_

#include "../../util/types.h"

#include <string>
#include <sstream>

#include <vector>

namespace nes {

class Assembler {
 public:
	enum class TokenType {
		LITERAL,
		DECIMAL_NUMBER,
		HEXADECIMAL_NUMBER,
		COMMENT,
		COLLEN,
		DOLLAR_SIGN,
		PARENTHESES,
		COMMA,
		HASHTAG,
	};

	struct Token {
		TokenType type;
		std::string data;
	};

 public:
	Assembler() = default;
	~Assembler() = default;

	std::vector<Token> Tokenize(const std::string &source);

	std::vector<u8> Parse(const std::vector<Token> &tokens);

	static std::string TypeToString(TokenType type) {
		switch (type) {
			case TokenType::LITERAL:
				return "LITERAL";
			case TokenType::COLLEN:
				return "COLLEN";
			case TokenType::DOLLAR_SIGN:
				return "DOLLAR_SIGN";
			case TokenType::PARENTHESES:
				return "PARENTHESES";
			case TokenType::COMMA:
				return "COMMA";
			case TokenType::HASHTAG:
				return "HASHTAG";
			case TokenType::COMMENT:
				return "COMMENT";
			case TokenType::DECIMAL_NUMBER:
				return "DECIMAL_NUMBER";
			case TokenType::HEXADECIMAL_NUMBER:
				return "HEXADECIMAL_NUMBER";
		}

		return "N/A";
	}
};

}

#endif //NES_NES_SRC_EMULATOR_ASSEMBLER_H_
