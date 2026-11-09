# minishell

A small Unix shell in C, written during my first year at Epitech
(module B-PSU-200, March–May 2024). It reads commands, finds them in
`PATH`, runs them with `fork`/`execve`, and has its own `cd`, `env`,
`setenv`, `unsetenv` and `exit`.

## Read this first

**This code is bad, and I know it.** I wrote it nearly three
years ago as a first-year student, while working on several other
projects. I'm publishing it **exactly as I submitted it**. I haven't
cleaned up, refactored or fixed anything, because rewriting it now
would misrepresent what I could do back then.

I'm including it for two reasons:

1. It was one of my first real low-level projects: processes, system
   calls, raw memory and no safety net.
2. It shows where I started. Comparing it with my recent work shows how
   far I've come.

I went back through the whole codebase and compiled it with
AddressSanitizer to write this README. Everything below, good or bad,
comes from what the code really does. An earlier version of this README
was written without looking at the code and listed pipes, redirections
and `&&`. **None of those exist.** This version fixes that.

---

## History

This repo is the last of three stages, all in Epitech's private
GitHub org:

| Stage | Dates | What happened |
|---|---|---|
| `bsminishell1` (bootstrap) | Feb 12–13, 2024 | Guided exercises. Last commit: *"finished bootstrap, IMPORTANT, NEED TO LEARN HOW TO USE ERRNO"* |
| `minishell1` | Feb 13 – Mar 1, 2024 | ~480 lines: PATH execution, `env`, `cd`. I gave up on my own word splitter for `strtok` (*"switching from my_str_to_Word_array to strtok because im going through an aneurysm"*) |
| `minishell2` (**this repo**) | Mar 20 – May 24, 2024 | Rebuilt on minishell1: `setenv`/`unsetenv`, `cd -`, `;`, error handling |

minishell2 was supposed to add pipes and redirections. I never got that
far. The bootstrap repo for pipes (`bsminishell2`) is empty, and no
version of the code ever calls `pipe()` or `dup2()`.

### The last 36 hours

After `;` landed on May 1, the repo went quiet for three weeks. I spent
that time trying to get my work reviewed. The project allowed three
correction sessions with the teaching staff to help find what was
blocking the automated tests. I didn't get any of them, and when I
asked for help I was told to read the manual. Then came six commits between May 23, 00:29 and May 24, 11:06. Each one
fixes something an automated grader would fail on:

- **`4eecd57`**: the `unsetenv` TTY check was inverted, so the shell
  quit in *interactive* mode on a usage error. A line containing only
  spaces also crashed, because the builtin check read a `NULL` argv[0].
- **`87940d1`**: stopped the startup crash under `env -i` (only the
  startup one; running a command still crashes), and rewrote the
  `setenv` name check. That rewrite made the "must begin with a letter"
  check accept digits. The old version rejected `1`–`9` and missed `0`.
