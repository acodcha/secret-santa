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

#ifndef SECRET_SANTA_MESSENGER_EMAILER_HPP
#define SECRET_SANTA_MESSENGER_EMAILER_HPP

#include "../Configuration.hpp"
#include "../Matchings.hpp"

namespace SecretSanta::Messenger {

// Composes the full email message body for a given gifter. Prefixes a brief greeting to the given
// main message body and appends the giftee information.
[[nodiscard]] std::string ComposeFullMessageBody(
    const Participant& gifter, const Participant& giftee, const std::string& main_message_body) {
  std::string text;

  text.append("Hello " + gifter.Name() + ",\n\n");

  text.append(main_message_body + "\n\n");

  text.append("Your giftee is: " + giftee.Name() + "\n\n");

  text.append("Mail to:\n\n");
  text.append(giftee.Name() + " SECRET SANTA\n");
  if (!giftee.Address().empty()) {
    text.append(giftee.Address() + "\n");
  }
  if (!giftee.Instructions().empty()) {
    text.append("Special Instructions: " + giftee.Instructions() + "\n");
  }

  text.append("\nThank you!");
  return text;
}

// Composes the command used to invoke the S-nail utility for a given gifter.
[[nodiscard]] std::string ComposeCommand(
    const Participant& gifter, const std::string& message_subject,
    const std::string& message_body) {
  return "echo \"" + message_body + "\" | s-nail --subject \"" + message_subject + "\" "
         + gifter.Email();
}

// Composes and sends an email message to a given gifter. Creates the full body of the message and
// sends it using the S-nail utility.
void ComposeAndSendEmailMessage(
    const Participant& gifter, const Participant& giftee, const std::string& message_subject,
    const std::string& main_message_body) {
  const std::string full_message_body = ComposeFullMessageBody(gifter, giftee, main_message_body);

  const std::string command{ComposeCommand(gifter, message_subject, full_message_body)};

  const int outcome{std::system(command.c_str())};

  if (outcome == 0) {
    std::cout << "Sent an email message to " << gifter.Name() << " (" << gifter.Email() << ")."
              << std::endl;
  } else {
    std::cout << "Could not run the command: " << command << std::endl;
  }
}

// Composes and sends email messages to all gifters.
void ComposeAndSendEmailMessages(const Configuration& configuration, const Matchings& matchings) {
  for (const Participant& gifter : configuration.Participants()) {
    // Obtain the gifter and giftee names.
    const std::map<std::string, std::string>::const_iterator gifter_name_and_giftee_name =
        matchings.GiftersToGiftees().find(gifter.Name());

    if (gifter_name_and_giftee_name == matchings.GiftersToGiftees().cend()) {
      continue;
    }

    // Obtain the giftee information.
    const std::set<Participant>::const_iterator giftee =
        configuration.Participants().find(Participant{gifter_name_and_giftee_name->second});

    if (giftee == configuration.Participants().cend()) {
      continue;
    }

    // Compose and send the email message to this gifter.
    ComposeAndSendEmailMessage(
        gifter, *giftee, configuration.MessageSubject(), configuration.MessageBody());
  }
}

}  // namespace SecretSanta::Messenger

#endif  // SECRET_SANTA_MESSENGER_EMAILER_HPP
