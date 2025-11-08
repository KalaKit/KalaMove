# How to use 

To handle files with **KalaMove** simply create a text file in the same directory as the executable and set its extension to `.kmf` and write your content inside it. The example section at the bottom of this **README** file shows how to write a simple `.kmf` file. All relative paths are built internally relative to their `.kmf` file.

## Run types

You can run **KalaMove** manually or from your console. by running its executable manually which gets `.kmf` files from the same folder as the exe itself is at, or by passing `.kmf` paths to **KalaMove** executable from your console as parameters.

| Key          | Description |
|--------------|-------------|
| `manual`     | Picks up all `.kmf` files from the same folder where the exe is run |
| `console`    | Accepts `.kmf` file paths as parameters from the console, allowing you to run them from outside the exe folder |

## Core Keys

All available keys you can use in `.kmf` files.

| Key          | Description |
|--------------|-------------|
| `origin`     | Defines the source path where content is copied from, the origin path must always exist |
| `target`     | Defines the destination path(s). Supports multiple paths, separated by `, `. Invalid values are skipped, one value must always exist |
| `action`     | Handle origin and target paths with chosen action type |

## Action types

All available action types you can use for the action keyword.

| Action      | Description |
|-------------|-------------|
| `copy`      | Copy origin to target path(s), skip if target exists |
| `forcecopy` | Copy origin to target path(s), overwrite if target exists |
| `move`      | Force copy origin to all targets except last, then move origin to last target |
| `rename`    | Rename each target to use origin’s stem, origin must be a valid path |
| `delete`    | Delete all target paths, origin is validated but not used |
| `create`    | Create a new directory at chosen target paths, origin is validated but not used |

## Syntax rules

All syntax rules you must follow when creating `.kmf` files.

| Rule          | Description |
|---------------|-------------|
| Name rule     | Origin name does not need to match with target names as long as extensions match and file-file or dir-dir matches |
| Block rule    | Each move block must contain `origin`, `target`, and `action` keys, and each key must end with `: ` |
| `@@`          | Use `@@` for absolute paths, relative path to executable is used if no `@@` was added at the front of a path. Using absolute paths naturally makes the .kmf file not cross platform because of how absolute paths work differently on Windows and Linux |
| `@`           | Use `@` as the directory separator to ensure cross-platform compatibility |
| `..@`, `.@`   | Use `..@` to reference the parent directory and `.@` for the current directory |
| `/`           | Lines starting with `/` (or multiple `/`) are treated as comments |

---

# Example

```
//kmf version must always be at the top.
//comments and empty lines are ignored so you can comment as much as you want
#KMF VERSION 1.0

//
// This example .kmf file shows how to use the three different actions
// and how to handle relative, absolute, parent and current directory.
//

//file example
origin: KalaWindow@readme.md
target: Elypso-engine@_external_shared@KalaWindow@readme.md
action: copy

//folder example
origin: KalaWindow@_external_shared@glm
target: Elypso-engine@_external_shared@glm
action: copy

//absolute path example
origin: @@C:@Users@greenlaser@Documents@_cpp@KalaWindow@readme.md
target: @@C:@Users@greenlaser@Documents@_cpp@Elypso-engine@_external_shared@KalaWindow@readme.md
action: copy

//relative parent directory example
origin: ..@readme.md
target: ..@Elypso-engine@readme.md
action: copy

//relative current directory example
origin: .@readme.md
target: .@Elypso-engine@readme.md
action: copy
```