- **`afec85e`** → **`6bdf123`** ("*debuggin need to have marvin's
  pov*" → "*debugg failed so returned to old program*"): I couldn't see
  what the grader saw, so I printed every exit status and made the
  shell exit after every command. It didn't help, and I reverted the
  exit condition 90 minutes later. One small cleanup survived: a
  missing `else` had made `ttyerr` run twice per command when input
  was piped.
- **`f5a46c1`**: until this commit, the prompt was printed **even when
  input was piped**, which would garble the output of every scripted
  test. I found this the night before the deadline.
- **`252eaba`**: every `setenv` error message called `write()` with a
  length one byte too long, so a stray `\0` went out on stderr.

I felt close to cracking it, but I ran out of time before I could fix
everything the project required, and the history matches. Looking back,
the reviews I missed would have helped, but most of what stood
between me and a passing shell is in the bug list below. The final push is cleanup of
grader-visible output, not new features. What's here is what I turned
in.

---

## What it actually does

Each item was checked against a build of this exact code.

| Feature | Status | Notes |
|---|---|---|
| Run programs found in `PATH` | ✅ | `ls`, `echo`, `cat` and so on |
| Absolute / relative paths (`/bin/ls`, `./a.out`) | ✅ | Works, but more by accident than design (see below) |
| `;` command separator | ✅ | `echo a ; echo b` |
| `env` | ✅ | Prints the shell's own copy of the environment |
| `setenv NAME [VALUE]` | ⚠️ | Works, with name validation, but corrupts the heap (see bugs) |
| `unsetenv NAME...` | ✅ | Several names in one command |
| `cd <dir>` | ✅ | Errors go through `perror` |
| `cd -` | ⚠️ | Works once. Twice in a row doesn't swap back (the commit message admits this) |
| `cd` / `cd ~` | ⚠️ | Goes to `/home` itself, not to `$HOME` |
| `exit` | ⚠️ | Only when the line is exactly `exit`. `exit 3` and `ls; exit` fail |
| No prompt when stdin isn't a TTY | ✅ | `isatty(0)` check, so piped scripts work |
| Coloured prompt | ✅ | `BASED$>` |
| `\|`, `>`, `>>`, `<`, `&&`, `\|\|` | ❌ | Not implemented. The commit titled `&& now works` really added `;` |
| Signals (Ctrl-C) | ❌ | Not handled. Ctrl-C kills the shell |

## How it works

About 1,300 lines of C in a flat directory. The life of one input line:

```
getline()                                    main.c        inf_lp
  │  exact "exit\n"? → leave the loop         main.c        exit_mana / terminator
  ▼
split on ';'                                 my_strtopointvirgule.c
  ▼  for each sub-command
split on ' ' / '\t' with strtok              main.c        inputer
  ▼
builtin? (cd, env, setenv, unsetenv)         built_in.c    is_built_in
  │ no
  ▼
resolve in PATH                              pathfinder.c  path_is
  │  split PATH on ':', opendir() each dir,
  │  readdir() every entry, strcmp with the command name
  ▼
access(path, X_OK) → fork()                  main.c        execer / fork_exec
  ├─ child:  execve(path, argv, env)
  └─ parent: waitpid() → status handling     fork_exec_add.c ttyerr
```

The shell keeps its own heap-allocated copy of `envp` (`env_alloc`).
`setenv` and `unsetenv` build a new array and pass it back up the call
chain, so the environment children receive really does change.

PATH resolution doesn't build `dir/cmd` and call `access()` on it.
Instead it opens each `PATH` directory and reads every file name in it
until one matches. That's slow and unusual, but it's how I understood
the problem at the time.

### Files

| File | Role |
|---|---|
| `main.c` | Read loop, `;` dispatch, tokenizing, `fork`/`execve`/`waitpid` |
| `built_in.c` | Builtin dispatcher |
| `cd.c` | `cd`, `cd -`, `cd ~` (`prev_pwd` lives in a `static` local) |
| `setter.c` / `unsetter.c` | `setenv` / `unsetenv`, with tcsh-style error messages |
| `main_env_alloc.c` | Environment copying |
| `env_prnt.c` | `env` |
| `pathfinder.c` | `PATH` lookup via `opendir`/`readdir` |
| `fork_exec_add.c` | Child exit status → messages and shell exit code |
| `my_strtopointvirgule.c` | Split on `;` (*point-virgule*, French for semicolon) |
| `my_str_to_word_array_twodots.c` | Split on `:` (*deux-points*). A copy of the file above with one character changed |
| `custom_str_to_array.c` | Counts spaces to size the argv buffer |
| `my_*.c`, `printf/` | My own libc replacements from the Epitech Piscine (`strlen`, `strcat`, `strdup`, `put_nbr`, a `printf` with `%c %s %d %i %o %u %x %X %f %F %p %n`) |

### The low-level parts

- **Processes:** `fork`, `execve`, `waitpid`, and reading the raw wait
  status by hand
- **Filesystem:** `opendir`/`readdir` for path lookup, `access` for
  permissions, `chdir`/`getcwd` for `cd`
- **I/O:** `getline` for input, `write(2, ...)` for most errors,
  `isatty` to switch between interactive and scripted behaviour
- **Memory:** a hand-managed `char **` environment, grown and shrunk
  with `malloc` on every `setenv`/`unsetenv`
- **No standard `printf`:** all formatted output goes through my own
  `my_printf`, which makes one `write()` syscall per character

---

## The honest part: known bugs

I found these going through the code in 2026. I reproduced every one
with a build of this repo, most of them with `-fsanitize=address`.
I'm leaving them in on purpose.

### Memory safety

- **Every command with an argument overflows the heap.**
  `main.c:97` sizes the argv buffer by splitting the command on **`:`**
  (it reuses the PATH splitter), which nearly always gives 2 slots.
  Then `inputer` writes one slot per space-separated word plus a `NULL`.
  `echo a` is already one write too many. The commit that added `;`
  introduced this, and it only "worked" because glibc's allocator
  usually leaves slack.
- **`setenv` on an existing variable overflows the heap.**
  `env_realloc` (`setter.c:67`) allocates room for `index + 2` entries,
  then copies the *whole* environment into it. `setenv PATH /usr/bin`
  writes dozens of pointers past the end.
- **`setenv NAME VALUE` writes one byte past its buffer.** The buffer
  holds `len(NAME) + len(VALUE) + 2` bytes, and the code writes a
  terminator at index `len(NAME) + len(VALUE) + 2` (`setter.c:23`).
  `strcat` had already terminated the string anyway.
- **An empty environment segfaults** as soon as you run any command:
  `env -i ./mysh` then `ls` exits with 139. `env_alloc` returns `NULL`,
  and `path_is` reads `env[i]` without checking. (A commit says "empty
  env no longer segfaults". It only fixed the startup crash.)

### Resource leaks

- **File descriptors leak on every command.** `pathfinder.c:21` calls
  `opendir` and never calls `closedir`. With the fd limit at 64, the
  shell starts answering `Command not found.` for `true` after about
  10 commands.
- **A missing semicolon allocates in a loop.** In `main_env_alloc.c:18`:
  ```c
  for (; env[cells] != NULL; cells++)
  out = malloc(sizeof(char *) * (cells + 2));
  ```
  The `for` has no body, so the next line *becomes* its body: one
  `malloc` per environment variable, all but the last leaked. The final
  size is still right, which is why I never noticed. `setenv_alloc` has
  the same bug.
- **Nothing is ever freed.** That includes the old environment after
  each `setenv`/`unsetenv`, the `PATH` split arrays (two per command),
  the `;` split, and an `arg` buffer that `inf_lp` allocates on every
  line and never uses.

### Parsing

- **Tabs drop arguments.** `strtok` splits on spaces and tabs, but the
  word count only counts spaces. `echo⇥a⇥b` prints an empty line.
- **Builtins match by prefix** (`strncmp(input[0], "env", 3)`), so
  `envy` prints the environment and `cdrom` runs `cd`.
- **`exit` must be the whole line.** It's compared to `"exit\n"` before
  any parsing.

### Behaviour vs. a real shell

- **`cd` with no argument goes to `/home`**, not `$HOME`. `go_home`
  `chdir`s to the literal string `"/home"`. The loop also calls
  `chdir(". .")` with a space, which always fails. I knew at the time,
  as my minishell1 commit admits: *"cd alone sends you to /home/ and
  not /home/user unfortunatley im too lazy"*.
- **`cd -` can't swap back.** After going back, it saves the *new*
  directory as the previous one. A failed `cd` also overwrites the
  previous directory.
- **Paths over 128 characters** break `cd`, because `getcwd` uses a
  fixed 128-byte buffer.
- **`setenv` accepts names starting with a digit.** The "must begin
  with a letter" check leaves out the 0–9 range. This was a regression
  from the final-day rewrite (see History).
- **`Command not found.` goes to stdout**, through `my_printf`. Most
  other errors use `write(2, ...)`.
- **A failed `execve` prints `execve problemo`** and the child exits
  with 84.
- **Status checks are wrong.** `ttyerr` compares the raw `waitpid`
  status to `11` instead of using `WIFSIGNALED`/`WTERMSIG`. It also
  checks `errno == ENOEXEC` in the *parent*, where the child's `execve`
  can't set it.

### Hacks for the automated grader

Epitech grades projects with an automated test suite ("Marvin"), mostly
by piping scripts into the shell and comparing output and exit codes.
I never implemented a "last exit status". To get the right exit codes
anyway, the shell **exits** in non-interactive mode whenever something
fails: a command returning non-zero, or a `setenv`/`unsetenv` error.
So `printf 'false\necho after\n' | ./mysh` exits with 1 and never runs
`echo after`. Reaching the end of a script (EOF) exits with **84**, the
Epitech error code, even when every command succeeded.

### Code quality

- Function names like `child_killer` (it runs `execve`),
  `terminator` (checks for `exit`), `magik_func` (validates `setenv`
  names), `conditional` and `conditional2`, and
  `str_to_mefaitpaschier` (French for roughly "this one is driving me
  crazy").
- Two string splitters that differ by one character instead of one
  function with a delimiter parameter.
- `my.h` includes about 20 headers, some twice and some unused
  (`signal.h`, `ucontext.h`, `math.h`, and the non-portable
  `bits/sigaction.h`). Its header still says `task02 Day09` from the
  Piscine.
- The Makefile links with `-lm` before the objects, `fclean` deletes an
  undefined `$(NAME)`, there's no `.PHONY`, and there's a joke target I
  left in as well.
- Many small helpers exist only to stay under Epitech's coding-style
  limits on function length and function count per file, not because
  the split made sense.

---

## Build and run

Linux with `gcc` and `make`:

```sh
make
./mysh                         # interactive, shows the BASED$> prompt
echo 'ls -l ; pwd' | ./mysh    # non-interactive, no prompt
```

The binary builds with `-g3` and no optimisation. There are no tests.

## What I'd do differently today

- **Memory ownership first.** Every allocation has an owner and a
  `free`. Valgrind and ASan run in CI, not years later.
- **A real lexer and parser.** Tokenize once into a list of commands,
  then execute it. That would make `|`, redirections and `&&`/`||`
  simple to add instead of a rewrite.
- **Proper PATH lookup:** build `dir/cmd`, call `access()`, and handle
  commands containing `/` on purpose.
- **Track `$?`** instead of killing the shell to fake exit codes. Use
  `WIFEXITED`/`WIFSIGNALED` and the conventional 126/127 codes.
- **`cd`** with `$HOME`, `OLDPWD`/`PWD`, and `getcwd(NULL, 0)`.
- **Signal handling** for `SIGINT` in the shell versus in the child.
- **A layout** with `src/`, `include/`, `lib/`, clear names, and
  regression tests that diff output against `tcsh`.
