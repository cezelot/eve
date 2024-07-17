# Contributing Guidelines

Contribution is welcome, encouraged, and appreciated. There are many ways to contribute,
from improving the documentation, submitting bug reports and feature requests or writing code
which can be incorporated into eve itself.

Here are some guidelines for contributing back to this project.

**Table of Content:**
 - [Code of Conduct](#code-of-conduct)
 - [Reporting Issues](#reporting-issues)
   - [Bug Report](#bug-report)
   - [Feature Request](#feature-request)
 - [Submitting Pull Requests](#submitting-pull-requests)
   - [Getting started](#getting-started)
   - [Coding Style Guidelines](#coding-style-guidelines)
   - [Commit Message Guidelines](#commit-message-guidelines)
   - [Versioning Guidelines](#versioning-guidelines)

## Code of Conduct

First, please take a moment to review our [Code of Conduct](CODE_OF_CONDUCT.md).

## Reporting Issues

### Bug Report

If you have a bug, please be so kind as to search for any open issue already covering your problem.

If you find one, comment on it, so we know more people are experiencing it.

If not, you can go ahead and [create a bug report](https://github.com/cezelot/eve/issues/new?assignees=&labels=bug%2Ctriage&projects=&template=bug_report.yml&title=%5BBug%5D+%3Ctitle%3E)
with as much detail as you can provide.

### Feature Request

Please be so kind as to search for any open issue already covering your enhancement.

If you find one, comment on it, so we know more people are supporting it.

If not, you can go ahead and [create a feature request](https://github.com/cezelot/eve/issues/new?assignees=&labels=enhancement%2Ctriage&projects=&template=feature_request.yml&title=%5BFeature%5D+%3Ctitle%3E).
Or you can [start a new discussion](https://github.com/cezelot/eve/discussions/new?category=ideas)
in the Ideas category of [eve Discussions](https://github.com/cezelot/eve/discussions).

## Submitting Pull Requests

### Getting Started

**Working on your first Pull Request?** You can learn how from this *free* series
[How to Contribute to an Open Source Project on GitHub](https://kcd.im/pull-request).
See also [First Timers Only](http://www.firsttimersonly.com).

Search for any open or closed PR that relates to your submission.

If you don't find one:

  1. Fork https://github.com/cezelot/eve to your GitHub account.
  2. Clone the forked repository.
  3. Create a new git branch.
  4. Make your changes.
  5. Commit your changes using a descriptive commit message that follows
     our [commit message conventions](#commit-message-guidelines).
  6. Push your branch to GitHub.
  7. Send a pull request to `eve:main`.

### Coding Style Guidelines

See the file [STANDARD.md](STANDARD.md) for details on the coding standard
used by this project.

Please follow this style to make eve easy to read, maintain and develop.

These coding rules are open for discussion, if you think another standard’s specifications
makes eve better overall in an objective sense or anything else,
please feel free to [start a new discussion](https://github.com/cezelot/eve/discussions/new?category=standard).

### Commit Message Guidelines

eve uses the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
specification.

Try to keep the first commit line short. It's harder to do using this commit style but try to be
concise, and if you need more space, you can use the commit body. Try to make sure that the commit
subject is clear and precise enough that we will know what changed by just looking at the commit logs.

Also be so kind as to reference any issue that would be solved in the PR description body,
[for instance](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue)
_"Fixes #1337"_ for issue number 1337.

### Versioning Guidelines

This project uses [SemVer](https://semver.org/spec/v2.0.0.html) for versioning.

Please increase the version number of `EVE_VERSION` in `includes/eve.h` to the new version
that your Pull Request would represent.

Here are the rules for generating semantic versioning:

  Version  |  Commit
  :--------|:-------------
  MAJOR    | BREAKING CHANGE
  MINOR    | feat
  PATCH    | fix, perf, refactor, revert

That's it! Thank you for your contribution!
