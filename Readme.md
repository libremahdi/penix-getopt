# Parabyte Penix getopt
[![Version](assets/version.svg)]()
[![Project Mode](assets/Mode.svg)]()
[![Project Owner](assets/Owner.svg)]()

## Introduction

Every console utility used in Unix-like operating systems employs various methods for user interaction. Consequently, there is a clear need for a comprehensive and consistent standard that helps users predict and understand how to interact with all command-line tools.

Pgetopt is a C language library designed to address this need by providing robust management and parsing of command-line arguments and options. Its structure and syntax strictly adhere to the PENIX Standard.

> Pgetopt is an acronym for PENIX Getopt.

---

## Basic Concepts

The library uses several basic concepts to parse user inputs. Here, any form of input that is not a key-value pair is called an option. All options in pgetopt have an opt_id.

You can assign the same opt_id to multiple options, which we call clone options.

Options are divided into several categories:

- **Flags :**

    These are options that do not take any input but inform the software of a specific state. For example, the flag -c or --create indicates that the goal is to create, and the flag -d or --delete indicates that the goal is to delete.


- **Keys :**

    Keys are options that always require an input. The input for keys is called a Value. Values must be valid, and whether a value is valid or not is determined by the developer (you).

- **Masters :**
    Masters are options different from keys and flags. Their management is the programmer's responsibility. Masters return all options that follow them. A simple and popular example is the commit section in the command `git commit -m "LOL"`. 
    
    In the pgetopt library, the commit section in the git command is called a Master.



## Features

- ✨ **Clean structure:** Uses headings, lists, and separators effectively
  
- 🖋️ **Consistent typography:** Emphasis with bold & italics
  
- 💻 **Code blocks:** Proper syntax highlighting and inline code
  
- 🔗 **Links and references:** Clear navigation within the document
  
- 📌 **Notes and warnings:** Highlight important info with blockquotes
  

---

## Usage

1. Clone the repository
  
2. Customize the content sections
  
3. Add your code snippets or documentation
  
4. Share or publish with confidence
  

---

## Code Example

```python
def greet(name: str) -> str:

"""

Returns a greeting message.

"""

return f"Hello, {name}! Welcome to the professional Markdown template."



print(greet("User"))
```

How to compile your application via Gcc and Pgetopt:

gcc -g -O0 <source.c> -o -L/usr/local/lib -lpgetopt -Wl,-rpath,/usr/local/lib# Parabyte Penix getopt

## Introduction

Every console utility used in Unix-like operating systems employs various methods for user interaction. Consequently, there is a clear need for a comprehensive and consistent standard that helps users predict and understand how to interact with all command-line tools.

Pgetopt is a C language library designed to address this need by providing robust management and parsing of command-line arguments and options. Its structure and syntax strictly adhere to the PENIX Standard.

> Pgetopt is an acronym for PENIX Getopt.

---

## Basic Concepts

The library uses several basic concepts to parse user inputs. Here, any form of input that is not a key-value pair is called an option. All options in pgetopt have an opt_id.

You can assign the same opt_id to multiple options, which we call clone options.

Options are divided into several categories:

- **Flags :**

These are options that do not take any input but inform the software of a specific state. For example, the flag -c or --create indicates that the goal is to create, and the flag -d or --delete indicates that the goal is to delete.

```c
dfsdf
```

- **Keys :**

Keys are options that always require an input. The input for keys is called a Value. Values must be valid, and whether a value is valid or not is determined by the developer (you).

## Features

- ✨ **Clean structure:** Uses headings, lists, and separators effectively
  
- 🖋️ **Consistent typography:** Emphasis with bold & italics
  
- 💻 **Code blocks:** Proper syntax highlighting and inline code
  
- 🔗 **Links and references:** Clear navigation within the document
  
- 📌 **Notes and warnings:** Highlight important info with blockquotes
  

---

## Usage

1. Clone the repository
  
2. Customize the content sections
  
3. Add your code snippets or documentation
  
4. Share or publish with confidence
  

---

## Code Example

```python
def greet(name: str) -> str:

"""

Returns a greeting message.

"""

return f"Hello, {name}! Welcome to the professional Markdown template."



print(greet("User"))
```

How to compile your application via Gcc and Pgetopt:

gcc -g -O0 <source.c> -o -L/usr/local/lib -lpgetopt -Wl,-rpath,/usr/local/lib