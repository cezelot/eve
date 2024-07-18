eve
===

[![CodeQL](https://github.com/cezelot/eve/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/cezelot/eve/actions/workflows/github-code-scanning/codeql)
![CodeScene Code Health](https://codescene.io/projects/51883/status-badges/code-health)
![Code Size](https://img.shields.io/github/languages/code-size/cezelot/eve)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-green.svg?style=flat-square)](https://makeapullrequest.com)

> A user-friendly command-line text editor.

eve is a lightweight, user-friendly text editor for the terminal that aims to be simple and intuitive,
while also taking advantage of the capabilities of advanced text editor like Vim or Emacs.

The project is in alpha stage and will provides essential and powerful editing features (see [Roadmap](#roadmap)),
making it ideal for editing configuration files, creating scripts or witing source codes
from the command-line.

## Getting Started

### Prerequisites

- A Unix-like operating system: Linux, BSD, macOS.
  On Windows, you can use [WSL2](https://learn.microsoft.com/windows/wsl/install) or [Cygwin](https://cygwin.com), etc.
  On Android, use [Termux](https://termux.dev).
- Tools for building the binary:
  - `make`
  - `gcc`

You can install all the required tools on Linux with this command:

```bash
sudo apt install make gcc
```

### Compiling

If you haven't already clone the repository:

```bash
sudo apt install git
git clone https://github.com/cezelot/eve.git
```

Navigate to the repo directory and run `make`:

```bash
cd eve
make
```

It'll build a binary named `eve`.

If you want to install `eve`, copy the compiled binary into `~/.local/bin`:

```bash
cp eve ~/.local/bin
```

Or into `/usr/local/bin`, note that you must have adequate privileges:

```bash
sudo cp eve /usr/local/bin
```

#### Make rules

Command       |  Description
:-------------|:-------------
`make`        | Compile `eve`.
`make clean`  | Remove objects files.
`make fclean` | Remove objects files and `eve`.
`make re`     | Re-compile `eve`.

### Usage

To open and edit a file, remove `./` if you have installed the binary:

```bash
./eve <filename>
```

## Roadmap

List of features planned for version 1.0.0:

 - [x] Display text files
 - [ ] Edit text files
 - [ ] Search feature
 - [ ] Syntax highlighting and filetype detection
 - [ ] Line number
 - [ ] Config file
 - [ ] Text formatting
   - [ ] Soft indent
   - [ ] Auto indent
   - [ ] Hard-wrap lines
   - [ ] Soft-wrap lines
 - [ ] Cut, Copy and paste
 - [ ] Modal editing
 - [ ] Undo/Redo

## Contributing

Pull requests are welcome. For reporting a bug or suggesting an enhancement,
feel free to open an issue.

Please make sure to read the [contributing guidelines](docs/CONTRIBUTING.md) before.

## Authors

**Ismael Benjara** - [@cezelot](https://x.com/count_ezelot) - [email](mailto:cezelot@proton.me)

See also the list of [contributors](https://github.com/cezelot/eve/graphs/contributors)
who participated in this project.

## License

eve is free software distributed under the GNU Public License, for details see [COPYING](COPYING).
