## Pgetopt E8: Masters
Throughout this tutorial, we've frequently referred to the concept of a **master**. Now it's time to implement it!

**Masters** also function as options that return all data that follows them in the command line!

This means that if **A** is defined as a master in the example below, all options that come after **A** are **not processed** by the parser and are returned as raw data:

```bash
command -l -a --key value A -f -r -w --add -l
```

---
First, we need to define the allowed masters. The **`palw`** structure comes to our aid for this. Each master is assigned an **`opt_id`**, which can be used repeatedly to achieve the **master cloning** capability.

The function `pinit_set_allowed_masters` initializes the `palw` data during the setup process.


Since a user cannot use multiple masters simultaneously, there's no need for a loop; a simple conditional structure like a **`switch-case`** is sufficient. The function `pinit_get_master_id` returns the `opt_id` of the master the user has employed.

Note that other options, such as **flags** and **keys**, will continue to function as expected.

If you use the `create` master in this example, the message "Create Master" will be printed. If you use `remove`, the message "Remove Master" will be printed.

```bash
$ ./example -o 1 -h create "This part is not processed."
Create Master
Output = 1
Help Page
```
```bash
$ ./example rm "This part is not processed."
Remove Master
```
```bash
$ ./example remove "This part is not processed."
Remove Master
```

## Pgetopt E8-1: Option in Master
Within the **`switch-case`** conditional structure, you can define options specific to the relevant master.

Example 8-1 demonstrates how to define these options.

> **Note:** The `pgetopt` library is inherently somewhat complex. Strive for **clean coding** to avoid compounding the difficulty of reading your code!

To maintain clarity, define the master's options in a **separate function** and call that function within the `switch-case` structure. In this example, we've used the function **`_create_func`** for the `create` master.

The function `_create_func` operates exactly like a standard **Unix application**. It receives the `argc` and `argv` parameters, and within the function, you can define a new `init` structure and parse the options specific to that function.

> **Tip:** This exercise might feel a bit tedious. Pay close attention to the application's structure and its output.


## Pgetopt E8-2: Master in Master
As we saw in **Section 8-1**, it's possible to define options like **classes**, **flags**, and **keys** *within* a master. The masters themselves are no exception to this rule!

We can create a **new master** inside an existing master, leading to a complex, nested structure—a **Master-in-Master** scenario.

The principle for creating a master inside the `_create_func` is the exact same as the one we learned for creating masters within the `main` function.