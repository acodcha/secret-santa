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

#ifndef SECRET_SANTA_MESSENGER_ARGUMENT_HPP
#define SECRET_SANTA_MESSENGER_ARGUMENT_HPP

#include <string>
#include <string_view>

namespace SecretSanta::Messenger::Argument {

namespace Key {

// Prints usage instructions and exits. Optional.
static const std::string Help{"--help"};

// Path to the YAML configuration file to be read. Required.
static const std::string Configuration{"--configuration"};

// Path to the YAML matchings file to be read. Required.
static const std::string Matchings{"--matchings"};

}  // namespace Key

namespace Value {

// Filesystem path.
static const std::string Path{"<path>"};

}  // namespace Value

// Prints usage instructions and exits. Optional.
[[nodiscard]] std::string_view Help() {
  return Key::Help;
}

// Path to the YAML configuration file to be read. Required.
[[nodiscard]] std::string Configuration() {
  return Key::Configuration + " " + Value::Path;
}

// Path to the YAML matchings file to be read. Required.
[[nodiscard]] std::string Matchings() {
  return Key::Matchings + " " + Value::Path;
}

}  // namespace SecretSanta::Messenger::Argument

#endif  // SECRET_SANTA_MESSENGER_ARGUMENT_HPP
