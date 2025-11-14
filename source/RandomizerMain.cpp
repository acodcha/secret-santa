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

#include <yaml-cpp/yaml.h>

#include "Configuration.hpp"
#include "Matchings.hpp"
#include "RandomizerSettings.hpp"

int main(int argc, char* argv[]) {
  const SecretSanta::Randomizer::Settings settings{argc, argv};

  const SecretSanta::Configuration configuration{settings.ConfigurationFile()};

  const SecretSanta::Matchings matchings{configuration.Participants(), settings.RandomSeed()};

  matchings.Write(settings.MatchingsFile());

  std::cout << "End of " << SecretSanta::Randomizer::Program::Title << "." << std::endl;

  return EXIT_SUCCESS;
}
