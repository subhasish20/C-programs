# File Handling in C - Complete Notes

---

## Introduction to File Handling

### What is a File?

A **file** is a collection of data stored on a secondary storage device (like a hard disk, SSD, or USB drive) that persists even after the program terminates. In C, files are treated as sequences of bytes.

```
┌─────────────────────────────────────────────┐
│                   FILE                      │
│  ┌───────────────────────────────────────┐  │
│  │  Byte  │ Byte  │ Byte  │ ... │ Byte  │  │
│  │   0    │   1   │   2   │     │  n-1  │  │
│  └───────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

### Why File Handling is Needed

| Need | Description |
|------|-------------|
| **Persistence** | Data survives program termination |
| **Data Storage** | Store large amounts of data permanently |
| **Data Sharing** | Exchange data between different programs |
| **Configuration** | Store program settings |
| **Logging** | Record program execution history |

### File vs RAM

| Aspect | RAM | File |
|--------|-----|------|
| **Persistence** | Volatile (data lost on power off) | Permanent (data persists) |
| **Speed** | Very fast (nanoseconds) | Slow (milliseconds) |
| **Size** | Limited (typically GBs) | Large (TB+ possible) |
| **Cost** | Expensive | Cheap |
| **Access** | Random access via pointers | Sequential/Random via functions |
| **Addressing** | Memory addresses | File positions/offsets |

### File Streams

A **stream** is a logical interface between the program and the file. It abstracts the physical details of the storage device.

```
┌─────────┐   Read/Write   ┌─────────┐   Physical   ┌─────────┐
│ Program │ ◄────────────► │ Stream  │ ◄──────────► │  File   │
│ (C code)│                │ (Buffer)│              │ (Disk)  │
└─────────┘                └─────────┘              └─────────┘
```

**Two types of streams:**
- **Text Stream**: Data is interpreted as characters (newlines may be translated)
- **Binary Stream**: Data is read/written exactly as-is

### FILE and FILE *

- **FILE**: An opaque data type (structure) defined in `<stdio.h>` that contains information about the file: buffer, position indicator, error flags, EOF flag, etc.
- **FILE\***: A pointer to a FILE structure. It's the handle used to access a file.

```c
FILE *fp;  // Declare a file pointer
```

> **Important**: You never need to know what's inside the FILE structure. Just use the pointer.

---

## Opening and Closing Files

### fopen()

**Definition**: Opens a file and creates a connection (stream) between the program and the file.

**Syntax**:
```c
FILE *fopen(const char *filename, const char *mode);
```

**Parameters**:
- `filename`: Path/name of file to open
- `mode`: String specifying how to open the file

**Return Value**: 
- Success: Pointer to FILE structure
- Failure: NULL

**Example**:
```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    printf("File could not be opened\n");
    return 1;
}
```

### fclose()

**Definition**: Closes the file and flushes any buffered data.

**Syntax**:
```c
int fclose(FILE *stream);
```

**Parameters**: File pointer to close

**Return Value**:
- Success: 0
- Failure: EOF (usually -1)

**Example**:
```c
if (fclose(fp) != 0) {
    printf("Error closing file\n");
}
```

### Checking NULL

Always check if `fopen()` returns NULL before using the file pointer.

```c
FILE *fp = fopen("file.txt", "r");
if (fp == NULL) {
    perror("Error opening file");
    exit(1);  // or handle gracefully
}
```

### How File Opening Works

```
┌──────────────┐      ┌──────────────┐      ┌──────────────┐
│    fopen()   │ ───► │  OS creates  │ ───► │  Returns a   │
│   called     │      │  file handle │      │   FILE *     │
└──────────────┘      └──────────────┘      └──────────────┘
                                                      │
                                                      ▼
                                             ┌──────────────┐
                                             │   Program    │
                                             │ uses fp to   │
                                             │ access file  │
                                             └──────────────┘
