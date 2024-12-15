// Copyright © 2023-2024 Alexandre Coderre-Chabot
//
// This file is part of Secret Santa, a simple C++ utility that organizes a "Secret Santa" gift
// exchange event!
//
// Secret Santa is hosted at:
//     https://github.com/acodcha/secret-santa
//
// Secret Santa is licensed under the MIT License:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included in all copies or
//     substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//     BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//     NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM
//     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "../source/Matchings.hpp"

#include <gtest/gtest.h>

#include "CreateSampleParticipant.hpp"

namespace {

TEST(Matchings, ComparisonOperators) {
  const SecretSanta::Matchings first{std::set<SecretSanta::Participant>{
    SecretSanta::Participant{SecretSanta::CreateSampleParticipantA()}}};
  const SecretSanta::Matchings second{SecretSanta::CreateSampleParticipants()};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Matchings, ConstructorFromNoParticipants) {
  const SecretSanta::Matchings matchings{std::set<SecretSanta::Participant>()};
  EXPECT_TRUE(matchings.GiftersToGiftees().empty());
}

TEST(Matchings, ConstructorFromOneParticipant) {
  const SecretSanta::Matchings matchings{std::set<SecretSanta::Participant>{
    SecretSanta::Participant{SecretSanta::CreateSampleParticipantA()}}};
  EXPECT_EQ(matchings.GiftersToGiftees().size(), 1);
  EXPECT_NE(matchings.GiftersToGiftees().find("Alice Smith"), matchings.GiftersToGiftees().cend());
  EXPECT_EQ(matchings.GiftersToGiftees().at("Alice Smith"), "Alice Smith");
}

TEST(Matchings, ConstructorFromThreeParticipants) {
  const SecretSanta::Matchings matchings{SecretSanta::CreateSampleParticipants()};
  EXPECT_EQ(matchings.GiftersToGiftees().size(), 3);
  for (const std::pair<const std::string, std::string>& gifter_and_giftee :
       matchings.GiftersToGiftees()) {
    EXPECT_NE(gifter_and_giftee.first, gifter_and_giftee.second);
  }
}

TEST(Matchings, DefaultConstructor) {
  const SecretSanta::Matchings matchings;
  EXPECT_TRUE(matchings.GiftersToGiftees().empty());
}

TEST(Matchings, ConstructorFromYamlFile) {
  const SecretSanta::Matchings first{SecretSanta::CreateSampleParticipants()};
  const std::filesystem::path path = "matchings.yaml";
  first.Write(path);
  const SecretSanta::Matchings second{path};
  EXPECT_EQ(first, second);
}

}  // namespace
