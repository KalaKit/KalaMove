# KMF 2.0 spec roadmap

This document outlines the roadmap for KMF 2.0 spec. These ideas help reduce repetition, expand feature sets while keeping syntax simple and help make the overall workflow easier to manage as manifest file sizes grow. 

> Important: this document is not final and may be refined over time

## Goals

- backwards-compatible: kmf 2.0 fully supports all features of kmf 1.0 docs and they don't need to be modified or rewritten
- tokens + token key:   reusability and maintainability (write less, repeat less)
- ?…? path wrapping:    clarity and robustness (no parsing ambiguity)
- print key:            observability and debugging (know what’s happening)
- run key:              execution and extensibility (bridge out to the world)

---

## Save empty kmf blocks

KalaMove 1.0 and 1.1 bail out early when a bad kmf block is detected at parse time, this is bad if a bad block is detected in the middle of your `.kmf` file. The goal in 2.0 is to fix this by allowing empty key values but simply skip those in handle stage, and if a path is invalid then we save as empty so it doesnt break stuff

---

## Token key

The purpose of the `token: ` key is to be able to avoid retyping paths for each origin or target part that is reused

- you cant pass more than one value to a token
- a `, ` splits the name and value of a token
- pass a token to any part of any key as a path or a part of a path, the start of a token is marked with `$`
- tokens must use the same `@` symbol for dir splitting
- tokens must be defined before used, but can be defined at any stage between any kmf blocks

---

## Support for env keys

OS-agnostic env keys work just like the token value, these tokens are restricted and you can't make new tokens with any of these names

### OS-agnostic

| Token       | Windows                                | Linux                        |
|-------------|----------------------------------------|------------------------------|
| $HOME       | C:\Users\username                      | /home/username               |
| $TEMP       | %TEMP%                                 | /tmp                         |
| $DESKTOP    | C:\Users\username\Desktop              | $HOME/Desktop                |
| $DOCUMENTS  | C:\Users\username\Documents            | $HOME/Documents              |
| $DOWNLOADS  | C:\Users\username\Downloads            | $HOME/Downloads (if present) |
| $MUSIC      | C:\Users\username\Music                | ~/Music (if present)         |
| $PICTURES   | C:\Users\username\Pictures             | ~/Pictures (if present)      |
| $VIDEOS     | C:\Users\username\Videos               | ~/Videos (if present)        |
| $PUBLIC     | C:\Users\Public                        | /usr/share or /srv/public or ~/Public |
| $CONFIG     | C:\Users\username\AppData\Roaming      | $HOME/.config                |
| $BIN        | $PROGRAMFILES (defaults to $BINX64)    | /usr/local/bin               |
| $BINX64     | $PROGRAMFILES                          | /usr/local/bin               |
| $BINX32     | $PROGRAMFILESX86                       | /usr/local/bin               |
| $BINLOCAL   | $LOCALAPPDATA\Programs                 | /usr/local/bin               |
	
### Windows-specific

| Token               | Path                                                                 |
|---------------------|----------------------------------------------------------------------|
| $APPDATA            | C:\Users\username\AppData\Roaming                                   |
| $LOCALAPPDATA       | C:\Users\username\AppData\Local                                     |
| $LOCALLOW           | C:\Users\username\AppData\LocalLow                                  |
| $PROGRAMFILES       | C:\Program Files                                                    |
| $PROGRAMFILESX86    | C:\Program Files (x86)                                              |
| $COMMONPROGRAMFILES | C:\Program Files\Common Files or C:\Program Files (x86)\Common Files |

### Linux-specific

| Token            | Path             |
|------------------|------------------|
| $XDG_CONFIG_HOME | $HOME/.config    |
| $XDG_CACHE_HOME  | $HOME/.cache     |
| $XDG_DATA_HOME   | $HOME/.local/share |
| $USR_LOCAL       | /usr/local       |
| $ETC             | /etc             |

---

## Print key

The purpose of the `print: ` key is to be able to print log messages to the console for debugging or information at a specific point in the `.kmf` file

- each print key prints only one block of text
- the text is always the first parameter after an optional owner token with a space in between them
- print keys accept OS and user defined tokens and can print the value of a token, the token must be defined before the print key
- print keys accept `\n`, `\t` and `\r` and will print their values correctly
- when printing paths, only `@` is used as the separator, `\` is always literal
- print key does not interpret `, ` in any special way and it works as regular character

--- 

## Run key

The purpose of the `run: ` key is to be able to run external scripts when you need to do an action at a specific point in the `.kmf` file

The script referenced in this text is batch/powershell/shell depending on which one is valid and found

- each run key accepts multiple scripts separated with `, `, a space separates run script params
- the script path is always the first parameter after an optional owner token with a space in between them
- run key script path doesnt accept extensions so that the key can remain os-agnostic and run the same way on both windows and linux, instead the parser checks internally if the value leads to a valid script and then runs that
- each parameter except the owner token must be covered with `?` so that parameters and paths with spaces can be sent

--- 

## Shared by Print and Run key

Some details are shared across these two keys and work the same way, mostly

- user defined and os tokens and kmf block tokens can be combined to create paths
- paths must be be surrounded with `?` so that the print or run key can treat it as a single path
- owner types are `$BEFORE_OWNER`, `$AFTER_OWNER` and `$NO_OWNER`
- `$BEFORE_OWNER` token means the kmf block below this key is referenced
- `$AFTER_OWNER` token means the kmf block above this key is referenced
- `$NO_OWNER` token means this kmf block is standalone and cannot reference either below or above kmf block data, this is the default, and if no owner token is passed to either key then this token is assigned by default
- `$ORIGIN`, `$TARGET_X` and `$ACTION` tokens are accepted only if the owner token was set to one of the two ones, and not `$NO_OWNER`. the X in `$TARGET_X` is the X-th target starting from 0 in the targets vector of the referenced block
- owner tokens are evaluated at the second pass during parsing, where value to them is passed internally by the origin, target or action value relative to internally stored line

---

## Reserved tokens

Several tokens are reserved and cannot be defined by the end user, defining any of these will skip the definition of this token because allowing these tokens to be defined will clash with using them for real world uses.

- All tokens defined in env keys are reserved
- `$BEFORE_OWNER`, `$AFTER_OWNER` and `$NO_OWNER` are reserved
- `$ORIGIN` and `$ACTION` tokens are reserved
- `$TARGET_0` to `$TARGET_255` are reserved and the maximum allowed number of targets for a kmf block will be capped to 256

## Paths in kmf blocks

This version introduces tokens which make path building harder to parse, so to solve this we introduced the `?` as described above. This symbol ensures complex paths are always combined together correctly, using the ? symbol clearly marks the begin and end of each path even with half-paths and multiple tokens, and the special path handler helper function will always be used if any part of any key value has the `?` symbol