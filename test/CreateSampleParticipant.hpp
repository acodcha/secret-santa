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

#ifndef SECRET_SANTA_CREATE_SAMPLE_PARTICIPANT_HPP
#define SECRET_SANTA_CREATE_SAMPLE_PARTICIPANT_HPP

#include <yaml-cpp/yaml.h>

#include "../source/Participant.hpp"

namespace SecretSanta {

YAML::Node CreateSampleParticipantA() {
  YAML::Node node;
  node["Alice Smith"]["email"] = "alice.smith@gmail.com";
  node["Alice Smith"]["address"] =
      "123 First Ave, Apt 1, Townsville, CA 91234 USA";
  node["Alice Smith"]["instructions"] =
      "Leave the package with the doorman in the lobby.";
  return node;
}

YAML::Node CreateSampleParticipantB() {
  YAML::Node node;
  node["Bob Johnson"]["email"] = "bob.johnson@gmail.com";
  node["Bob Johnson"]["address"] =
      "456 Second St, Apt 2, Villagetown, CA 92345 USA";
  return node;
}

YAML::Node CreateSampleParticipantC() {
  YAML::Node node;
  node["Claire Jones"]["email"] = "claire.jones@gmail.com";
  node["Claire Jones"]["address"] = "789 Third Rd, Villageburg, CA 93456 USA";
  node["Claire Jones"]["instructions"] = "Hide the package behind the bushes.";
  return node;
}

}  // namespace SecretSanta

#endif  // SECRET_SANTA_CREATE_SAMPLE_PARTICIPANT_HPP
