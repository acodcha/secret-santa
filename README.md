# Secret Santa

[![build and test](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/secret-santa/actions/workflows/build_and_test.yaml)

Sends email messages for organizing a Secret Santa gift-exchange event!

- [Requirements](#requirements)
- [Configuration](#configuration)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)

## Requirements

This project requires the following packages:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.

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
