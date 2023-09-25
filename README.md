# Secret Santa

[![build and test](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml)

Organizes a "Secret Santa" gift exchange event! Given a list of participant names, addresses, and emails, this project randomizes the gift exchange and sends instructions via email to each participant.

- [Requirements](#requirements)
- [Configuration](#configuration)
  - [Email](#configuration-email)
  - [S-Nail Package](#configuration-s-nail-package)
  - [Secret Santa Executable](#configuration-secret-santa-executable)
- [Usage](#usage)
  - [Command-Line](#usage-command-line)
  - [Configuration File](#usage-configuration-file)
  - [Results File](#usage-results-file)
- [Testing](#testing)
- [License](#license)

## Requirements

This project requires the following packages:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.
- **S-nail**: On Ubuntu, install S-nail with `sudo apt install s-nail`.

Additionally, the _yaml-cpp_ library (<https://github.com/jbeder/yaml-cpp>) is used for parsing YAML files. However, you do not need to install this library; instead, this library is automatically downloaded, built, and linked with this project when this project is configured.

## Configuration

- [Email](#configuration-email)
- [S-Nail Package](#configuration-s-nail-package)
- [Secret Santa Executable](#configuration-secret-santa-executable)

[(Back to Top)](#secret-santa)

### Configuration: Email

If you intend to use a Gmail email address to send messages, the easiest way of doing so is to create an App Password on your Google account. See <https://support.google.com/accounts/answer/185833> for instructions on how to do so. Google App Passwords are not as secure as other more modern options, so it is recommended to delete your App Password once you are done using this project. Better yet, create a new Gmail email address specifically for your Secret Santa event!

[(Back to Configuration)](#configuration)

### Configuration: S-Nail Package

The S-nail package requires some configuration. In your home directory, create a `.mailrc` configuration file with:

```bash
touch ~/.mailrc
chmod 0600 ~/.mailrc
```

Open this file in any text editor, and paste the following contents:

```bash
set v15-compat
set verbose
set sendcharsets=utf-8,iso-8859-1
set reply-in-same-charset
set folder=mail
set sendwait
set tls-verify=strict
set tls-ca-file=/etc/ssl/certs/ca-certificates.crt
set tls-ca-no-defaults
set smtp-use-starttls
set smtp-auth=login
set from="myusername@gmail.com"
set mta=smtps://myusername:mypassword@smtp.gmail.com:465
```

Replace `myusername` with your email address and `mypassword` with your email password. If using Gmail, the password is your App Password.

Verify that S-nail is correctly configured by sending a short email message to yourself with:

```bash
echo "This is a test message." | s-nail --subject "Test Email" myusername@gmail.com
```

Again, replace `myusername` with your email address. This should send a short email from yourself to yourself.

[(Back to Configuration)](#configuration)

### Configuration: Secret Santa Executable

Clone this project's repository and configure it with:

```bash
git clone git@github.com:acodcha/secret-santa.git
cd secret-santa
mkdir build
cd build
cmake ..
make --jobs=16
```

This builds the main executable, `build/bin/secret-santa`.

[(Back to Configuration)](#configuration)

## Usage

- [Command-Line](#usage-command-line)
- [Configuration File](#usage-configuration-file)
- [Results File](#usage-results-file)

[(Back to Top)](#secret-santa)

### Usage: Command-Line

Print usage information to the console by running the main executable from the `build` directory with:

```bash
bin/secret-santa --help
```

Run the main executable from the `build` directory with:

```bash
bin/secret-santa --configuration <path> [--results <path>] [--email] [--seed <integer>]
```

The command-line arguments are:

- `--configuration <path>`: Path to the YAML configuration file to be read. Required.
- `--results <path>`: Path to the YAML results file to be written. Optional. If omitted, no results file is written.
- `--email`: Whether or not to email instructions to each participant. Optional. If omitted, instructions are not emailed to any participant.
- `--seed <integer>`: Seed value for pseudo-random number generation. If omitted, the seed value is randomized.

[(Back to Usage)](#usage)

### Usage: Configuration File

TODO.

[(Back to Usage)](#usage)

### Usage: Results File

TODO.

[(Back to Usage)](#usage)

## Testing

Testing is optional, disabled by default, and requires the following additional package:

- **GoogleTest**: The GoogleTest library (<https://github.com/google/googletest>) is used for testing. On Ubuntu, install it with `sudo apt install libgtest-dev`. When testing is enabled, if the GoogleTest library is not found on your system, it is automatically downloaded, built, and linked with this project when this project is configured.

You may optionally test this project from the `build` directory with:

```bash
cmake .. -DTEST_SECRET_SANTA=ON
make --jobs=16
make test
```

This builds and runs the tests.

[(Back to Top)](#secret-santa)

## License

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT license. For more details, see the [LICENSE](LICENSE) file or visit <https://mit-license.org>.

[(Back to Top)](#secret-santa)
