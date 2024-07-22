# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

 - Show a warning in the status bar about unsaved changes when closing.

## [0.3.0] - 2024-07-21

### Added

 - Recommended community standards:
   - Code of Conduct
   - Security policy
   - Contributing Guidelines
 - Use `Ctrl-S` to write the current buffer to disk.
 - Notify the user whether the save succeeded or not.
 - Notify the user in the status bar if the file has been modified.

### Fixed

 - Fix `Complex Method` issue in input.c (#1).

## [0.2.0] - 2024-07-12

### Added

 - Insert characters excluding special characters:
   `Enter`, `Escape`, `Delete`, `Backspace`, `Ctrl-H`, and `Ctrl-L`.

## [0.1.0] - 2024-06-30

### Added

 - Display a file.
 - Move the cursor using the arrow keys.
 - Move the cursor to the left or right edges of the screen
   using `Home` and `End` keys.
 - Move the cursor to the top or the bottom of the screen
   using `Page Up` and `Page Down` keys.
 - Move to the end or beginning of the previous or next line when
   `Arrow Left` or `Arrow Right` is pressed at the end or beginning of a line.
 - Scroll up or down an entire page when `Page Up` or `Page Down` key is pressed.
 - Move to the end of the current line with the `End` key.
 - Horizontal scrolling.
 - Vertical scrolling.
 - Display a welcome message when the user starts the program with no file.
 - Render tabs as four spaces.
 - Display a status bar and a status message.
 - Take `--help` and `--version` command-line options.

[unreleased]: https://github.com/cezelot/eve/compare/v0.3.0...HEAD
[0.3.0]: https://github.com/cezelot/eve/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/cezelot/eve/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/cezelot/eve/releases/tag/v0.1.0