```

### File Modes - Complete Reference

| Mode | Read | Write | Create | Truncate | Initial Position |
|------|:----:|:-----:|:------:|:--------:|:----------------:|
| `"r"` | ✅ | ❌ | ❌ | ❌ | Beginning |
| `"w"` | ❌ | ✅ | ✅ | ✅ | Beginning |
| `"a"` | ❌ | ✅ | ✅ | ❌ | End |
| `"r+"` | ✅ | ✅ | ❌ | ❌ | Beginning |
| `"w+"` | ✅ | ✅ | ✅ | ✅ | Beginning |
| `"a+"` | ✅ | ✅ | ✅ | ❌ | End |
| `"rb"` | ✅ | ❌ | ❌ | ❌ | Beginning |
| `"wb"` | ❌ | ✅ | ✅ | ✅ | Beginning |
| `"ab"` | ❌ | ✅ | ✅ | ❌ | End |
| `"rb+"` | ✅ | ✅ | ❌ | ❌ | Beginning |
| `"wb+"` | ✅ | ✅ | ✅ | ✅ | Beginning |
| `"ab+"` | ✅ | ✅ | ✅ | ❌ | End |

### Mode Comparison Table

| Mode Group | Description | File Must Exist | Existing Content |
|------------|-------------|:---------------:|------------------|
| **Read** (`r`, `rb`) | Open for reading | ✅ Yes | Preserved |
| **Write** (`w`, `wb`) | Open for writing | ❌ No | Overwritten |
| **Append** (`a`, `ab`) | Open for appending | ❌ No | Preserved |
| **Read+Write** (`r+`, `rb+`) | Open for update | ✅ Yes | Preserved |
| **Write+Read** (`w+`, `wb+`) | Open for update | ❌ No | Overwritten |
| **Append+Read** (`a+`, `ab+`) | Open for update | ❌ No | Preserved |

**Important Points about Modes:**

- Mode **must** be a string literal
- `"r"` mode fails if file doesn't exist
- `"w"` mode creates file if it doesn't exist
- `"a"` mode creates file if it doesn't exist
- Text mode (`"r"`, `"w"`, etc.): newline translation may occur (`\n` ↔ `\r\n`)
- Binary mode (`"rb"`, `"wb"`, etc.): no translation, raw bytes

---

## Character-Based File Handling

### fgetc()

**Definition**: Reads a single character from a file.

**Syntax**:
```c
int fgetc(FILE *stream);
```

**Return Value**:
- Success: Character read as unsigned char cast to int (0-255)
- Failure or EOF: EOF (-1)

### fputc()

**Definition**: Writes a single character to a file.

**Syntax**:
```c
int fputc(int character, FILE *stream);
```

**Parameters**: Character to write (int, but only lower 8 bits are used)

**Return Value**:
- Success: Character written (as unsigned char cast to int)
- Failure: EOF (-1)

### getc() and putc()

- **getc()**: Same as `fgetc()` but implemented as a macro for speed
- **putc()**: Same as `fputc()` but implemented as a macro for speed

```c
int c = getc(fp);    // Equivalent to fgetc(fp)
putc('A', fp);       // Equivalent to fputc('A', fp)
```

### EOF (End of File)

`EOF` is a macro defined in `<stdio.h>` typically set to `-1`. It indicates:
- End of file has been reached
- An error occurred during reading

### Why fgetc() Returns int

```c
int c = fgetc(fp);
```

**Reasons:**
1. **To distinguish EOF**: If `char` is used, all values 0-255 are valid. Need a special value (-1) to indicate EOF.
2. **Signed/Unsigned char issues**: If `char` is unsigned on some systems, comparing with -1 would fail.
3. **Extended character sets**: Characters beyond 127 (ASCII) are properly handled.

**Example - Reading a file character by character:**

```c
FILE *fp = fopen("input.txt", "r");
if (fp == NULL) {
    printf("Cannot open file\n");
    return 1;
}

int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);  // Print to console
}

fclose(fp);
```

**Example - Writing characters to a file:**

```c
FILE *fp = fopen("output.txt", "w");
if (fp == NULL) return 1;

char text[] = "Hello World";
for (int i = 0; text[i] != '\0'; i++) {
    fputc(text[i], fp);
}

