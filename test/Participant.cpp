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

#include "../source/Participant.hpp"

#include <gtest/gtest.h>

#include "CreateSampleParticipant.hpp"

namespace SecretSanta {

namespace {

TEST(Participant, ComparisonOperators) {
  const Participant first{CreateSampleParticipantA()};
  const Participant second{CreateSampleParticipantB()};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Participant, Constructor) {
  const Participant participant{CreateSampleParticipantA()};
  EXPECT_EQ(participant.Name(), "Alice Smith");
  EXPECT_EQ(participant.Email(), "alice.smith@gmail.com");
  EXPECT_EQ(
      participant.Address(), "123 First Ave, Apt 1, Townsville, CA 91234 USA");
  EXPECT_EQ(participant.Instructions(),
            "Leave the package with the doorman in the lobby.");
}

TEST(Participant, CopyAssignmentOperator) {
  const Participant first{CreateSampleParticipantA()};
  Participant second = CreateSampleParticipantB();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Participant, CopyConstructor) {
  const Participant first{CreateSampleParticipantA()};
  const Participant second{first};
  EXPECT_EQ(second, first);
}

TEST(Participant, DefaultConstructor) {
  const Participant participant;
  EXPECT_TRUE(participant.Name().empty());
  EXPECT_TRUE(participant.Email().empty());
  EXPECT_TRUE(participant.Address().empty());
  EXPECT_TRUE(participant.Instructions().empty());
}

TEST(Participant, Hash) {
  const Participant first{CreateSampleParticipantA()};
  const Participant second{CreateSampleParticipantB()};
  std::hash<Participant> hash;
  EXPECT_NE(hash(first), hash(second));
}

TEST(Participant, MoveAssignmentOperator) {
  Participant first{CreateSampleParticipantA()};
  Participant second = CreateSampleParticipantB();
  second = std::move(first);
  EXPECT_EQ(second, Participant(CreateSampleParticipantA()));
}

TEST(Participant, MoveConstructor) {
  Participant first{CreateSampleParticipantA()};
  Participant second{std::move(first)};
  EXPECT_EQ(second, Participant(CreateSampleParticipantA()));
}

TEST(Participant, Print) {
  const Participant participant{CreateSampleParticipantA()};
  EXPECT_EQ(participant.Print(),
            "Alice Smith (email: alice.smith@gmail.com; address: 123 First "
            "Ave, Apt 1, Townsville, CA 91234 USA; instructions: Leave the "
            "package with the doorman in the lobby.)");
}

TEST(Participant, Stream) {
  const Participant participant{CreateSampleParticipantA()};
  std::stringstream stream;
  stream << participant;
  EXPECT_EQ(stream.str(),
            "Alice Smith (email: alice.smith@gmail.com; address: 123 First "
            "Ave, Apt 1, Townsville, CA 91234 USA; instructions: Leave the "
            "package with the doorman in the lobby.)");
}

TEST(Participant, YAML) {
  const Participant participant{CreateSampleParticipantA()};
  const YAML::Node node = participant.YAML();
  ASSERT_TRUE(node.IsMap());
  ASSERT_EQ(node.size(), 1);
  for (const YAML::detail::iterator_value& element : node) {
    ASSERT_EQ(element.first.as<std::string>(), "Alice Smith");
    ASSERT_TRUE(element.second["email"]);
    ASSERT_EQ(
        element.second["email"].as<std::string>(), "alice.smith@gmail.com");
    ASSERT_TRUE(element.second["address"]);
    ASSERT_EQ(element.second["address"].as<std::string>(),
              "123 First Ave, Apt 1, Townsville, CA 91234 USA");
    ASSERT_TRUE(element.second["instructions"]);
    ASSERT_EQ(element.second["instructions"].as<std::string>(),
              "Leave the package with the doorman in the lobby.");
  }
}

}  // namespace

}  // namespace SecretSanta
