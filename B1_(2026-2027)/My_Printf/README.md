<p align="center">
<img src="./ReadmeRessource2.svg" alt= "Banner" width="800" height="200" />
</p>

<br />

<div align="center">

<a href="https://koor.fr/C/Tutorial/Index.wp" target="_blank" rel="noopener">
  <img src="CBadge.svg" alt="Language C Badge" width="250" height="49" />
</a>

</div>

<br />
<br />
<br />
<br />
<br />
<br />

<div align="center">

# Printf

<br />

<img src="ReadmeRessource.jpg" alt="Picture of a Print" width="200" align="center">

<br/>

*"Picture of a Print"*

</div>

<br />
<br />

<div align="center">

## {🗂️}\ Summary

<br />

<h3>
  <a href="#context" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">Context</kbd>
  </a>
</h3>


<br />

<h3>
  <a href="#guide" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">Guide</kbd>
  </a>
</h3>

<br />

<h3>
  <a href="#more-information" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">More Information</kbd>
  </a>
</h3>

<br />

<h3>
  <a href="#download" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">Download</kbd>
  </a>
</h3>

<br />

<h3>
  <a href="#future" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">Future</kbd>
  </a>
</h3>

<br />

<h3>
  <a href="#credits" style="text-decoration: none;">
    <kbd style="font-size: 0.9em; padding: 0.3em 0.6em; font-weight: bold;">Credits</kbd>
  </a>
</h3>

<br />
<br />

> Clickable Buttons !

</div>

<br />
<br />


<div align="center">

<h2 id="context">{📚}\ Context</h2>

</div>

<br />

> ---
> 
>As part of the development of a **C-based software tool**, there is a need for a **custom mechanism for formatting and displaying data**.
>
>The goal is to **reproduce the essential features of the standard `printf` function** by implementing **data type conversions**, **variadic argument handling**, and **direct output to standard output using the `write()` system call**.
>
>This implementation provides a **deeper understanding of C language mechanisms**, including **variadic functions**, **numeric conversions**, and **modular code organization**.
>
>The project must also meet strict **compilation requirements**, using the following **compiler flags: `-Wall -Wextra -Werror`**.
>
> ---

<br />

<div align="center">

<img src="ReadmeRessource1.jpg" alt="Logo C" width="200" align="center">

<br />

*"C Language Logo"*


<br />
<br />

<h2 id="guide">{📖}\ Guide</h2>

</div>

<br />

><a href="https://koor.fr/C/Tutorial/Index.wp" target="_blank" rel="noopener">
>  <img src="CBadge.svg" alt="C Badge" width="250" height="50" />
> </a>
>
> <br />
>
>  ### " my_printf.c " : 
>
> This **block of code represents** the complete and modular implementation of the **custom my_printf function**. Here is the explanation of **what each part does**:
>
> The **main function, my_printf (The orchestrator)**: It is the **entry point of the program** that mimics the behavior of the standard printf function. It uses **`<stdarg.h>`** with va_start to capture and handle the variable arguments passed after the format string. It then iterates through the **string character by character**. If it encounters a **normal character**, it **writes it immediately** to the **standard output using `write()`**. If it encounters a **`%`**, it analyzes the following **specifier and redirects execution** to the corresponding **specialized function**. Finally, it **cleans up the context** with **`va_end`** and returns the **total number of characters written**.
>
> The **universal conversion engine (write_unsigned)**: This **recursive function** handles the display of all **unsigned numbers**, regardless of their base. It **divides the number** by the **base until a single digit** is obtained, which allows **displaying the digits** in the correct **order** without requiring a temporary **memory array**. It then picks the corresponding **character from the digit array** and **writes it using `write()`**.
>
> **Specialized type-specific functions (print_*)**:
>
>* **print_char (%c)**: Extracts a **character and writes it**.
> <br>
>
>* **print_str (%s)**: Extracts a **string and handles safety** if the **pointer is NULL** by neatly **displaying (null)**.
> <br>
>
>* **print_int (%d, %i)**: Handles **signed integers**, manages the **minus sign**, and casts to **long long** to **prevent overflow bugs** with **`INT_MIN`**.
> <br>
>
>* **print_unsigned (%u)**: Extracts an **unsigned integer** in base **`10`**.
> <br>
>
>* **print_octal (%o)**: Displays an **integer** in base **`8`**.
> <br>
>
>* **print_hex (%x)**: Displays an **integer** in **lowercase hexadecimal**.
> <br>
>
>* **print_pointer (%p)**: Converts a **memory address**, displays the **0x prefix**, and then the **hexadecimal value**.
>
>
> In summary, this **code ensures strict modularity** where each format has its own role and directly uses the **write system** call for efficient, **memory-leak-free management**.