fclose(fp);
```

**Important Points:**
- `fgetc()` returns `int`, not `char`
- Always use an `int` variable to store the return value
- Check for EOF after the read, not before
- `fputc()` writes only the lower 8 bits of the integer

---

## String/Line-Based File Handling

### fgets()

**Definition**: Reads a line (or up to n characters) from a file.

**Syntax**:
```c
char *fgets(char *str, int n, FILE *stream);
```

**Parameters**:
- `str`: Buffer to store the read string
- `n`: Maximum number of characters to read (including null terminator)
- `stream`: File pointer

**Return Value**:
- Success: Pointer to `str`
- Failure or EOF: NULL

**Behavior**:
- Reads `(n-1)` characters maximum
- Stops when newline (`\n`) is encountered (includes it in the buffer)
- Stops when EOF is reached
- Always adds null terminator (`\0`)

**Example**:
```c
char buffer[100];
FILE *fp = fopen("file.txt", "r");
if (fp == NULL) return 1;

while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);  // buffer includes newline
}

fclose(fp);
```

### fputs()

**Definition**: Writes a string to a file.

**Syntax**:
```c
int fputs(const char *str, FILE *stream);
```

**Return Value**:
- Success: Non-negative value
- Failure: EOF (-1)

**Example**:
```c
FILE *fp = fopen("output.txt", "w");
if (fp == NULL) return 1;

fputs("Hello\n", fp);
fputs("World\n", fp);

fclose(fp);
```

### Newline and Buffer Behavior

| Aspect | Explanation |
|--------|-------------|
| **fgets() - Newline** | Stops reading at newline, includes `\n` in buffer, then adds `\0` |
| **fputs() - Newline** | Does NOT automatically add a newline; you must include `\n` explicitly |
| **Buffer Size** | Pass `sizeof(buffer)` to avoid overflow |
| **Input Buffer** | If input line is longer than `n-1`, fgets reads partial line and leaves rest for next call |

**Example - fgets behavior with newline:**

```c
char line[10];
fgets(line, 10, fp);

// If input line was "HelloWorld\n":
// Buffer: H e l l o W o r l \0   (9 chars + null)
// "d\n" remains in input stream
```

---

## Formatted File Handling

### fprintf()

**Definition**: Writes formatted output to a file, similar to `printf()`.

**Syntax**:
```c
int fprintf(FILE *stream, const char *format, ...);
```

**Return Value**:
- Success: Number of characters written
- Failure: Negative value

**Example**:
```c
FILE *fp = fopen("data.txt", "w");
if (fp == NULL) return 1;

int age = 25;
float salary = 75000.50;
char name[] = "Alice";

fprintf(fp, "Name: %s, Age: %d, Salary: %.2f\n", name, age, salary);

fclose(fp);
```

### fscanf()

**Definition**: Reads formatted input from a file, similar to `scanf()`.

**Syntax**:
```c
int fscanf(FILE *stream, const char *format, ...);
```

**Return Value**:
- Success: Number of input items successfully matched and assigned
- Failure: EOF (or fewer items than expected)

**Example**:
```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) return 1;

char name[50];
int age;
float salary;

int items = fscanf(fp, "Name: %s, Age: %d, Salary: %f", name, &age, &salary);
if (items == 3) {
    printf("Name: %s, Age: %d, Salary: %.2f\n", name, age, salary);
}

fclose(fp);
```

### Comparison with printf() and scanf()

| Function | Target | Source | Input/Output |
|----------|--------|--------|--------------|
| `printf()` | Console | Program | Output |
| `fprintf()` | File | Program | Output |
| `scanf()` | Program | Console | Input |
| `fscanf()` | Program | File | Input |

**Key Differences**:
- `printf()` and `scanf()` use `stdout` and `stdin` by default
- `fprintf()` and `fscanf()` take an additional file pointer parameter

### Return Values and Proper Usage

**For fprintf():**
```c
int chars_written = fprintf(fp, "Data: %d", value);
if (chars_written < 0) {
    // Error occurred
}
```

**For fscanf():**
```c
int items = fscanf(fp, "%d %s", &num, name);
if (items == 2) {
    // Successfully read both items
} else if (items == 1) {
    // Only read num, name reading failed
} else {
    // No items read (EOF or format mismatch)
}
```

**Important Points:**
- Always check return values
- `fscanf()` doesn't handle malformed input gracefully
- For complex parsing, `fgets()` + `sscanf()` is safer
- `fprintf()` might fail due to disk full, permissions, etc.

---

## Binary File Handling

### What is a Binary File?

A binary file stores data in the same format as it exists in memory (raw bytes), without any translation or formatting. There is no concept of lines, delimiters, or human-readable text.

```
Text file:    "1234"  → Bytes: 0x31 0x32 0x33 0x34
Binary file:  1234    → Bytes: 0x04 0xD2  (assuming 2-byte int)
```

### fread()

**Definition**: Reads a block of data from a file into memory.

**Syntax**:
```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
```

**Parameters**:
- `ptr`: Pointer to memory block to read into
- `size`: Size of each element (in bytes)
- `count`: Number of elements to read
- `stream`: File pointer

**Return Value**: Number of elements successfully read

**Example**:
```c
int numbers[10];
FILE *fp = fopen("data.bin", "rb");
if (fp == NULL) return 1;

