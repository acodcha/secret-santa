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

#ifndef SECRET_SANTA_MATCHINGS_HPP
#define SECRET_SANTA_MATCHINGS_HPP

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "Participant.hpp"

namespace SecretSanta {

// Matchings between gifters and giftees.
class Matchings {
public:
  // Default constructor. Constructs an empty set of matchings.
  Matchings() = default;

  // Constructor. Constructs matchings given a set of participants and an
  // optional random seed. Ensures that the matchings are valid.
  Matchings(const std::set<Participant>& participants,
            const std::optional<int64_t>& random_seed = std::nullopt) {
    // Initialize the random generator.
    std::random_device random_device;
    std::mt19937_64 random_generator(random_device());
    if (random_seed.has_value()) {
      random_generator.seed(random_seed.value());
    }

    // Obtain the participant names.
    std::vector<std::string> participant_names(participants.size());
    {
      std::size_t index = 0;
      for (const Participant& participant : participants) {
        participant_names[index] = participant.Name();
        ++index;
      }
    }

    // Shuffle the participant names.
    std::shuffle(
        participant_names.begin(), participant_names.end(), random_generator);

    // Create the matchings between gifters and giftees. Each participant in the
    // shuffled sequence is a gifter, and their giftee is the next participant
    // in the shuffled sequence. This results in one large cyclic list rather
    // than a graph and guarantees that gifters cannot be their own giftees. For
    // example, consider the sequence [Alice, Bob, Claire, David]. After
    // shuffling, suppose this sequence is [Claire, Bob, David, Alice]. The
    // matchings are thus: Claire->Bob, Bob->David, David->Alice, and
    // Alice->Claire.
    for (std::size_t gifter_index = 0; gifter_index < participant_names.size();
         ++gifter_index) {
      const std::size_t giftee_index =
          gifter_index + 1 < participant_names.size() ? gifter_index + 1 : 0;

      gifters_to_giftees_.emplace(
          participant_names[gifter_index], participant_names[giftee_index]);
    }

    std::cout
        << "Randomized the matchings between gifters and giftees." << std::endl;
  }

  // Constructor. Constructs matchings by reading them from a given YAML file.
  Matchings(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
      std::cout << "Cannot find the YAML matchings file at " << path
                << "; please check the file path." << std::endl;
      return;
    }

    YAML::Node root = YAML::LoadFile(path.string());
    if (!root) {
      std::cout << "Cannot parse the YAML matchings file at " << path
                << "; please check that it is a valid YAML file." << std::endl;
      return;
    }

    YAML::Node gifters_to_giftees = root["gifters_to_giftees"];

    if (gifters_to_giftees && gifters_to_giftees.IsSequence()) {
      for (YAML::iterator gifter_to_giftee = gifters_to_giftees.begin();
           gifter_to_giftee != gifters_to_giftees.end(); ++gifter_to_giftee) {
        if (gifter_to_giftee->size() == 1 && gifter_to_giftee->IsMap()) {
          gifters_to_giftees_.emplace(
              gifter_to_giftee->begin()->first.as<std::string>(),
              gifter_to_giftee->begin()->second.as<std::string>());
        }
      }
    }

    std::cout
        << "Read " << gifters_to_giftees_.size()
        << " matchings between gifters and giftees from the YAML file at: "
        << path << std::endl;
  }

  // Destructor. Destroys this matchings object.
  ~Matchings() noexcept = default;

  // Deleted copy constructor.
  Matchings(const Matchings& other) = delete;

  // Deleted move constructor.
  Matchings(Matchings&& other) noexcept = delete;

  // Deleted copy assignment operator.
  Matchings& operator=(const Matchings& other) = delete;

  // Deleted move assignment operator.
  Matchings& operator=(Matchings&& other) noexcept = delete;

  // Map of gifter participant names to giftee participant names. For example,
  // the map element {Alice, Bob} means that Alice is the gifter and Bob is the
  // giftee, such that Alice is Bob's Secret Santa.
  const std::map<std::string, std::string>& GiftersToGiftees() const noexcept {
    return gifters_to_giftees_;
  }

  // Write these matchings to a given YAML file.
  void Write(const std::filesystem::path& path) const {
    if (path.empty()) {
      return;
    }

    if (!path.parent_path().empty()) {
      std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream stream;

    if (!path.empty()) {
      stream.open(path.string());
      if (!stream.is_open()) {
        std::cout << "Could not open the YAML matchings file for writing at: "
                  << path.string() << std::endl;
        return;
      }
    }

    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "gifters_to_giftees";
    emitter << YAML::Value << YAML::BeginSeq;

    for (const std::pair<const std::string, std::string>& gifter_and_giftee :
         gifters_to_giftees_) {
      YAML::Node node;
      node[gifter_and_giftee.first] = gifter_and_giftee.second;
      emitter << node;
    }

    emitter << YAML::EndSeq << YAML::EndMap;

    stream << emitter.c_str();

    if (std::filesystem::exists(path)) {
      std::filesystem::permissions(
          path, std::filesystem::perms::owner_read
                    | std::filesystem::perms::owner_write
                    | std::filesystem::perms::group_read
                    | std::filesystem::perms::others_read);
    }

    if (stream.is_open()) {
      stream.close();
    }

    std::cout
        << "Wrote the matchings between gifters and giftees to the YAML file: "
        << path << std::endl;
  }

  inline bool operator==(const Matchings& other) const noexcept {
    return gifters_to_giftees_ == other.gifters_to_giftees_;
  }

  inline bool operator!=(const Matchings& other) const noexcept {
    return gifters_to_giftees_ != other.gifters_to_giftees_;
  }

  inline bool operator<(const Matchings& other) const noexcept {
    return gifters_to_giftees_ < other.gifters_to_giftees_;
  }

  inline bool operator>(const Matchings& other) const noexcept {
    return gifters_to_giftees_ > other.gifters_to_giftees_;
  }

  inline bool operator<=(const Matchings& other) const noexcept {
    return gifters_to_giftees_ <= other.gifters_to_giftees_;
  }

  inline bool operator>=(const Matchings& other) const noexcept {
    return gifters_to_giftees_ >= other.gifters_to_giftees_;
  }

private:
  // Map of gifter participant names to giftee participant names. For example,
  // the map element {Alice, Bob} means that Alice is the gifter and Bob is the
  // giftee, such that Alice is Bob's Secret Santa.
  std::map<std::string, std::string> gifters_to_giftees_;
};

}  // namespace SecretSanta

#endif  // SECRET_SANTA_MATCHINGS_HPP
