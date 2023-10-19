// Copyright © 2023 Alexandre Coderre-Chabot
//
// This file is licensed under the MIT license. For more information, visit:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included
//     in all copies or substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//     OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
//     NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//     OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//     USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This file was originally obtained from:
//     https://github.com/acodcha/secret-santa

#include "../source/Matchings.hpp"

#include <gtest/gtest.h>

#include "CreateSampleParticipant.hpp"

namespace SecretSanta {

namespace {

std::set<Participant> CreateSampleParticipants() {
  std::set<Participant> participants;
  participants.emplace(CreateSampleParticipantA());
  participants.emplace(CreateSampleParticipantB());
  participants.emplace(CreateSampleParticipantC());
  return participants;
}

TEST(Matchings, ComparisonOperators) {
  const Matchings first{{CreateSampleParticipantA()}};
  const Matchings second{CreateSampleParticipants()};
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
  const Matchings matchings{std::set<Participant>()};
  EXPECT_TRUE(matchings.GiftersToGiftees().empty());
}

TEST(Matchings, ConstructorFromOneParticipant) {
  const Matchings matchings{{CreateSampleParticipantA()}};
  EXPECT_EQ(matchings.GiftersToGiftees().size(), 1);
  EXPECT_NE(matchings.GiftersToGiftees().find("Alice Smith"),
            matchings.GiftersToGiftees().cend());
  EXPECT_EQ(matchings.GiftersToGiftees().at("Alice Smith"), "Alice Smith");
}

TEST(Matchings, ConstructorFromThreeParticipants) {
  const Matchings matchings{CreateSampleParticipants()};
  EXPECT_EQ(matchings.GiftersToGiftees().size(), 3);
  for (const std::pair<const std::string, std::string>& gifter_and_giftee :
       matchings.GiftersToGiftees()) {
    EXPECT_NE(gifter_and_giftee.first, gifter_and_giftee.second);
  }
}

TEST(Matchings, DefaultConstructor) {
  const Matchings matchings;
  EXPECT_TRUE(matchings.GiftersToGiftees().empty());
}

TEST(Matchings, ConstructorFromYamlFile) {
  const Matchings first{CreateSampleParticipants()};
  const std::filesystem::path path = "matchings.yaml";
  first.Write(path);
  const Matchings second{path};
  EXPECT_EQ(first, second);
}

}  // namespace

}  // namespace SecretSanta
