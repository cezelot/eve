# Contributing Guidelines

Contribution is welcome, encouraged, and appreciated. There are many ways to contribute,
from improving the documentation, submitting bug reports and feature requests or writing code
which can be incorporated into eve itself.

Here are some guidelines for contributing back to this project:

 - [Code of Conduct](#Code of Conduct)
 - [Reporting Issues](#reporting-issues)
 - [Submitting Pull Requests](#submitting-pull-requests)
   - [Getting started](#getting-started)
   - [Coding Style Guidelines](#coding-style-guidelines)
   - [Commit Message Guidelines](#commit-message-guidelines)
   - [Versioning Guidelines](#versioning-guidelines)

## Code of Conduct

First, please take a moment to review our [Code of Conduct](CODE_OF_CONDUCT.md).

## Reporting Issues

If you have a bug or a suggestion, please be so kind as to search
for any open issue already covering your problem or suggestion.

If you find one, comment on it, so we know more people are experiencing/supporting it.

If not, you can go ahead and [open an issue](https://github.com/cezelot/eve/issues/new/choose) with as much detail as you can provide.

## Submitting Pull Requests

### Getting started

**Working on your first Pull Request?** You can learn how from this *free* series [How to Contribute to an Open Source Project on GitHub](https://kcd.im/pull-request).
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

eve follows the C coding standard at 42 School.
See the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) for details.

Please follow this style to make eve easy to maintain and develop.

But do not follow it rigidly, you should implement an outside standard’s specifications
when that makes eve better overall in an objective sense. When it doesn’t, you shouldn’t.

Also be so kind as to put a license notice in each new file (*.c or *.h) you create.

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

This project uses [SemVer]((https://semver.org/spec/v2.0.0.html) for versioning.

Please increase the version number of `EVE_VERSION` in `includes/eve.h` to the new version
that your Pull Request would represent.

Here are the rules for generating semantic versioning:

  Version  |  Commit
  :--------|:-------------
  MAJOR    | BREAKING CHANGE
  MINOR    | feat
  PATCH    | fix, perf, refactor, revert

That's it! Thank you for your contribution!
