# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.
  

## Pgetopt E7: Error Management
Error management has always been, and continues to be, one of the most crucial parts of the computing world. In **pgetopt**, errors are divided into two categories: **`user_error`** and **`pgetopt_error`**.

The **`pgetopt_error`** is related to mistakes made by the project's **programmer** (and they should be executed!).
This means that when this error occurs, the software **aborts** and the error message is printed.

However, the **`user_error`** is related to mistakes made by the **user**, and its management is entirely up to the programmer.

A **`user_error`** does not cause the program to fail on its own, but the programmer is free to **handle these errors however they wish**.

The **`pinit_parser`** function, when parsing user options, returns a value of type **`usrerr`** if an error exists. This type is a **`typedef`** of a multi-field structure and **does not need to be freed**.

To simplify error management, the **pgetopt** library provides the **`usererror_parser`** function. You must pass your **`usrerr`** variable and the program's **`argv`** to it. This function will issue the appropriate error message, if necessary, and return the value **`1`**. If no error exists in `usererr`, it returns **`0`**.

For **manual management of user errors**, the **`usrerr`** contains a field named **`error`**. The `error` field is an integer that returns the **type of error as a number**. You can see the error types based on their numbers below:

| int | #Define Macro | Description |
| --- | --- | --- |
| 0   | _without_error | There is no error |
| 1   | _invalid_option | An Option was user that does not exist. Or the option was user incorrectly. |
| 2   | _key_without_value | The key has no value or its value start with - or @, which is invalid. |
| 3   | _lack_of_class | The user used a class that does not exist. |
| 4   | _class_syntax_error | The user is trying to use the class incorrectly. For example, they forgot the '.' |
| 5   | _invalid_value | The user uses a value for a specific key that is not allowed. This means that the programmer has declared it not allowed. |
| 6   | _lack_of_master | The user used a master that does not exist. |