size_t elements_read = fread(numbers, sizeof(int), 10, fp);

fclose(fp);
```

### fwrite()

**Definition**: Writes a block of data from memory to a file.

**Syntax**:
```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
```

**Parameters**:
- `ptr`: Pointer to data to write
- `size`: Size of each element (in bytes)
- `count`: Number of elements to write
- `stream`: File pointer

**Return Value**: Number of elements successfully written

**Example**:
```c
int numbers[] = {10, 20, 30, 40, 50};
FILE *fp = fopen("data.bin", "wb");
if (fp == NULL) return 1;

size_t elements_written = fwrite(numbers, sizeof(int), 5, fp);

fclose(fp);
```

### Storing Structures in Binary Files

```c
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

// Writing a structure
Employee emp = {101, "John Doe", 55000.50};
FILE *fp = fopen("employees.bin", "wb");
fwrite(&emp, sizeof(Employee), 1, fp);
fclose(fp);

// Reading a structure
Employee read_emp;
fp = fopen("employees.bin", "rb");
fread(&read_emp, sizeof(Employee), 1, fp);
fclose(fp);
```

### Important Limitations

#### 1. Structure Padding

```c
typedef struct {
    char c;    // 1 byte
    int i;     // 4 bytes
} MyStruct;    // Size might be 8 bytes (3 bytes padding), not 5!
```

**Solution**: Use `#pragma pack` or serialize manually.

```c
#pragma pack(1)
typedef struct {
    char c;
    int i;
} MyStruct;    // Now size = 5 bytes
#pragma pack()
```

#### 2. Platform Representation

| Issue | Problem | Solution |
|-------|---------|----------|
| **Endianness** | Different byte orders on different systems | Use standard formats, check at runtime |
| **Data Types** | Size of `int`, `long` varies across systems | Use fixed-width types (`int32_t`, `int64_t`) |
| **Pointers** | Pointers are meaningless in files | Store data, not pointers |

#### 3. Portability Issues

```c
// NOT portable
fwrite(&emp, sizeof(Employee), 1, fp);

// More portable approach
// Write each field separately with known sizes
fwrite(&emp.id, sizeof(int32_t), 1, fp);
fwrite(emp.name, sizeof(char), 50, fp);
fwrite(&emp.salary, sizeof(float), 1, fp);
```

**Endianness Example:**
```
Little Endian:  0x78 0x56 0x34 0x12  (for 0x12345678)
Big Endian:     0x12 0x34 0x56 0x78
```

---

## Text Files vs Binary Files

### Difference Table

| Aspect | Text Files | Binary Files |
|--------|------------|--------------|
| **Storage** | Human-readable characters | Raw bytes |
| **Newlines** | Converted (`\n` ↔ `\r\n`) | Not converted |
| **Data Representation** | ASCII/Unicode | Memory format |
| **Editable** | Yes (in text editor) | No (requires special tool) |
| **Size** | Typically larger | Typically smaller |
| **Portability** | Highly portable | Platform dependent |
| **Performance** | Slower (conversion overhead) | Faster |
| **Error Handling** | EOF detection simple | Must know structure |
| **Seeking** | Complex (variable line lengths) | Simple (fixed record sizes) |

### Which to Use?

| Use Text Files When | Use Binary Files When |
|---------------------|----------------------|
| Human readability needed | Performance is critical |
| Configuration files | Image/sound/video data |
| Cross-platform compatibility important | Large datasets |
| Simple data exchange | Need to store complex structures |
| Debugging/Logging | Memory mapping and direct access |

---

## File Position and Random Access

### File Position Indicator

