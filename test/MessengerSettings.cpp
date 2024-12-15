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

#include "../source/MessengerSettings.hpp"

#include <gtest/gtest.h>

namespace {

TEST(MessengerSettings, Constructor) {
  char program[] = "bin/secret-santa";

  char configuration_key[] = "--configuration";
  char configuration_value[] = "path/to/some/directory/configuration.yaml";

  char matchings_key[] = "--matchings";
  char matchings_value[] = "path/to/some/directory/matchings.yaml";

  int argc{5};

  char* argv[] = {
    program, configuration_key, configuration_value, matchings_key, matchings_value,
  };

  const SecretSanta::Messenger::Settings settings{argc, argv};

  EXPECT_EQ(settings.ConfigurationFile(), "path/to/some/directory/configuration.yaml");
  EXPECT_EQ(settings.MatchingsFile(), "path/to/some/directory/matchings.yaml");
}

TEST(MessengerSettings, DefaultConstructor) {
  const SecretSanta::Messenger::Settings settings;
  EXPECT_EQ(settings.ConfigurationFile(), "");
  EXPECT_EQ(settings.MatchingsFile(), "");
}

}  // namespace
