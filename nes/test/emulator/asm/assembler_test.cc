//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include <gtest/gtest.h>
#include "../../../src/emulator/asm/assembler.h"

using namespace nes;

TEST(Assembler, Tokenizer) {
  Assembler assembler;

  using TT = Assembler::TokenType;
  Assembler::Token expected_tokens[] = {
      {
        .type = TT::LITERAL,
        .data = "lda",
      },
      {
        .type = TT::HEXADECIMAL_NUMBER,
        .data = "AA",
      },
      {
        .type = TT::LITERAL,
        .data = "sta",
      },
      {
        .type = TT::HEXADECIMAL_ADDRESS,
        .data = "0000",
      },
      {
        .type = TT::LITERAL,
        .data = "ldx",
      },
      {
        .type = TT::HEXADECIMAL_NUMBER,
        .data = "FA",
      },
      {
        .type = TT::LITERAL,
        .data = "stx",
      },
      {
        .type = TT::PARENTHESES,
        .data = "(",
      },
      {
        .type = TT::HEXADECIMAL_ADDRESS,
        .data = "00",
      },
      {
        .type = TT::COMMA,
        .data = ",",
      },
      {
        .type = TT::LITERAL,
        .data = "X",
      },
      {
        .type = TT::PARENTHESES,
        .data = ")",
      },
  };

  auto tokens = assembler.Tokenize("lda #$AA\nsta $0000\nldx #$FA\nstx ($00,X)");
  for (int i = 0; i < tokens.size(); i++) {
    auto expected = expected_tokens[i];
    auto found = tokens[i];

    std::cout << "[          ] Expected Token: " << Assembler::TypeToString(expected.type) << std::endl;
    std::cout << "[          ] Token: " << Assembler::TypeToString(found.type) << std::endl;

    EXPECT_STREQ(found.data.c_str(), expected.data.c_str());
    EXPECT_EQ(found.type, expected.type);
  }
}