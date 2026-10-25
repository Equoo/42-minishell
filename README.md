# minishell

A small Unix shell in C, modelled on bash: prompt, parsing, pipes, redirections and builtins.
Written at 42 Lyon with ticasali: I mainly worked on parsing and execution, ticasali on the builtins and signal handling.

## Build and run

```bash
git clone --recurse-submodules https://github.com/Equoo/42-minishell
cd 42-minishell
make CC=clang          # needs the readline development headers
./minishell
```

The project was built with clang (42 school machines). With gcc, the pinned `libft` submodule fails on `-Werror=unused-result`.

## Features

- Interactive prompt with history (GNU readline)
- Pipelines: `ls -l | grep .c | wc -l`
- Redirections: `<`, `>`, `>>` and heredocs `<<`
- Single and double quotes, `$VAR` and `$?` expansion (no expansion inside single quotes or heredoc delimiters)
- Builtins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signals like bash: `Ctrl-C` gives a new prompt, `Ctrl-\` is ignored at the prompt, `Ctrl-D` exits

## How it works

1. **Parsing**: the line is split into commands and redirections, quotes are resolved and variables expanded. Syntax errors are reported before anything runs.
2. **Heredocs** are read first, before any command starts.
3. **Execution**: one `fork` per command, connected with `pipe` and `dup2`, then `execve` on the path found in `PATH`. Builtins run in the shell process when they are not part of a pipeline, so `cd` and `export` change the shell itself.
4. The exit status of the last command is kept for `$?`.

## What I learned

How a shell actually starts programs (`fork`, `execve`, file descriptors), and how to share a parser and an executor cleanly between two developers.
