# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.
  

## Pgetopt E6: Classes
In this exercise, we are going to create and use a **new class, separate from `main`**. I recommend looking at this exercise carefully!

In this exercise, we have created two class variables. One is named **`'class'`** and the other is named **`'user'`**.
To make things a bit more challenging for you, we set the name of the **`'class'`** class to **`'mahdi'`**.
And the name of the **`'user'`** class to **`'user'`**.

The class name is a simple string that we send to **`pclass`** so that the user can utilize the options within that class.

It has been used in **`palw`**: one for **`'class'`** and one for **`'user'`**.

For each class, we must use the function **`pclass_set_allowed_options`** to initialize that class with the `palw` data.

Finally, after parsing the arguments with the **`pinit_parser`** function, we used **two `while` loops** for the classes: one for **`'class'`** and one for **`'user'`**.

It's best to control the lifetime of the variables dependent on the `while` loop—namely the variables **`i`** and **`opt_id`** in this example—by using the **`{}`** structure. Pay attention to the exercise's source code!

Also, be sure to pass the corresponding class variable to the **`pclass_loop_get_opt_id`** function for each class. Note the following example:

```C
// for 'class' class
pclass_loop_get_opt_id ( class, i )
```

```C
// for 'user' class
pclass_loop_get_opt_id ( user, i )
```