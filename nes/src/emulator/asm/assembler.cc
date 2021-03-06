//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "../../util/types.h"
#include "assembler.h"

#include <iostream>
#include <map>

namespace nes {

enum class TokenizerState {
  START,
  LITERAL,
  HEXADECIMAL_NUMBER,
  DECIMAL_NUMBER,
  COMMENT,
  END,
};

std::vector<Assembler::Token> Assembler::Tokenize(const std::string &source) {
  // Validation strings for literals.
  static std::string s_literal_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
  static std::string s_literal_first_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Validation string for hexadecimal numbers.
  static std::string s_hexadecimal_characters = "abcdefABCDEF0123456789";

  // Validation string for decimal numbers.
  static std::string s_decimal_characters = "0123456789";

  // Single character validation map.
  static std::map<char, TokenType> s_single_character_map = {
      std::make_pair(':', TokenType::COLLEN),
      std::make_pair('(', TokenType::PARENTHESES),
      std::make_pair(')', TokenType::PARENTHESES),
      std::make_pair(',', TokenType::COMMA),
  };

  // Container to store tokens generated from the source.
  std::vector<Assembler::Token> tokens;

  // The current "state" of the tokenizer.
  auto state = TokenizerState::START;

  bool eof = false;

  i32 index = 0;
  Token token = {};

  while (!eof) {
    if (index >= source.length())
      state = TokenizerState::END;

    // Every iteration we'll read the state value, and modify the current token based on that.
    switch (state) {
      case TokenizerState::START: {
        // Read in the current source character.
        char input = source[index];

        // Literal check.
        if (s_literal_first_characters.find(input) != std::string::npos) {
          token.type = TokenType::LITERAL;
          token.data += input;

          state = TokenizerState::LITERAL;
          index++;

          break;
        }

        // Immediate value check.
        if (input == '#') {
          // Hexadecimal immediate value.
          if (source[index + 1] == '$') {
            token.type = TokenType::HEXADECIMAL_NUMBER;
            state = TokenizerState::HEXADECIMAL_NUMBER;
            index += 2;

            break;
          }

          // Decimal immediate value.
          token.type = TokenType::DECIMAL_NUMBER;
          state = TokenizerState::DECIMAL_NUMBER;
          index++;

          break;
        }

        // Hexadecimal address check.
        if (source[index] == '$') {
          token.type = TokenType::HEXADECIMAL_ADDRESS;

          state = TokenizerState::HEXADECIMAL_NUMBER;
          index ++;

          break;
        }

        // Comment check.
        if (input == ';') {
          token.type = TokenType::COMMENT;
          token.data += input;

          state = TokenizerState::COMMENT;
          index++;

          break;
        }

        // Character map validation check.
        if (s_single_character_map.contains(input)) {
          token.type = s_single_character_map[input];
          token.data = input;

          state = TokenizerState::END;
          index++;

          break;
        }

        // Finally, if nothing happens we'll just skip the character.
        index++;

        break;
      }

      case TokenizerState::LITERAL: {
        char input = source[index];

        // Save the token if the character isn't valid.
        if (s_literal_characters.find(input) == std::string::npos) {
          state = TokenizerState::END;
          break;
        }

        token.data += input;
        index++;

        break;
      };

      case TokenizerState::HEXADECIMAL_NUMBER: {
        char input = source[index];

        // Check if the input character exists within the hexadecimal validation characters.
        if (s_hexadecimal_characters.find(input) == std::string::npos) {
          state = TokenizerState::END;
          break;
        }

        // Add the input to the current token, and continue.
        token.data += input;
        index++;

        break;
      }

      case TokenizerState::DECIMAL_NUMBER: {
        char input = source[index];

        // Check if this is still a valid decimal number.
        if (s_decimal_characters.find(input) == std::string::npos) {
          state = TokenizerState::END;
          break;
        }

        token.data += input;
        index++;

        break;
      }

      case TokenizerState::COMMENT: {
        char input = source[index];

        if (input == '\n') {
          state = TokenizerState::END;
          break;
        }

        token.data += input;
        index++;

        break;
      }

      case TokenizerState::END: {
        // First we need to check if there even is a token to save.
        if (!token.data.empty()) {
          tokens.push_back(token);
          token.data = "";
        }

        // Again, perform the sanity check to exit the loop if we've read every character.
        if (index >= source.length())
          eof = true;

        // This won't matter if the index exceeds the source length.
        state = TokenizerState::START;

        break;
      }
    }
  }

  return tokens;
}

std::vector<u8> Assembler::Parse(const std::vector<Token> &tokens) {
  std::vector<u8> bytes;



  return bytes;
}

}