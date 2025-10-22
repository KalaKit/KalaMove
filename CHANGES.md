version 1.0:

- initial release
- origin, target, action keys
- copy, forcecopy, move, rename, delete, create action values

version 1.1:

- splash screen with metadata at the top whenever KalaMove is ran
- fixed a bug where kmf blocks that errored out at handle stage would stop the rest of them from being handled
- fixed a small issue where 'no content after kmf version' error wouldn't print full kmf file path

version 1.2:

- removed splash screen
- no longer quitting after first use
- added several new commands
- move is now its own command which requires parameter for single path or all to get all kmf files in current directory
- using cli template from https://github.com/greenlaser/cli-template