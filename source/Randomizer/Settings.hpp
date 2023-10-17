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

#ifndef SECRET_SANTA_RANDOMIZER_SETTINGS_HPP
#define SECRET_SANTA_RANDOMIZER_SETTINGS_HPP

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

#include "../String.hpp"
#include "Argument.hpp"
#include "Program.hpp"

namespace SecretSanta::Randomizer {

// Settings of the Secret Santa Randomizer program.
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
  const std::filesystem::path& ConfigurationFile() const noexcept {
    return configuration_file_;
  }

  // Path to the YAML matchings file to be written. If empty, no matchings file
  // is written.
  const std::filesystem::path& MatchingsFile() const noexcept {
    return matchings_file_;
  }

  // Optional seed value for pseudo-random number generation. If no value is
  // specified, the seed value is randomized.
  constexpr const std::optional<int64_t>& RandomSeed() const noexcept {
    return random_seed_;
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

    std::cout << indent << executable_name_ << " " << Argument::Configuration()
              << " [" << Argument::Matchings() << "] "
              << " [" << Argument::Seed() << "]" << std::endl;

    // Compute the padding length of the argument patterns.
    const std::size_t length = std::max({
        Argument::Help().length(),
        Argument::Configuration().length(),
        Argument::Matchings().length(),
        Argument::Seed().length(),
    });

    std::cout << "Arguments:" << std::endl;

    std::cout << indent << PadToLength(Argument::Help(), length) << indent
              << "Displays this information and exits." << std::endl;

    std::cout
        << indent << PadToLength(Argument::Configuration(), length) << indent
        << "Path to the YAML configuration file to be read. Required."
        << std::endl;

    std::cout << indent << PadToLength(Argument::Matchings(), length) << indent
              << "Path to the YAML matchings file to be written. Optional."
              << std::endl;

    std::cout << indent << PadToLength(Argument::Seed(), length) << indent
              << "Seed value for pseudo-random number generation. Optional."
              << std::endl;
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
      } else if (argv[index] == Argument::Key::Configuration
                 && AtLeastOneMore(index, argc)) {
        configuration_file_ = argv[index + 1];
        index += 2;
      } else if (argv[index] == Argument::Key::Matchings
                 && AtLeastOneMore(index, argc)) {
        matchings_file_ = argv[index + 1];
        index += 2;
      } else if (
          argv[index] == Argument::Key::Seed && AtLeastOneMore(index, argc)) {
        random_seed_ = std::strtoll(argv[index + 1], nullptr, 10);
        index += 2;
      } else {
        PrintHeader();
        std::cout << "Unrecognized argument: " << argv[index] << std::endl;
        PrintUsage();
        exit(EXIT_FAILURE);
      }
    }
  }

  // Returns whether there is at least one more element after the given element
  // index.
  bool AtLeastOneMore(const int index, const int count) const noexcept {
    return index + 1 < count;
  }

  // Prints the command to the console.
  void PrintCommand() const {
    std::cout
        << "Command: " << executable_name_ << " "
        << Argument::Key::Configuration << " " << configuration_file_
        << (!matchings_file_.empty() ? " " + Argument::Key::Matchings + " "
                                           + matchings_file_.string() :
                                       "")
        << (random_seed_.has_value() ?
                " " + Argument::Key::Seed + " "
                    + std::to_string(random_seed_.value()) :
                "")
        << std::endl;
  }

  // Prints the settings to the console.
  void PrintSettings() const {
    std::cout << "- The configuration will be read from: "
              << configuration_file_ << std::endl;

    if (matchings_file_.empty()) {
      std::cout
          << "- The matchings will not be written to a file." << std::endl;
    } else {
      std::cout << "- The matchings will be written to: " << matchings_file_
                << std::endl;
    }

    if (random_seed_.has_value()) {
      std::cout << "- The seed value for pseudo-random number generation is : "
                << random_seed_.value() << std::endl;
    } else {
      std::cout
          << "- The seed value for random number generation will be randomized."
          << std::endl;
    }
  }

  // Name of the Secret Santa Randomizer executable.
  std::string executable_name_;

  // Path to the YAML configuration file to be read.
  std::filesystem::path configuration_file_;

  // Path to the YAML matchings file to be written. If empty, no matchings file
  // is written.
  std::filesystem::path matchings_file_;

  // Optional seed value for pseudo-random number generation. If no value is
  // specified, the seed value is randomized.
  std::optional<int64_t> random_seed_;
};

}  // namespace SecretSanta::Randomizer

#endif  // SECRET_SANTA_RANDOMIZER_SETTINGS_HPP
