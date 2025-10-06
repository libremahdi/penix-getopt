# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.

## Pgetopt E1: main class

Think of classes like a classroom where different students gather to waste their time!

All those students gather in the class because of a common characteristic. They all study a specific major in that class.

In `pgetopt`, options such as `flags` or `keys` can also be grouped inside a `class`, and this categorization prevents conflicts and clashes between options with the same name but different functionalities.

- **Example:**

    There is an option named `create`. But what does it create? That’s exactly what classes are for! If you set create in a class named `user`, the user understands that this option creates a `user`. If you implement it in a class named    `group`, the user realizes that the goal is to create a `group`.

Before all this, we need to have a `main class`. The main class is for all those options that don’t fit into any specific category or that the programmer does not intend to categorize! For example, options like help and version don’t belong to any particular class.

Although you must define a main class, it is not necessary to create any option inside it (an empty class).

### Functions

The function `pclass_create` creates an empty class where the first parameter is init and the second parameter is the name of the `class` you want to create.

The function `pinit_set_main_class` sets any desired class as the main class.

#### Memory Deallocation

Classes also need to be freed. But not just any kind of freeing! The function `pclass_free` makes this possible!