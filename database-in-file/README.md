# Low Level Academic Database (LLAD)

## Project Overview

This project implements a simple database system in C, demonstrating low-level file operations, binary data manipulation, and command-line interface design. The database simulates some functionalities similar to SQLite, offering insights into how database systems manage data at a low level.

## Key Features

- Custom binary file format for data storage
- CRUD operations (Create, Read, Update, Delete) on employee records
- Command-line interface for database interactions
- File descriptor management for low-level file I/O
- Binary data parsing and manipulation

## What I Learned

### 1. Binary File Structures

- Understood how binary files are structured for efficient data storage, similar to format specifications like MP3 or PNG
- Implemented a custom file header (`struct dbheader_t`) to manage database metadata
- Learned about magic numbers for file type identification (e.g., `HEADER_MAGIC 0x4c4c4144`)

### 2. Low-Level File Operations

- Used system calls like `open()`, `read()`, `write()`, and `lseek()` for file manipulation
- Implemented file descriptor management for database operations

### 3. Data Structures and Memory Management

- Designed structures for database header (`dbheader_t`) and records (`employee_t`)
- Used dynamic memory allocation (`malloc()`, `realloc()`) for managing record storage
- Learned about heap memory management in C

### 4. Binary Data Parsing

- Implemented functions to read and write binary data
- Handled endianness issues using network-to-host order conversions (`ntohl()`, `ntohs()`)

### 5. Command-Line Interface Design

- Used `getopt()` for parsing command-line arguments
- Implemented a user-friendly CLI for database operations

### 6. Database Concepts and Debugging

- Simulated basic database operations similar to SQLite
- Learned about database file structures and binary data representation
- Used debugging tools like `xxd` to analyze and inspect binary file contents
- Gained insights into how database systems manage and structure data at a low level

## Project Structure

- `main.c`: Entry point and CLI logic
- `file.c`: File operations (create, open, read, write)
- `parse.c`: Data parsing and manipulation functions

## Sparked Interests

This project ignited my curiosity in various areas of low-level programming and hardware:

- Microcontrollers and embedded systems (e.g., STM32 Nucleo board)
- [Bare metal programming](https://youtube.com/playlist?list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ&si=CA1vNJzEHFMnzy35)
- Modern systems programming languages (Rust, Zig)
- Hardware hacking tools (Flipper Zero)
- Microchip architecture and design

While these topics aren't directly related to the database project, they demonstrate how diving deep into one area of systems programming can lead to a broader interest in low-level computing and hardware.

## Future Goals

1. Web Server Integration
   - Combine this database system with a custom-built web server
   - Implement threading for concurrent database operations
   - Create a full-stack C application demonstrating both backend and frontend skills

2. Embedded Database
   - Adapt the database system to run on a microcontroller
   - Optimize for constrained environments
   - Explore real-time database operations in embedded systems

These future directions aim to expand the project's scope, combining database management with web technologies and embedded systems, showcasing a comprehensive understanding of systems programming.

## Conclusion

This database project served as a gateway to a wide array of low-level programming concepts and system design principles. Beyond providing hands-on experience with file I/O and basic database operations, it ignited a passion for exploring the deeper layers of computing systems.

Through this project, I gained practical experience in manipulating binary data, managing file structures, and implementing fundamental database operations. However, the true value lies in how it sparked curiosity about related fields. It led me to investigate microcontrollers, explore bare-metal programming, and delve into modern systems languages like Rust and Zig.

Looking ahead, I've got some big plans. I want to hook this database up to a web server (which I built too, by the way!), and maybe even shrink it down to run on tiny computers. It's like I'm building my own mini tech world! It's amazing how one project can lead you down so many exciting paths.

This project has reinforced that curiosity and willingness to explore are invaluable assets in software development. It's a testament to the power of hands-on learning and the exciting possibilities that unfold when you dive deep into the foundations of computer systems. 