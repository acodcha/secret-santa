// Copyright © 2023-2025, Alexandre Coderre-Chabot.
//
// This file is part of Secret Santa, a software utility for organizing a "Secret Santa" gift
// exchange event! Secret Santa is hosted at: https://github.com/acodcha/secret-santa
//
// Secret Santa is licensed under the MIT License: https://mit-license.org
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

#include "../source/Emailer.hpp"

#include <gtest/gtest.h>

#include "CreateSampleParticipant.hpp"

namespace {

TEST(Emailer, ComposeFullMessageBody) {
  const SecretSanta::Participant gifter{SecretSanta::CreateSampleParticipantA()};
  const SecretSanta::Participant giftee{SecretSanta::CreateSampleParticipantB()};

  const std::string main_message_body{
            "You are receiving this message because you opted to participate in a Secret Santa "
            "gift exchange!"};

  const std::string result{SecretSanta::ComposeFullMessageBody(
      SecretSanta::Participant{SecretSanta::CreateSampleParticipantA()},
      SecretSanta::Participant{SecretSanta::CreateSampleParticipantB()}, main_message_body)};

  EXPECT_EQ(result,
            "Hello Alice Smith,\n\nYou are receiving this message because you opted to participate "
            "in a Secret Santa gift exchange!\n\nYour giftee is: Bob Johnson\n\nMail to:\n\nBob "
            "Johnson SECRET SANTA\n456 Second St, Apt 2, Villagetown, CA 92345 USA\n\nThank you!");
}

TEST(Emailer, ComposeCommand) {
  const SecretSanta::Participant gifter{SecretSanta::CreateSampleParticipantA()};
  const std::string message_subject{"My Message Subject"};
  const std::string message_body{"My Message Body"};

  const std::string command{SecretSanta::ComposeCommand(gifter, message_subject, message_body)};

  EXPECT_EQ(
      command,
      "echo \"My Message Body\" | s-nail --subject \"My Message Subject\" alice.smith@gmail.com");
}

}  // namespace
