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

#ifndef SECRET_SANTA_STRING_HPP
#define SECRET_SANTA_STRING_HPP

#include <algorithm>
#include <string>
#include <string_view>

// Namespace that encapsulates all of the Secret Santa program's contents.
namespace SecretSanta {

// Returns a copy of a given string where the copy has been padded to a given length with trailing
// spaces. If the given string is already longer than the given length, nothing is changed.
[[nodiscard]] std::string PadToLength(
    const std::string_view text, const std::size_t length) noexcept {
  std::string padded_text{text};
  const std::size_t text_length = text.size();
  if (length > text_length) {
    padded_text.append(length - text_length, ' ');
  }
  return padded_text;
}

}  // namespace SecretSanta

#endif  // SECRET_SANTA_STRING_HPP
