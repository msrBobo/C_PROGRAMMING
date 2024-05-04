# Welcome to My Libasm
***

## Task

The problem I have is that I have a basic knowledge of assembly language.
and the problems in the project code were to eliminate the defects that arose during its use
My LibASM is a simple assembly library that contains the implementation of some commonly used string and memory manipulation functions.
 The library is written in NASM x86-64 assembly language and is designed to be compatible with both macOS and Linux.

## Description

My LibASM is a lightweight, efficient, and easy-to-use assembly library that provides implementations for a selection of
essential string and memory manipulation functions.
The library is written in NASM x86-64 assembly language, offering performance advantages and a deeper understanding of
low-level programming concepts.
This makes it an excellent choice for developers looking to optimize their code or learn assembly language.
My LibASM is compatible with both macOS and Linux, allowing for seamless integration into various projects.
By implementing these commonly-used functions in assembly, developers can leverage the full potential of their hardware and
gain valuable insights into how high-level programming languages interact with the underlying system.
My LibASM provides the following functions:
my_strlen - Calculate the length of a string
my_strchr - Locate the first occurrence of a character in a string
my_memset - Fill a block of memory with a specified value
my_memcpy - Copy memory area
my_strcmp - Compare two strings
my_memmove - Move block of memory
my_strncmp - Compare a specified number of characters of two strings
my_strcasecmp - Compare two strings ignoring case
my_index - Locate the first occurrence of a character in a string (alias for my_strchr)
my_read - Read from a file descriptor
my_write - Write to a file descriptor

## Installation

Installation
To install and use My LibASM in your projects, follow the steps below:
Clone the repository:
Open a terminal window and clone the My LibASM repository using the following command:
git clone https://github.com/yourusername/my_libasm.git
cd my_libasm
Assemble the library:
Assemble the assembly source files to create the object file:
For macOS:
nasm -fmacho64 my_libasm.asm -o my_libasm.o
For Linux:
nasm -felf64 my_libasm.asm -o my_libasm.o
This will create a file named my_libasm.o, which contains the compiled library.
Include the header file:
In your C/C++ code, include the my_libasm.h header file to access the functions provided by My LibASM:
#include "path/to/my_libasm.h"
Replace path/to/ with the actual path to the my_libasm.h file in your project directory.
Compile and link your code:
Compile your C/C++ code and link it with the assembled My LibASM object file using a compiler like gcc or clang:
gcc your_code.c path/to/my_libasm.o -o your_executable
Replace path/to/ with the actual path to the my_libasm.o file in your project directory, and your_code.c with the name of your C/C++ source file.
Run your executable:
After successfully compiling and linking your code, run the generated executable:
./your_executable
My LibASM is now installed and ready for use in your projects. Enjoy the benefits of low-level programming and performance optimization with this easy-to-use assembly library.

## Usage

To use any of the functions provided by My LibASM,
simply include the header file my_libasm.h in your C/C++ code:
For macOS:  nasm -fmacho64 my_libasm.asm -o my_libasm.o
For Linux:  nasm -felf64 my_libasm.asm -o my_libasm.o


### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
