*This project has been created as part of the 42 curriculum by eljessou.*

# Get Next Line (GNL)

## Description

**Get Next Line** is a 42 school curriculum project designed to implement a function in C that reads and returns a single line from a file descriptor at each call. 

The primary goal of this project is to introduce the concept of **static variables** in C, memory management, and working efficiently with input/output operations (`read()`). Repeatedly calling `get_next_line()` allows reading text from a file descriptor line by line until reaching the End Of File (EOF) or encountering an error.

### Overview & Key Features
- **Line-by-Line Reading:** Returns one line at a time, including the newline character `\n` (if present).
- **Buffer Flexibility:** Works with any buffer size set at compile time (`BUFFER_SIZE`).
- **Resource Management:** Ensures no memory leaks by properly freeing heap allocations once data is processed or when EOF/errors occur.
- **Multiple File Descriptors (Bonus):** Capable of managing multiple file descriptors simultaneously without losing reading state across different streams.

---

## Technical Explanation & Algorithm Justification

### The Core Challenge
When using the standard `read()` function, data is read in fixed chunks dictated by `BUFFER_SIZE`. However, lines in a file are determined by the newline character (`\n`), which rarely aligns perfectly with `BUFFER_SIZE` boundaries. A single `read()` call might contain:
1. Less than a full line.
2. Exactly one line.
3. Multiple lines plus leftover text for the next line.

### Selected Algorithm: Static Buffer Accumulation
To solve this, the algorithm utilizes a **static variable** that acts as a persistent stash (or dynamic buffer) across function calls.

#### Step-by-Step Breakdown:
1. **Reading into Stash:** 
   - We allocate a buffer of size `BUFFER_SIZE + 1`.
   - We repeatedly call `read()` and concatenate the newly read characters to our static stash variable until a newline (`\n`) is found in the stash or `read()` reaches EOF (0 bytes read).
2. **Extracting the Line:** 
   - Once a newline is found (or EOF is reached), we search for the index of `\n`.
   - We extract all characters up to and including `\n` (or EOF) into a newly allocated string, which represents the line to be returned.
3. **Updating the Stash:** 
   - Whatever remaining characters exist after the `\n` are saved back into the static stash.
   - The original portion of the stash that was returned is freed.
4. **Clean up & Edge Cases:**
   - If memory allocation fails or an error occurs during `read()`, all allocated memory is freed, and `NULL` is returned.

### Algorithm Justification
- **Efficiency:** Instead of reading the entire file into memory at once (which is memory-prohibitive for large files), the algorithm only reads into memory as far as necessary to find the next newline.
- **Persistence:** Using a static variable guarantees that any leftover data read past a newline character is retained and preserved for the subsequent call to `get_next_line()`.

---

## Instructions

### Compilation

You can compile `get_next_line` together with your main C program. The `BUFFER_SIZE` flag `-D BUFFER_SIZE=n` can be specified during compilation. If omitted, the default defined in `get_next_line.h` will be used.

**Mandatory Compilation Example:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

**Bonus Compilation Example (Multiple FD support):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Usage Example

Here is a minimal `main.c` example demonstrating how to use `get_next_line()`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

---

## Resources

### Documentation & References
- [Linux manual page for read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Understanding Static Variables in C - GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File Descriptors Explained - IBM Documentation](https://www.ibm.com/docs/en/aix/7.2?topic=concepts-file-descriptors)

### AI Usage Statement
In accordance with 42 AI guidelines, artificial intelligence was strictly used as a learning companion. AI tools were helpful in guiding me toward relevant documentation, explaining core concepts.

All core algorithm logic, memory handling, edge-case solutions, and actual project code were designed, reasoned through, and implemented entirely manually. This balanced approach ensured a strong foundational grasp of low-level C programming without compromising the problem-solving journey.