Every open file has a **position indicator** that tracks where the next read/write will occur.

```
┌─────────────────────────────────────────────┐
│ File: data.txt                             │
│ ┌─────────────────────────────────────────┐ │
│ │ H │ E │ L │ L │ O │   │ W │ O │ R │ L │ │
│ └─────────────────────────────────────────┘ │
│       ▲                                     │
│       │                                     │
│   Position indicator (pointing to 'L')     │
└─────────────────────────────────────────────┘
```

### Sequential vs Random Access

| Access Type | Description | Movement |
|-------------|-------------|----------|
| **Sequential** | Read/write from start to end | Forward only |
| **Random Access** | Can read/write at any position | Forward/Backward |

### fseek()

**Definition**: Moves the file position indicator to a specified location.

**Syntax**:
```c
int fseek(FILE *stream, long offset, int origin);
```

**Parameters**:
- `stream`: File pointer
- `offset`: Number of bytes to move (can be negative)
- `origin`: Starting point for offset

**Origin Constants**:
| Constant | Value | Starting Point |
|----------|-------|----------------|
| `SEEK_SET` | 0 | Beginning of file |
| `SEEK_CUR` | 1 | Current position |
| `SEEK_END` | 2 | End of file |

**Return Value**:
- Success: 0
- Failure: Non-zero

### ftell()

**Definition**: Gets the current position of the file position indicator.

**Syntax**:
```c
long ftell(FILE *stream);
```

**Return Value**:
- Success: Current position (in bytes from beginning)
- Failure: -1L

### rewind()

**Definition**: Moves the file position indicator to the beginning of the file.

**Syntax**:
```c
void rewind(FILE *stream);
```

**Equivalent to**: `fseek(fp, 0, SEEK_SET);` plus clearing error flags.

### Examples

**1. Random Access using fseek():**

```c
// File contains integers 1, 2, 3, 4, 5
FILE *fp = fopen("numbers.bin", "rb");
int value;

// Read the 4th integer (index 3)
fseek(fp, 3 * sizeof(int), SEEK_SET);
fread(&value, sizeof(int), 1, fp);
printf("4th element: %d\n", value);  // Output: 4

fclose(fp);
```

**2. Determine file size:**

```c
FILE *fp = fopen("file.txt", "rb");
fseek(fp, 0, SEEK_END);
long size = ftell(fp);
printf("File size: %ld bytes\n", size);
fclose(fp);
```

**3. Move backward from current position:**

```c
// Read 10 bytes, then go back 5 bytes
char buffer[10];
fread(buffer, 1, 10, fp);           // Read 10 bytes
fseek(fp, -5, SEEK_CUR);            // Move back 5 bytes
fread(buffer, 1, 5, fp);            // Re-read last 5 bytes
```

**4. Rewind to beginning:**

```c
rewind(fp);  // Same as fseek(fp, 0, SEEK_SET);
// Now reading starts from beginning
```

---

## EOF and File Errors

### feof()

**Definition**: Checks if the end of the file has been reached.

**Syntax**:
```c
int feof(FILE *stream);
```

**Return Value**:
- Non-zero: EOF has been reached
- Zero: EOF not reached

### ferror()

**Definition**: Checks if an error occurred during file operations.

**Syntax**:
```c
int ferror(FILE *stream);
```

**Return Value**:
- Non-zero: Error occurred
- Zero: No error

### clearerr()

**Definition**: Clears the EOF and error indicators for the file.

**Syntax**:
```c
void clearerr(FILE *stream);
```

**Example**:
```c
if (ferror(fp)) {
    printf("Error occurred while reading\n");
    clearerr(fp);  // Clear error indicator
    // Handle error...
}
```

### Why while (!feof(fp)) is Wrong

**The Problem:**

```c
// WRONG - Don't do this!
while (!feof(fp)) {
    fscanf(fp, "%d", &num);
    // Process num
}
```

**Why it's wrong:**
1. `feof()` only becomes true **after** attempting to read past the end
2. The loop will process the last value twice
3. If there's a format mismatch, the loop becomes infinite

**Example of the bug:**

```c
// File contains: 10 20 30

int num;
while (!feof(fp)) {
    fscanf(fp, "%d", &num);
    printf("%d ", num);  // Output: 10 20 30 30  (last value twice!)
}
```

