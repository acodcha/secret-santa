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

#include "../../source/Randomizer/Configuration.hpp"

#include <gtest/gtest.h>

namespace SecretSanta::Randomizer {

namespace {

TEST(RandomizerConfiguration, Constructor) {
  const Configuration configuration{"../test/Randomizer/configuration.yaml"};
  EXPECT_EQ(configuration.MessageSubject(), "Secret Santa Gift Exchange 2023");
  EXPECT_FALSE(configuration.MessageBody().empty());
  EXPECT_EQ(configuration.Participants().size(), 3);
  ASSERT_NE(configuration.Participants().find("Alice Smith"),
            configuration.Participants().cend());
  EXPECT_EQ(configuration.Participants().find("Alice Smith")->second.Name(),
            "Alice Smith");
}

TEST(RandomizerConfiguration, DefaultConstructor) {
  const Configuration configuration;
  EXPECT_EQ(configuration.MessageSubject(), "Secret Santa Gift Exchange");
  EXPECT_EQ(configuration.MessageBody(),
            "Hello!\n\n"
            "You are receiving this message because you opted to participate "
            "in a Secret Santa gift exchange!");
}

}  // namespace

}  // namespace SecretSanta::Randomizer
