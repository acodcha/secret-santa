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

#ifndef SECRET_SANTA_RANDOMIZER_PROGRAM_HPP
#define SECRET_SANTA_RANDOMIZER_PROGRAM_HPP

#include <string>

namespace SecretSanta::Randomizer::Program {

// Title of the Secret Santa Randomizer program.
static const std::string Title{"Secret Santa Randomizer"};

// Date and time at which the Secret Santa Randomizer program was compiled.
static const std::string CompilationDateAndTime{
  std::string{__DATE__} + ", " + std::string{__TIME__}};

// Description of the Secret Santa Randomizer program.
static const std::string Description{
    "  Organizes a Secret Santa gift exchange event! Reads a YAML\n"
    "  configuration file containing a list of participants,\n"
    "  randomly generates Secret Santa matchings among the\n"
    "  participants, and outputs the matchings to a YAML file."};

}  // namespace SecretSanta::Randomizer::Program

#endif  // SECRET_SANTA_RANDOMIZER_PROGRAM_HPP
