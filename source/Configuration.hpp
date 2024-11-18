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

#ifndef SECRET_SANTA_CONFIGURATION_HPP
#define SECRET_SANTA_CONFIGURATION_HPP

#include <filesystem>
#include <set>
#include <yaml-cpp/yaml.h>

#include "Participant.hpp"

namespace SecretSanta {

// Configuration details read from a YAML configuration file.
class Configuration {
public:
  // Default constructor. Constructs configuration details with a default message and no
  // participants.
  Configuration() = default;

  // Constructor. Constructs configuration details by reading them from a YAML configuration file.
  explicit Configuration(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
      std::cout << "Cannot find the YAML configuration file at " << path
                << "; please check the file path." << std::endl;
      return;
    }

    YAML::Node root = YAML::LoadFile(path.string());
    if (!root) {
      std::cout << "Cannot parse the YAML configuration file at " << path
                << "; please check that it is a valid YAML file." << std::endl;
      return;
    }

    YAML::Node message = root["message"];

    YAML::Node message_subject = message["subject"];
    if (message_subject) {
      message_subject_ = message_subject.as<std::string>();
      std::cout
          << "The email message subject was read from the YAML configuration file. " << std::endl;
    } else {
      std::cout << "No email message subject is defined in the YAML configuration file; using the "
                   "default email message subject."
                << std::endl;
    }

    YAML::Node message_body = message["body"];
    if (message_body) {
      message_body_ = message_body.as<std::string>();
      std::cout
          << "The email message body was read from the YAML configuration file. " << std::endl;
    } else {
      std::cout << "No email message body is defined in the YAML configuration file; using the "
                   "default email message body."
                << std::endl;
    }

    YAML::Node participants = root["participants"];
    if (participants) {
      for (const YAML::iterator::value_type& participant_node : participants) {
        participants_.emplace(participant_node);
      }
    }

    if (participants_.empty()) {
      std::cout << "No participants are defined in the YAML configuration file." << std::endl;
    } else {
      std::cout << "A total of " << participants_.size()
                << " participants were found. They are:" << std::endl;

      for (const Participant& participant : participants_) {
        std::cout << "- " << participant << std::endl;
      }
    }
  }

  // Destructor. Destroys this configuration object.
  ~Configuration() noexcept = default;

  // Deleted copy constructor.
  Configuration(const Configuration& other) = delete;

  // Deleted move constructor.
  Configuration(Configuration&& other) noexcept = delete;

  // Deleted copy assignment operator.
  Configuration& operator=(const Configuration& other) = delete;

  // Deleted move assignment operator.
  Configuration& operator=(Configuration&& other) noexcept = delete;

  // Subject of the email message that will be sent to each participant. A default value is used if
  // no message subject is defined in the YAML configuration file.
  [[nodiscard]] const std::string& MessageSubject() const noexcept {
    return message_subject_;
  }

  // Body of the email message that will be sent to each participant. A default value is used if no
  // message body is defined in the YAML configuration file. A brief greeting of "Hello <name>" is
  // automatically prepended to this body, and information regarding the participant's giftee is
  // automatically appended to this body.
  [[nodiscard]] const std::string& MessageBody() const noexcept {
    return message_body_;
  }

  // Set of participants.
  [[nodiscard]] const std::set<Participant>& Participants() const noexcept {
    return participants_;
  }

private:
  // Subject of the email message that will be sent to each participant. A default value is used if
  // no message subject is defined in the YAML configuration file.
  std::string message_subject_{"Secret Santa Gift Exchange"};

  // Body of the email message that will be sent to each participant. A default value is used if no
  // message body is defined in the YAML configuration file. A brief greeting of "Hello <name>" is
  // automatically prepended to this body, and information regarding the participant's giftee is
  // automatically appended to this body.
  std::string message_body_{
      "You are receiving this message because you opted to participate in a Secret Santa gift "
      "exchange! This is an automated email message generated by: "
      "https://github.com/acodcha/secret-santa"};

  // Set of participants.
  std::set<Participant> participants_;
};

}  // namespace SecretSanta

#endif  // SECRET_SANTA_CONFIGURATION_HPP