```C
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>


int write_unsigned(unsigned long long n, int base, const char *digits) {
    int count = 0;
    
   
    if (n == 0) {
        if (write(1, &digits[0], 1) < 0) return -1;
        return 1;
    }

    if (n >= (unsigned long long)base) {
        int res = write_unsigned(n / base, base, digits);
        if (res < 0) return -1;
        count += res;
    }
    
    char c = digits[n % base];
    if (write(1, &c, 1) < 0) return -1;
    count++;
    
    return count;
}

int print_char(va_list *args) {
    char c = (char)va_arg(*args, int);
    if (write(1, &c, 1) < 0) return -1;
    return 1;
}

int print_str(va_list *args) {
    char *s = va_arg(*args, char *);
    if (!s) {
        s = "(null)";
    }
    int count = 0;
    while (s[count] != '\0') {
        if (write(1, &s[count], 1) < 0) return -1;
        count++;
    }
    return count;
}

int print_int(va_list *args) {
    int n = va_arg(*args, int);
    unsigned long long un;
    int count = 0;

    if (n < 0) {
        if (write(1, "-", 1) < 0) return -1;
        count++;
        
        un = (unsigned long long)(-(long long)n);
    } else {
        un = (unsigned long long)n;
    }
    
    int res = write_unsigned(un, 10, "0123456789");
    if (res < 0) return -1;
    
    return count + res;
}

int print_unsigned(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 10, "0123456789");
}

int print_octal(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 8, "0123456789");
}

int print_hex(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 16, "0123456789abcdef");
}

int print_pointer(va_list *args) {
    void *ptr = va_arg(*args, void *);
    uintptr_t addr = (uintptr_t)ptr;
    int count = 0;

    if (ptr == NULL) {
    
        char *null_str = "0x0";
        int i = 0;
        while (null_str[i] != '\0') {
            if (write(1, &null_str[i], 1) < 0) return -1;
            i++;
            count++;
        }
        return count;
    }

    if (write(1, "0x", 2) < 0) return -1;
    count += 2;

    int res = write_unsigned((unsigned long long)addr, 16, "0123456789abcdef");
    if (res < 0) return -1;
    
    return count + res;
}

int my_printf(char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    int total_written = 0;
    int i = 0;

    if (!format) {
        va_end(args);
        return -1;
    }

    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            if (format[i] == '\0') {
                break;
            }
            int res = 0;
            if (format[i] == 'd' || format[i] == 'i') {
                res = print_int(&args);
            } else if (format[i] == 'u') {
                res = print_unsigned(&args);
            } else if (format[i] == 'o') {
                res = print_octal(&args);
            } else if (format[i] == 'x') {
                res = print_hex(&args);
            } else if (format[i] == 'c') {
                res = print_char(&args);
            } else if (format[i] == 's') {
                res = print_str(&args);
            } else if (format[i] == 'p') {
                res = print_pointer(&args);
            } else if (format[i] == '%') {
                char c = '%';
                res = write(1, &c, 1);
            } else {
                char c = format[i];
                res = write(1, &c, 1);
            }

            if (res < 0) {
                va_end(args);
                return -1;
            }
            total_written += res;
        } else {
            if (write(1, &format[i], 1) < 0) {
                va_end(args);
                return -1;
            }
            total_written++;
        }
        i++;
    }

    va_end(args);
    return total_written;
}
```

<br />
<br />
<br />