**Flow:**
```
1. Read 10 → feof() = false, process 10
2. Read 20 → feof() = false, process 20
3. Read 30 → feof() = false, process 30
4. Attempt to read next → EOF reached → feof() becomes true
   BUT we already processed the last read (30) before checking!
5. Loop condition checked at end: feof() is true → exit
   Wait, we processed 30 twice!
```

### Correct Ways to Read Files

**Method 1: Check the return value of read function**

```c
// For fgets()
char buffer[100];
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);
}

// For fscanf()
int num;
while (fscanf(fp, "%d", &num) == 1) {
    printf("%d ", num);
}

// For fgetc()
int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}
```

**Method 2: Read and check**

```c
char buffer[100];
while (1) {
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        // Check why we stopped
        if (feof(fp)) {
            printf("End of file reached\n");
        } else if (ferror(fp)) {
            printf("Error reading file\n");
        }
        break;
    }
    printf("%s", buffer);
}
```

---

## Buffering

### What Buffering Means

**Buffering** is the temporary storage of data in memory before writing to disk or after reading from disk.

```
Without Buffering:  Program → Disk (direct, slow)
With Buffering:     Program → Buffer → Disk (in chunks, fast)

┌─────────┐    Write    ┌─────────┐    Flush    ┌─────────┐
│ Program │ ──────────► │ Buffer  │ ──────────► │  Disk   │
│         │   (fast)    │ (RAM)   │   (chunks)  │ (slow)  │
└─────────┘             └─────────┘             └─────────┘
```

### Why Buffering is Used

| Reason | Explanation |
|--------|-------------|
| **Performance** | Disk I/O is slow; fewer disk operations = faster |
| **Efficiency** | Grouping small writes into larger blocks |
| **Reduced System Calls** | Each disk operation is a system call |

### fflush()

**Definition**: Forces any buffered data to be written to the file.

**Syntax**:
```c
int fflush(FILE *stream);
```

**Parameters**:
- `stream`: File pointer (or NULL to flush all output streams)

**Return Value**:
- Success: 0
- Failure: EOF (-1)

**Example**:
```c
FILE *fp = fopen("log.txt", "a");
fprintf(fp, "Important log message");
fflush(fp);  // Ensure it's written immediately
// Continue...
fclose(fp);
```

### Relationship Between Buffering and fclose()

When `fclose()` is called:
1. It automatically flushes any buffered data
2. Releases the file handle

```c
fprintf(fp, "Hello");
fclose(fp);  // "Hello" is automatically written to disk
```

### Important Limitations of fflush()

1. **Only output streams**: `fflush()` is undefined for input streams
2. **No guarantee**: Even after flushing, data might not physically reach disk (OS caching)
3. **Not for stdin**: Can't flush input buffer (use `getchar()` to consume)
4. **Performance**: Excessive flushing defeats the purpose of buffering

---

## File Management

### remove()

**Definition**: Deletes a file from the filesystem.

**Syntax**:
```c
int remove(const char *filename);
```

**Return Value**:
- Success: 0
- Failure: Non-zero

**Example**:
```c
if (remove("temp.txt") == 0) {
    printf("File deleted successfully\n");
} else {
    perror("Error deleting file");
}
```

**Important**: File must be closed before deletion on most systems.

### rename()

**Definition**: Renames a file (or moves it to another location).

**Syntax**:
```c
int rename(const char *oldname, const char *newname);
```

**Return Value**:
- Success: 0
- Failure: Non-zero

**Example**:
```c
if (rename("old.txt", "new.txt") == 0) {
    printf("File renamed successfully\n");
} else {
    perror("Error renaming file");
}
```

**Important Points:**
- If `newname` exists, behavior is platform-dependent
- Can move file to different directory if on same filesystem
- File must be closed before renaming

---

## Standard Streams

### stdin, stdout, stderr

These are predefined FILE pointers that are always available.

| Stream | Description | Normally Connected To |
|--------|-------------|----------------------|
| **stdin** | Standard input | Keyboard |
| **stdout** | Standard output | Console/Terminal |
| **stderr** | Standard error | Console/Terminal |

### Relationship with File Handling

These are just FILE pointers like any other:

