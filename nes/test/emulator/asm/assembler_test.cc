//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include <gtest/gtest.h>
#include "../../../src/emulator/asm/assembler.h"

using namespace nes;

TEST(Assembler, Tokenizer) {
  using Type = Assembler::TokenType;
  struct TestCase {
    std::string input;
    std::vector<Assembler::Token> tokens;
  };

  std::vector<TestCase> test_cases = {
      {
          .input = "lda #$AA\nsta $0000\nldx #$FA\nstx ($00,X)",
          .tokens = {
              {
                  .type = Type::LITERAL,
                  .data = "lda",
              },
              {
                  .type = Type::HEXADECIMAL_NUMBER,
                  .data = "AA",
              },
              {
                  .type = Type::LITERAL,
                  .data = "sta",
              },
              {
                  .type = Type::HEXADECIMAL_ADDRESS,
                  .data = "0000",
              },
              {
                  .type = Type::LITERAL,
                  .data = "ldx",
              },
              {
                  .type = Type::HEXADECIMAL_NUMBER,
                  .data = "FA",
              },
              {
                  .type = Type::LITERAL,
                  .data = "stx",
              },
              {
                  .type = Type::PARENTHESES,
                  .data = "(",
              },
              {
                  .type = Type::HEXADECIMAL_ADDRESS,
                  .data = "00",
              },
              {
                  .type = Type::COMMA,
                  .data = ",",
              },
              {
                  .type = Type::LITERAL,
                  .data = "X",
              },
              {
                  .type = Type::PARENTHESES,
                  .data = ")",
              },
          },
      },
      {
          .input = "asl\nsta temp\nasl\nasl\nclc\nadc temp\nrts",
          .tokens = {
              {
                  .type = Type::LITERAL,
                  .data = "asl",
              },
              {
                  .type = Type::LITERAL,
                  .data = "sta",
              },
              {
                  .type = Type::LITERAL,
                  .data = "temp",
              },
              {
                  .type = Type::LITERAL,
                  .data = "asl",
              },
              {
                  .type = Type::LITERAL,
                  .data = "asl",
              },
              {
                  .type = Type::LITERAL,
                  .data = "clc",
              },
              {
                  .type = Type::LITERAL,
                  .data = "adc",
              },
              {
                  .type = Type::LITERAL,
                  .data = "temp",
              },
              {
                  .type = Type::LITERAL,
                  .data = "rts",
              },
          }
      },
  };

  Assembler assembler;
  for (auto &test_case : test_cases) {
    auto returned_tokens = assembler.Tokenize(test_case.input);

    if (returned_tokens.size() != test_case.tokens.size())
      FAIL() << "returned_tokens.size() != test_case.tokens.size()";

    for (int i = 0; i < returned_tokens.size(); i++) {
      auto expected = returned_tokens[i];
      auto found = test_case.tokens[i];

      EXPECT_STREQ(found.data.c_str(), expected.data.c_str()) << "found.data != expected.data";
      EXPECT_EQ(found.type, expected.type) << "found.type != << expected.type";
    }
  }
}