> [!NOTE]
> ### How to use "my_printf()" function ?
>
> Since the final submission file **"my_printf.c"** intentionally does not contain a **main function** (to prevent **multiple definition errors** during **automated grading**), you need to **create a separate test file** **`*.c`** (**`test.c`** or **`main.c`**) in your **local directory to test and execute your code**.
>
> **Here is a complete guide and a code example showing how to test the function locally**:

```C
#include <stdarg.h>

/* 1. Declare the prototype of the custom my_printf function */
int my_printf(char *restrict format, ...);

int main(void) {
    /* Test 1: Simple string */
    my_printf("Hello, World!\n");

    /* Test 2: Signed integers and strings (%d, %s) */
    my_printf("Name: %s | Age: %d\n", "Elias", 18);

    /* Test 3: Characters, unsigned numbers, and hexadecimal (%c, %u, %x) */
    my_printf("Character: %c | Unsigned: %u | Hex: %x\n", 'Z', 42000, 255);

    /* Test 4: Pointers and escaped percentage (%p, %%) */
    int x = 42;
    my_printf("Address of x: %p | Success Rate: 100%%\n", (void *)&x);

    return 0;
}
```

<br />
<br />
<br />
<br />

<div align="center">

<h2 id="more-information">{🗞️}\ More Information</h2>

<br />

</div>

> ---
>
> #### my_printf Documentation & Reference Tables:
>
> This **document provides a complete technical breakdown** of the **`my_printf`** project using **structured reference tables**.
>
> <br>
>
> #### 1. Supported Format Specifiers
>
> | Specifier | Expected Argument Type | Description & Behavior |
> | :---: | :---: | :--- |
> | **`%d` / `%i`** | `int` | **Converts and prints** a **signed decimal integer** (**handles negative signs** and **`INT_MIN` protection**). |
> | **`%u`** | `unsigned int` | **Converts and prints** an **unsigned decimal integer**. |
> | **`%o`** | `unsigned int` | **Converts and prints** an **unsigned integer in base `8`** (**octal**). |
> | **`%x`** | `unsigned int` | **Converts and prints** an **unsigned integer in base 16** (**lowercase hexadecimal**). |
> | **`%c`** | `int` (**promoted from `char`**) | **Writes a single character** (**handles null byte `\0` properly**). |
> | **`%s`** | `char *` | **Writes a character string** (**safely handles `NULL` pointers** by **printing `(null)`**). |
> | **`%p`** | `void *` | **Writes a memory address** in **hexadecimal format prefixed with `0x`**. |
> | **`%%`** | *None* | **Escapes the percentage symbol** and **writes a literal `%`**. |
>
> <br>
>
> #### 2. Code Architecture & Function Roles
>
>| Function Name | Parameters | Core Responsibility (Macro to Micro) |
>| :--- | :--- | :--- |
>| **`my_printf`** | `(char *restrict format, ...)` | **Main Orchestrator:** Initializes **`va_list`**, parses the **format string**, and **dispatches tasks to specifier handlers**. |
>| **`write_unsigned`** | `(unsigned long long n, int base, const char *digits)` | **Universal Recursive Engine:** Converts and **writes unsigned numbers** in any base (**`8`**, **`10`**, **`16`**) without **dynamic memory arrays**. |
>| **`print_int`** | `(va_list *args)` | **Extracts a signed integer**, handles **minus signs**, and **prevents `INT_MIN` overflow** via **`long long` casts**. |
>| **`print_unsigned`** | `(va_list *args)` | **Extracts an unsigned integer** and **delegates base `10`** conversion to **`write_unsigned`**. |
>| **`print_octal`** | `(va_list *args)` | **Extracts an unsigned integer** and delegates **base `8`** conversion to **`write_unsigned`**. |
>| **`print_hex`** | `(va_list *args)` | **Extracts an unsigned integer** and delegates **base `16` conversion to **`write_unsigned`**. |
>| **`print_char`** | `(va_list *args)` | **Extracts and writes** a **single character** directly using **`write`**. |
>| **`print_str`** | `(va_list *args)` | **Extracts a string pointer**, guards against **`NULL`**, and **writes characters sequentially**. |
>| **`print_pointer`** | `(va_list *args)` | **Extracts a memory pointer**, writes the **`0x` prefix**, and **prints the converted address**. |
> 
> ---

