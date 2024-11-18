// Copyright © 2023-2024 Alexandre Coderre-Chabot
//
// This file is part of Secret Santa, a simple C++ utility that organizes a "Secret Santa" gift
// exchange event!
//
// Secret Santa is hosted at:
//     https://github.com/acodcha/phq
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

#include "../source/Participant.hpp"

#include <gtest/gtest.h>

#include "CreateSampleParticipant.hpp"

namespace {

TEST(Participant, ComparisonOperators) {
  const SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  const SecretSanta::Participant second{SecretSanta::CreateSampleParticipantB()};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Participant, ConstructorFromName) {
  const SecretSanta::Participant participant{"Alice Smith"};
  EXPECT_EQ(participant.Name(), "Alice Smith");
  EXPECT_TRUE(participant.Email().empty());
  EXPECT_TRUE(participant.Address().empty());
  EXPECT_TRUE(participant.Instructions().empty());
}

TEST(Participant, ConstructorFromYamlNode) {
  const SecretSanta::Participant participant{SecretSanta::CreateSampleParticipantA()};
  EXPECT_EQ(participant.Name(), "Alice Smith");
  EXPECT_EQ(participant.Email(), "alice.smith@gmail.com");
  EXPECT_EQ(participant.Address(), "123 First Ave, Apt 1, Townsville, CA 91234 USA");
  EXPECT_EQ(participant.Instructions(), "Leave the package with the doorman in the lobby.");
}

TEST(Participant, CopyAssignmentOperator) {
  const SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  SecretSanta::Participant second =
      SecretSanta::Participant{SecretSanta::CreateSampleParticipantB()};
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Participant, CopyConstructor) {
  const SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  const SecretSanta::Participant second{first};
  EXPECT_EQ(second, first);
}

TEST(Participant, DefaultConstructor) {
  const SecretSanta::Participant participant;
  EXPECT_TRUE(participant.Name().empty());
  EXPECT_TRUE(participant.Email().empty());
  EXPECT_TRUE(participant.Address().empty());
  EXPECT_TRUE(participant.Instructions().empty());
}

TEST(Participant, Hash) {
  const SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  const SecretSanta::Participant second{SecretSanta::CreateSampleParticipantB()};
  std::hash<SecretSanta::Participant> hash;
  EXPECT_NE(hash(first), hash(second));
}

TEST(Participant, MoveAssignmentOperator) {
  SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  SecretSanta::Participant second{SecretSanta::CreateSampleParticipantB()};
  second = std::move(first);
  EXPECT_EQ(second, SecretSanta::Participant(SecretSanta::CreateSampleParticipantA()));
}

TEST(Participant, MoveConstructor) {
  SecretSanta::Participant first{SecretSanta::CreateSampleParticipantA()};
  SecretSanta::Participant second{std::move(first)};
  EXPECT_EQ(second, SecretSanta::Participant(SecretSanta::CreateSampleParticipantA()));
}

TEST(Participant, Print) {
  const SecretSanta::Participant participant{SecretSanta::CreateSampleParticipantA()};
  EXPECT_EQ(participant.Print(),
            "Alice Smith (email: alice.smith@gmail.com; address: 123 First Ave, Apt 1, Townsville, "
            "CA 91234 USA; instructions: Leave the package with the doorman in the lobby.)");
}

TEST(Participant, Stream) {
  const SecretSanta::Participant participant{SecretSanta::CreateSampleParticipantA()};
  std::stringstream stream;
  stream << participant;
  EXPECT_EQ(stream.str(),
            "Alice Smith (email: alice.smith@gmail.com; address: 123 First Ave, Apt 1, Townsville, "
            "CA 91234 USA; instructions: Leave the package with the doorman in the lobby.)");
}

TEST(Participant, YAML) {
  const SecretSanta::Participant participant{SecretSanta::CreateSampleParticipantA()};
  const YAML::Node node{participant.YAML()};
  ASSERT_TRUE(node.IsMap());
  ASSERT_EQ(node.size(), 1);
  for (const YAML::detail::iterator_value& element : node) {
    ASSERT_EQ(element.first.as<std::string>(), "Alice Smith");
    ASSERT_TRUE(element.second["email"]);
    ASSERT_EQ(element.second["email"].as<std::string>(), "alice.smith@gmail.com");
    ASSERT_TRUE(element.second["address"]);
    ASSERT_EQ(element.second["address"].as<std::string>(),
              "123 First Ave, Apt 1, Townsville, CA 91234 USA");
    ASSERT_TRUE(element.second["instructions"]);
    ASSERT_EQ(element.second["instructions"].as<std::string>(),
              "Leave the package with the doorman in the lobby.");
  }
}

}  // namespace
