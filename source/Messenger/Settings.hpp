// Copyright © 2023-2024 Alexandre Coderre-Chabot
//
// This file is licensed under the MIT license. For more information, visit:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included in all copies or
//   substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This file was originally obtained from:
//     https://github.com/acodcha/secret-santa

#ifndef SECRET_SANTA_MESSENGER_SETTINGS_HPP
#define SECRET_SANTA_MESSENGER_SETTINGS_HPP

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

#include "../String.hpp"
#include "Argument.hpp"
#include "Program.hpp"

namespace SecretSanta::Messenger {

// Settings of the Secret Santa Messenger program.
class Settings {
public:
  // Default constructor. Constructs settings with default parameters.
  Settings() = default;

  // Constructor. Constructs settings from command-line arguments.
  Settings(const int argc, char* argv[]) noexcept {
    ParseArguments(argc, argv);
    PrintHeader();
    PrintCommand();
    PrintSettings();
  }

  // Destructor. Destroys this settings object.
  ~Settings() noexcept = default;

  // Deleted copy constructor.
  Settings(const Settings& other) = delete;

  // Deleted move constructor.
  Settings(Settings&& other) noexcept = delete;

  // Deleted copy assignment operator.
  Settings& operator=(const Settings& other) = delete;

  // Deleted move assignment operator.
  Settings& operator=(Settings&& other) noexcept = delete;

  // Path to the YAML configuration file to be read.
  [[nodiscard]] const std::filesystem::path& ConfigurationFile() const noexcept {
    return configuration_file_;
  }

  // Path to the YAML matchings file to be read.
  [[nodiscard]] const std::filesystem::path& MatchingsFile() const noexcept {
    return matchings_file_;
  }

private:
  // Prints the program's header information to the console.
  void PrintHeader() const {
    std::cout << Program::Title << std::endl;
    std::cout << Program::Description << std::endl;
    std::cout << "Version: " << Program::CompilationDateAndTime << std::endl;
  }

  // Prints the program's usage information to the console.
  void PrintUsage() const {
    const std::string indent{"  "};

    std::cout << "Usage:" << std::endl;

    std::cout << indent << executable_name_ << " " << Argument::Configuration() << " "
              << Argument::Matchings() << std::endl;

    // Compute the padding length of the argument patterns.
    const std::size_t length = std::max({
        Argument::Help().length(),
        Argument::Configuration().length(),
        Argument::Matchings().length(),
    });

    std::cout << "Arguments:" << std::endl;

    std::cout << indent << PadToLength(Argument::Help(), length) << indent
              << "Displays this information and exits." << std::endl;

    std::cout << indent << PadToLength(Argument::Configuration(), length) << indent
              << "Path to the YAML configuration file to be read. Required." << std::endl;

    std::cout << indent << PadToLength(Argument::Matchings(), length) << indent
              << "Path to the YAML matchings file to be written. Optional." << std::endl;
  }

  // Parses the program's command-line arguments.
  void ParseArguments(const int argc, char* argv[]) {
    if (argc <= 1) {
      PrintHeader();
      PrintUsage();
      exit(EXIT_SUCCESS);
    }

    if (argc >= 1) {
      executable_name_ = argv[0];
    }

    for (int index = 1; index < argc;) {
      if (argv[index] == Argument::Key::Help) {
        PrintHeader();
        PrintUsage();
        exit(EXIT_SUCCESS);
      } else if (argv[index] == Argument::Key::Configuration && AtLeastOneMore(index, argc)) {
        configuration_file_ = argv[index + 1];
        index += 2;
      } else if (argv[index] == Argument::Key::Matchings && AtLeastOneMore(index, argc)) {
        matchings_file_ = argv[index + 1];
        index += 2;
      } else {
        PrintHeader();
        std::cout << "Unrecognized argument: " << argv[index] << std::endl;
        PrintUsage();
        exit(EXIT_FAILURE);
      }
    }
  }

  // Returns whether there is at least one more element after the given element index.
  [[nodiscard]] bool AtLeastOneMore(const int index, const int count) const noexcept {
    return index + 1 < count;
  }

  // Prints the command to the console.
  void PrintCommand() const {
    std::cout << "Command: " << executable_name_ << " " << Argument::Key::Configuration << " "
              << configuration_file_ << " "
              << Argument::Key::Matchings + " " + matchings_file_.string() << std::endl;
  }

  // Prints the settings to the console.
  void PrintSettings() const {
    std::cout << "- The configuration will be read from: " << configuration_file_ << std::endl;

    std::cout << "- The matchings will be read from: " << matchings_file_ << std::endl;
  }

  // Name of the Secret Santa Messenger executable.
  std::string executable_name_;

  // Path to the YAML configuration file to be read.
  std::filesystem::path configuration_file_;

  // Path to the YAML matchings file to be read.
  std::filesystem::path matchings_file_;
};

}  // namespace SecretSanta::Messenger

#endif  // SECRET_SANTA_MESSENGER_SETTINGS_HPP
