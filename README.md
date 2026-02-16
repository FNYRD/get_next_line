*This project has been created as part of the 42 curriculum by jericard.*

## Description

**get_next_line** is a project developed as part of the **42 Porto Common Core**, with the goal of implementing a function that reads a line from a **file descriptor**, returning it one line at a time.

The project consists of creating a function capable of reading from any file descriptor (such as files or standard input) and returning a complete line ending with a newline character (`\n`), or the last line if the end of **file** is reached. The function must handle variable **buffer sizes**, manage **static memory** correctly between calls, and ensure proper **memory allocation** and cleanup to avoid leaks.

### Overview
The mandatory part of the project focuses on implementing a function that *reads one line at a time from a single file descriptor*. Each call to *get_next_line* returns the next available line, including the terminating newline character (`\n`) when present, until the end of file is reached.

This requires reading from the file descriptor using a fixed buffer size, properly assembling partial reads, and storing any remaining data for subsequent calls. The function must handle memory allocation carefully, ensuring that *no memory leaks* occur and that the returned line is always correctly terminated.

As part of the *bonus* section, the project extends the base functionality by allowing the function to manage multiple file descriptors simultaneously.

In this enhanced version, *get_next_line* preserves an independent read state for each file descriptor, making it possible to return lines from different descriptors interleaved across successive calls. For example, the function may return a line from fd 4, followed by a line from fd 5, and later continue reading from fd 4 exactly where it left off.

Implementing this behavior requires an effective strategy for associating buffered data with each file descriptor, typically through static storage indexed by the file descriptor value. This extension reinforces key concepts such as *static memory persistence*, *file descriptor management*, and robust *memory handling* in C.

## Instructions


### Installation

The project must be cloned from the official GitHub repository of the user **FNYRD**:
git clone https://github.com/FNYRD/get_next_line.git

### Compilation

The project must be compiled from the **root directory**, where both the mandatory and bonus source files are located.  

#### Mandatory Part

## Test File Requirements

Make sure that your test file includes the following headers:

#include "get_next_line.h"
#include "get_next_line_bonus.h"

*Important:*
Depending on which version you are testing (mandatory or bonus), you must comment out the opposite header.
Failing to do so may result in compilation or runtime errors.

For example:

*When testing the mandatory version*, comment out get_next_line_bonus.h

*When testing the bonus version*, comment out get_next_line.h

*To compile the mandatory version* of `get_next_line`, use the following command:

cc -Wall -Wextra -Werror -g test_file.c get_next_line.c get_next_line_utils.c -o get_next_line

or

cc -Wall -Wextra -Werror -g test_file.c get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line 

to compile the bonus part.

### Usage

#### Mandatory Part

The mandatory version of `get_next_line` reads from **a single file descriptor at a time**.  
After compilation, the executable can be used to read a file line by line.

**Example usage with one file:**
./get_next_line file.txt

#### Bonus Part

The bonus version supports multiple file descriptors simultaneously, allowing lines to be read from different files in an interleaved manner.

**Example usage with multiple files:**
./get_next_line_bonus file1.txt file2.txt

#### Debugging

All compilations must include the `-g` flag in order to enable proper debugging and memory analysis with **Valgrind**.

#### Mandatory 
valgrind --leak-check=full --show-leak-kinds=all ./get_next_line example.txt

#### Bonus (2 fds, for example)
valgrind --leak-check=full --show-leak-kinds=all ./get_next_line example1.txt example2.txt

#### Extra

The number of characters read from the file descriptor on each call is controlled by the *BUFFER_SIZE* macro.

*BUFFER_SIZE* defines *how many bytes are read from the file descriptor at a time* before the data is processed and assembled into a complete line. A smaller value results in *more read operations*, while a larger value reduces the number of reads but *increases memory usage*.

To define *BUFFER_SIZE*, the macro must be added at compilation time using the -D flag.

**Example:**

cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 test_file.c get_next_line.c get_next_line_utils.c -o get_next_line

**The same approach applies to the bonus version:**
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 test_file.c get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line_bonus

## Resources

### References
- Function: https://medium.com/@beatrizbazaglia/get-next-line-3872eb3189e6
- memory management: https://www.w3schools.com/c/c_memory_management.php
- static and dinamic memory: https://www.geeksforgeeks.org/c/static-and-dynamic-memory-allocation-in-c/

### Use of AI Tools

- **ChatGPT** was used to clarify conceptual doubts ADAPTAR.
- **Codex** was used as a debugging aid to help identify logical errors and improve code correctness during development.

### Algorithm and Data Structures

The get_next_line function is implemented as an *incremental reading algorithm* that processes the input stream *one chunk at a time* until a full line is assembled. On each call, the function reads from the file descriptor into a temporary buffer of size *BUFFER_SIZE*, *appends* this new data to a persistent *stash*, and stops as soon as a newline character (`\n`) or the end of file is reached.

In the *mandatory* part, this persistent state is stored in a static pointer stash, which keeps any unread data between calls to get_next_line. Each read operation fills a dynamically allocated character array (buffer), which is then concatenated with the stash using *helper functions* such as ft_strjoin, ft_substr, flen, and ft_fb. When a complete line is found, a new null-terminated character array is created for the line, the stash is updated to contain only the remaining data, and the line is returned to the caller. If no more data is available, the stash is freed and the function returns NULL.

In the bonus part, the same logic is extended to support multiple file descriptors simultaneously. Instead of a single static pointer, the implementation uses a static array of pointers mstash[MAX_FD], where each index corresponds to the stash associated with a specific file descriptor. This structure allows get_next_line to preserve an independent read state for each descriptor, enabling interleaved calls on different files or streams without losing context.

Throughout the implementation, the main data structures are character arrays (strings), both static and dynamically allocated. Static storage is used to persist state across function calls, while dynamic allocation provides flexible buffers for reading, concatenating, and slicing text. Careful use of malloc, free, and null-terminated arrays ensures that lines are returned correctly and that all intermediate memory is properly managed to avoid leaks.