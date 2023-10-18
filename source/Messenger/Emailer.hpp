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

#ifndef SECRET_SANTA_MESSENGER_EMAILER_HPP
#define SECRET_SANTA_MESSENGER_EMAILER_HPP

#include "../Configuration.hpp"
#include "../Matchings.hpp"

namespace SecretSanta::Messenger {

std::string CreateFullMessageBody(
    const Participant& gifter, const Participant& giftee,
    const std::string& main_message_body) {
  std::string text;

  text.append("Hello " + gifter.Name() + ",\n\n");

  text.append(main_message_body + "\n\n");

  text.append("Your giftee is:\n\n");
  text.append(giftee.Name() + "\n");
  text.append(giftee.Address() + "\n");
  if (!giftee.Instructions().empty()) {
    text.append("Special Instructions: " + giftee.Instructions() + "\n");
  }

  text.append("\nThank you!");
  return text;
}

std::string CreateCommand(
    const Participant& gifter, const std::string& message_subject,
    const std::string& message_body) {
  return "echo \"" + message_body + "\" | s-nail --subject \"" + message_subject
         + "\" " + gifter.Email();
}

void SendEmailMessage(
    const Participant& gifter, const Participant& giftee,
    const std::string& message_subject, const std::string& main_message_body) {
  const std::string full_message_body =
      CreateFullMessageBody(gifter, giftee, main_message_body);

  const std::string command{
      CreateCommand(gifter, message_subject, full_message_body)};

  const int outcome{std::system(command.c_str())};

  if (outcome == 0) {
    std::cout << "Sent an email message to " << gifter.Name() << " ("
              << gifter.Email() << ")." << std::endl;
  } else {
    std::cout << "Could not run the command: " << command << std::endl;
  }
}

void SendEmailMessages(
    const Configuration& configuration, const Matchings& matchings) {
  for (const Participant& gifter : configuration.Participants()) {
    const std::map<std::string, std::string>::const_iterator
        gifter_name_and_giftee_name =
            matchings.GiftersToGiftees().find(gifter.Name());

    if (gifter_name_and_giftee_name == matchings.GiftersToGiftees().cend()) {
      continue;
    }

    const std::set<Participant>::const_iterator giftee =
        configuration.Participants().find(
            {gifter_name_and_giftee_name->second});

    if (giftee == configuration.Participants().cend()) {
      continue;
    }

    SendEmailMessage(gifter, *giftee, configuration.MessageSubject(),
                     configuration.MessageBody());
  }
}

}  // namespace SecretSanta::Messenger

#endif  // SECRET_SANTA_MESSENGER_EMAILER_HPP