<br>
<br>

> [!WARNING]
> **Before using:** Make sure to **compile the program first** by running:
> 
>*  **" `gcc -Wall -Wextra -Werror my_printf.c *.c -o my_printf` "**.    (**`*.c` is your test file that you created**). 
>
>in your terminal.
>
> To **uncompile the program** run the command:
> 
>*  **" `rm my_printf.exe` "** or **" `rm my_printf.out` "**

<br />
<br />

<div align="center">

<h2 id="download">{📥}\ Download</h2>

</div>

<br />

> ---
>
> #### Prerequisites:
> **Make sure** you have **installed** on your **system**:
>
> <br>
> 
> <a href="https://code.visualstudio.com/docs/cpp/config-mingw" target="_blank" rel="noopener">
>  <img src="GccBadge.svg" alt="GCC Badge" width="80" height="50" /> 
> </a>
> 
> <br>
> <br>
> <br>
> <br>
> 
> To **compile the project**, run the **terminal command**:
> * **" `gcc -Wall -Wextra -Werror my_printf.c *.c -o my_printf` "**.    (**`*.c` is your test file that you created**).
> 
> To **execute** the **program**:
> * **" `./my_printf.exe` "** or **" `./my_printf.out` "**.
> 
> The **project** can be directly downloaded on **GitHub**.
>
> ---

<br />
<br />
<br />

| File | Description | 
|:---:|:---:|
|**my_printf.c**| **Core implementation file** containing the **main function**, **variadic routing logic**, and **specialized conversion handlers** (**print_int, print_str, write_unsigned, etc.**).|

<br />
<br />
<br />

<div align="center">

```mermaid
flowchart TB

    Executable((my_printf.c))

    style Executable fill:#283593,stroke:#F5F5F0,stroke-width:2px,color:#fff

```

*"Project Composition"*

</div>

<br />
<br />

<div align="center">

<h2 id="future">{🌌}\ Future</h2>

</div>

</div>

<br />

> ---
>
> **While the current implementation covers all fundamental data types and base conversions, future iterations of my_printf can evolve to include**:
>
> * **Format Flags**: Support for **alignment (-)**, **forced signs (+)**, **alternative forms (#)**, **zero-padding (0)**, and **space padding**.
> <br>
>
> * **Width & Precision**: Dynamic field width and **precision constraints** (e.g., **controlling decimal places** or **string truncation limits**).
> <br>
>
> * **Internal Buffering**: Implementing a **memory write buffer** (similar to **standard streams**) to **minimize expensive system calls (write)** and boost **execution speed**.
> <br>
>
> * **Floating-Point Numbers**: Extending **compatibility** to **support %f, %e, and %g specifiers**.
>
> <br>
> <br>
>
> | Feature | Engineering Objective | Complexity Level |
> | :--- | :--- | :--- |
> | **Formatting Flags (`-`, `+`, `#`, ` `, `0`)** | **Implement left alignment**, **explicit positive signs**, **alternate base prefixes**, and **zero-padding**. | *Medium* |
> | **Width & Precision (`width`, `.precision`)** | **Control field width alignment** and **string/number truncation limits**. | *High* |
> | **Internal Buffering** | **Accumulate output** in a **4096-byte array** to reduce expensive **`write(2)` system calls**. | *High* |
> | **Floating-Point Numbers (`%f`, `%e`, `%g`)** | **Implement float/double formatting algorithms** without **using standard math libraries**. | *Very High* |
>
> ---

<br />
<br />

<div align="center">

<h2 id="credits">{📌}\ Credits</h2>

</div>

<br />

<p align="center">

<a href="https://github.com/EliasFCS" target="_blank" rel="noopener">
  <img src="CreditBadge.svg" alt="EliasFCS Badge" width="450" height="54" />
</a>