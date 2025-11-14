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

#ifndef SECRET_SANTA_PARTICIPANT_HPP
#define SECRET_SANTA_PARTICIPANT_HPP

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

namespace SecretSanta {

// A participant in the Secret Santa gift exchange. Contains the participant's information.
class Participant {
public:
  // Default constructor. Creates a participant with an empty name, email, address, and
  // instructions.
  Participant() = default;

  // Constructor. Creates a participant from a given name. The email address, street address, and
  // instructions are empty. Only used for searching through a set of participants.
  explicit Participant(const std::string& name) : name_(name) {}

  // Constructor. Creates a participant from a YAML node of the form:
  //   Alice Smith:
  //     email: alice.smith@gmail.com
  //     address: 123 First Ave, Apt 1, Townsville, CA, 91234 USA
  //     instructions: Leave the package with the doorman in the lobby.
  explicit Participant(const YAML::Node& node) {
    if (!node.IsMap()) {
      return;
    }

    if (node.size() != 1) {
      return;
    }

    for (const YAML::detail::iterator_value& element : node) {
      name_ = element.first.as<std::string>();

      if (name_.empty()) {
        return;
      }

      if (element.second["email"]) {
        email_ = element.second["email"].as<std::string>();
      }

      if (element.second["address"]) {
        address_ = element.second["address"].as<std::string>();
      }

      if (element.second["instructions"]) {
        instructions_ = element.second["instructions"].as<std::string>();
      }
    }
  }

  // Destructor. Destroys this participant.
  ~Participant() noexcept = default;

  // Copy constructor. Constructs a participant by copying another one.
  Participant(const Participant& other) = default;

  // Move constructor. Constructs a participant by moving another one.
  Participant(Participant&& other) noexcept = default;

  // Copy assignment operator. Assigns this participant by copying another one.
  Participant& operator=(const Participant& other) = default;

  // Move assignment operator. Assigns this participant by moving another one.
  Participant& operator=(Participant&& other) noexcept = default;

  // Name of this participant. Each participant must have a unique name.
  [[nodiscard]] const std::string& Name() const noexcept {
    return name_;
  }

  // Email address of this participant.
  [[nodiscard]] const std::string& Email() const noexcept {
    return email_;
  }

  // Street address of this participant.
  [[nodiscard]] const std::string& Address() const noexcept {
    return address_;
  }

  // Additional instructions for mailing packages to this participant.
  [[nodiscard]] const std::string& Instructions() const noexcept {
    return instructions_;
  }

  // Prints this participant as a string.
  [[nodiscard]] std::string Print() const noexcept {
    std::string details;

    if (!email_.empty()) {
      details.append("email: " + email_);
    }

    if (!address_.empty()) {
      if (!details.empty()) {
        details.append("; ");
      }
      details.append("address: " + address_);
    }

    if (!instructions_.empty()) {
      if (!details.empty()) {
        details.append("; ");
      }
      details.append("instructions: " + instructions_);
    }

    if (details.empty()) {
      return name_;
    } else {
      return name_ + " (" + details + ")";
    }
  }

  // Creates a YAML node containing this participant's information. The YAML
  // node is of the form:
  //   Alice Smith:
  //     email: alice.smith@gmail.com
  //     address: 123 First Ave, Apt 1, Townsville, CA, 91234 USA
  //     instructions: Leave the package with the doorman in the lobby.
  [[nodiscard]] YAML::Node YAML() const {
    YAML::Node node;
    node[name_]["email"] = email_;
    node[name_]["address"] = address_;
    node[name_]["instructions"] = instructions_;
    return node;
  }

  inline bool operator==(const Participant& other) const noexcept {
    return name_ == other.name_;
  }

  inline bool operator!=(const Participant& other) const noexcept {
    return name_ != other.name_;
  }

  inline bool operator<(const Participant& other) const noexcept {
    return name_ < other.name_;
  }

  inline bool operator>(const Participant& other) const noexcept {
    return name_ > other.name_;
  }

  inline bool operator<=(const Participant& other) const noexcept {
    return name_ <= other.name_;
  }

  inline bool operator>=(const Participant& other) const noexcept {
    return name_ >= other.name_;
  }

private:
  // Name of this participant. Each participant must have a unique name.
  std::string name_;

  // Email address of this participant.
  std::string email_;

  // Street address of this participant.
  std::string address_;

  // Additional instructions for mailing packages to this participant.
  std::string instructions_;
};

inline std::ostream& operator<<(std::ostream& stream, const Participant& participant) {
  stream << participant.Print();
  return stream;
}

}  // namespace SecretSanta

namespace std {

template <>
struct hash<SecretSanta::Participant> {
  inline size_t operator()(const SecretSanta::Participant& participant) const {
    return hash<std::string>()(std::string(participant.Name()));
  }
};

}  // namespace std

#endif  // SECRET_SANTA_PARTICIPANT_HPP
