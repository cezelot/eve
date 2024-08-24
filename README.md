eve
===

[![Build Status][build-svg]][build]
[![CodeQL][codeql-svg]][codeql]
[![CodeScene Code Health][codescene-svg]][codescene-report]
![Code Size][code-size]
[![PRs Welcome][makeapr-svg]][makeapr]

> A simple command-line text editor.

eve is a lightweight, user-friendly text editor for the terminal that aims to be
simple and intuitive, while also taking advantage of the capabilities of
advanced text editors.

The project is in alpha stage and will provides essential and powerful editing
features (see [Roadmap](#roadmap)), making it ideal for editing configuration
files, creating scripts or witing source codes from the command-line.

## Getting Started

### Prerequisites

- A Unix-like operating system: GNU/Linux, BSD, macOS, etc.
  On Windows, you can use [WSL2](https://learn.microsoft.com/windows/wsl/install)
  or [Cygwin](https://cygwin.com).
  On Android, use [Termux](https://termux.dev).
- Tools for building the executable:
  - `make`
  - `gcc`

You can install all the required tools on Linux (Debian-based) with this command:

```bash
sudo apt install make gcc
```

### Compiling

If you haven't already clone the repository:

```bash
git clone https://github.com/cezelot/eve.git
```

Navigate to the repo directory and run `make`:

```bash
cd eve
make
```

It'll build an executable named `eve`.

#### Make rules

Command       |  Description
:-------------|:-------------
`make`        | Compile `eve` executable.
`make clean`  | Remove objects files.
`make fclean` | Remove objects files and `eve` executable.
`make re`     | Re-compile `eve` executable.

### Installation

To install `eve`, copy the executable into `~/.local/bin`:

```bash
cp eve ~/.local/bin
```

Or into `/usr/local/bin`, note that you must have adequate privileges:

```bash
sudo cp eve /usr/local/bin
```

### Usage

To open and edit a file:

```bash
eve <filename>
```

To create a new file:

```bash
eve
```

Then use `Ctrl-S` to create and save the new file.

## Roadmap

List of features planned for version 1.0.0:

 - [x] Text viewer
 - [x] Text editor
 - [x] Search feature
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

Please make sure to read the [contributing guidelines](docs/CONTRIBUTING.md)
before.

## Authors

Ismaël Benjara <ib@cezelot.me>

See also the list of [contributors] who participated in this project.

## License

eve is free software distributed under the GNU Public License,
for details see [COPYING](COPYING).

[build-svg]: https://github.com/cezelot/eve/actions/workflows/build.yml/badge.svg?event=push
[build]: https://github.com/cezelot/eve/actions/workflows/build.yml
[codeql-svg]: https://github.com/cezelot/eve/actions/workflows/github-code-scanning/codeql/badge.svg
[codeql]: https://github.com/cezelot/eve/actions/workflows/github-code-scanning/codeql
[codescene-svg]: https://codescene.io/projects/51883/status-badges/code-health
[codescene-report]: https://drive.proton.me/urls/5SKHRBA710#yz0WZNGdkCAk
[code-size]: https://img.shields.io/github/languages/code-size/cezelot/eve
[makeapr-svg]: https://img.shields.io/badge/PRs-welcome-green.svg?style=flat-square
[makeapr]: https://img.shields.io/badge/PRs-welcome-green.svg?style=flat-square
[contributors]: https://github.com/cezelot/eve/graphs/contributors
