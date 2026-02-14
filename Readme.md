##
 # Copyright (C) 2025-2026 Mahdi Hosseini Asaad
 # For more information, please read LICENSE file.
##

# Parabyte Penix getopt
[![Version](https://img.shields.io/badge/Version-4.3-blue)]()
[![Project Mode](https://img.shields.io/badge/Mode-Public-green)]()

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



## Installation
There are several ways to install this library. Based on your requirements, you can proceed with one of the following methods to install the library:

- **Using the Pack Store :** 
    In the **pack store**'s search section, you can select the library option, search for the term pgetopt, and then proceed to download and install it.

- **Using pkg :** 
    You can install it by using the command `pkg` install `pgetopt-4` in your operating system's command line.

- **From Source Code :** 
    To compile directly from the source code, navigate to the source code folder and follow these commands:
    
    ```bash
    mkdir -p build && cd build
    cmake ..
    make
    make install
    ```

    To uninstall the library, in the same folder, after the `make` command, use `make uninstall`.

---
### Contact Us

You can find me on the following pages.

- **EMAIL :** [mahdi.libremann@gmail.com]()
- **Telegram :** [@libremann]()


---
### License
This project is developed and distributed under the GNU GPL-3.0 license. For more information, please read the LICENSE file.
