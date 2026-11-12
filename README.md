*This activity has been created as part of the 42 curriculum by yboutakh.*

# Get Next Line

## Description

`get_next_line` returns one line at a time from a file descriptor. The returned line includes `\n` when present; a final line without `\n` is returned as-is. It returns `NULL` at EOF or on error.

## Instructions

Compile the project sources with your test program:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

Run the executable with a test file path according to your test program. To use the default buffer size, omit `-D BUFFER_SIZE=42`; the header defaults to 42. The subject also requires testing other values, including `1`, `9999`, and `10000000`.

The project provides no executable or `main.c`; supply a separate test driver. Do not include the temporary test `main` in `get_next_line.c` in the submitted implementation.

## Algorithm and data structures

A function-local static `stash` preserves unread bytes between calls. The read helper appends chunks to it and stops as soon as it finds a newline or reaches EOF; it does not read the whole file in advance.

The extraction helper copies the first line into its own allocation, including the newline when present. It then copies any remaining suffix into a new stash allocation and frees the old stash only after the copy succeeds. This keeps the returned line independent from the state needed by the next call. If EOF leaves a nonempty stash without a newline, that remainder is returned once; the following call returns `NULL`.

## Resources

- 42 Get Next Line subject (project specification).
- [`read(2)` — Linux manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [`malloc(3)` and `free(3)` — Linux manual](https://man7.org/linux/man-pages/man3/malloc.3.html)

AI was used as a Socratic tutor for pointer indirection, allocation ownership, and the stash/extraction design.
