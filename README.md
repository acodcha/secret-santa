# Secret Santa

[![build and test](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml)

Sends email messages for organizing a Secret Santa gift exchange event!

- [Requirements](#requirements)
- [Configuration](#configuration)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)

## Requirements

This project requires the following packages:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.
- **S-nail**: On Ubuntu, install S-nail with `sudo apt install s-nail`.

The yaml-cpp library (<https://github.com/jbeder/yaml-cpp>) is also used for parsing YAML files. However, you do not need to install this library. Instead, this library is automatically downloaded, built, and linked with this project when this project is configured.

### Email Account and Password

If you intend to use a Gmail email address to send messages, the easiest way of doing so is to create an App Password on your Google account. See <https://support.google.com/accounts/answer/185833> for instructions on how to do so. Google App Passwords are not as secure as other more modern options, so it is recommended to delete your App Password once you are done using this project.

### S-nail

The S-nail package requires some configuration. In your home directory, create an S-nail configuration file:

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

Replace `myusername` with your email address and `mypassword` with your email password. If using Gmail, the password is your App Password. Send a test message to verify that your email account and S-nail are configured correctly:

```bash
echo "This is a test message." | s-nail --subject "Test Email" myusername@gmail.com
```

Again, replace `myusername` with your email address. This should send a short email from yourself to yourself.

[(Back to Top)](#secret-santa)

## Configuration

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

[(Back to Top)](#secret-santa)

## Usage

TODO.

[(Back to Top)](#secret-santa)

## Testing

Testing is optional, disabled by default, and requires the following additional package:

- **GoogleTest**: The GoogleTest library (<https://github.com/google/googletest>) is used for testing. On Ubuntu, install it with `sudo apt install libgtest-dev`. When testing is enabled, if the GoogleTest library is not found on your system, it is automatically downloaded, built, and linked with the Physical Quantities library.

You can manually test this project from the `build` directory with:

```bash
cmake .. -DTEST_SECRET_SANTA=ON
make --jobs=16
make test
```

[(Back to Top)](#secret-santa)

## License

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT license. For more details, see the [LICENSE](LICENSE) file or visit <https://mit-license.org>.

[(Back to Top)](#secret-santa)