```c
// Using stdout
fprintf(stdout, "Hello World\n");  // Same as printf()

// Using stdin
int num;
fscanf(stdin, "%d", &num);         // Same as scanf("%d", &num)

// Using stderr for errors
fprintf(stderr, "Error: Invalid input\n");
```

### Why stderr?

- **Separate stream**: Not buffered (or line-buffered)
- **Error messages**: Don't get lost or delayed
- **Redirection**: Can redirect output and errors separately

```bash
./program > output.txt 2> error.txt   # Redirect stdout and stderr separately
./program > output.txt 2>&1           # Redirect stderr to stdout
```

---

## Important File Handling Functions - Reference Table

| Function | Purpose | Syntax | Return Value |
|----------|---------|--------|--------------|
| `fopen()` | Open a file | `FILE *fopen(const char *path, const char *mode);` | `FILE*` or `NULL` |
| `fclose()` | Close a file | `int fclose(FILE *stream);` | `0` success, `EOF` error |
| `fgetc()` | Read a character | `int fgetc(FILE *stream);` | Character or `EOF` |
| `fputc()` | Write a character | `int fputc(int c, FILE *stream);` | Character or `EOF` |
| `getc()` | Read char (macro) | `int getc(FILE *stream);` | Character or `EOF` |
| `putc()` | Write char (macro) | `int putc(int c, FILE *stream);` | Character or `EOF` |
| `fgets()` | Read a string | `char *fgets(char *s, int n, FILE *stream);` | `s` or `NULL` |
| `fputs()` | Write a string | `int fputs(const char *s, FILE *stream);` | Non-negative or `EOF` |
| `fprintf()` | Formatted write | `int fprintf(FILE *stream, const char *fmt, ...);` | Chars written or negative |
| `fscanf()` | Formatted read | `int fscanf(FILE *stream, const char *fmt, ...);` | Items matched or `EOF` |
| `fread()` | Read binary block | `size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);` | Items read |
| `fwrite()` | Write binary block | `size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);` | Items written |
| `fseek()` | Seek in file | `int fseek(FILE *stream, long offset, int whence);` | `0` success, non-zero error |
| `ftell()` | Get current position | `long ftell(FILE *stream);` | Position or `-1L` |
| `rewind()` | Go to beginning | `void rewind(FILE *stream);` | (none) |
| `feof()` | Check EOF | `int feof(FILE *stream);` | Non-zero if EOF |
| `ferror()` | Check error | `int ferror(FILE *stream);` | Non-zero if error |
| `clearerr()` | Clear flags | `void clearerr(FILE *stream);` | (none) |
| `fflush()` | Flush buffer | `int fflush(FILE *stream);` | `0` success, `EOF` error |
| `remove()` | Delete file | `int remove(const char *filename);` | `0` success, non-zero error |
| `rename()` | Rename file | `int rename(const char *old, const char *new);` | `0` success, non-zero error |

---

## Revision Summary

### Core Concepts
- **File**: Persistent data storage on disk
- **Stream**: Interface between program and file
- **FILE***: Handle to access the file
- **Position indicator**: Tracks current read/write position

### Opening & Closing
- Always check if `fopen()` returns `NULL`
- Always `fclose()` when done
- Choose the right mode (`r`, `w`, `a`, with `+` or `b` variants)

### Reading/Writing
- **Character**: `fgetc()`/`fputc()` (return `int`, check `EOF`)
- **String**: `fgets()`/`fputs()` (safe with buffer size)
- **Formatted**: `fprintf()`/`fscanf()` (check return values)
- **Binary**: `fread()`/`fwrite()` (watch for padding/endianness)

### Positioning
- `fseek()` with `SEEK_SET`, `SEEK_CUR`, `SEEK_END`
- `ftell()` for current position
- `rewind()` to go to beginning

### Error Handling
- Check return values of all functions
- Use `feof()` correctly (check after read attempt, not before)
- Use `ferror()` for error detection
- `while (!feof(fp))` is WRONG

### Buffering
- Improves performance by batching I/O operations
- `fflush()` forces data to disk
- `fclose()` automatically flushes

### Text vs Binary
- Text: Human-readable, newline translation, slower
- Binary: Raw bytes, no translation, faster

### Portability Concerns
- Structure padding
- Endianness (byte order)
- Data type sizes
- Use fixed-width types for binary files

---
