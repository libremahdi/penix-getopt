# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.
  

## Pgetopt E0: init

The `init` will be the starting point of the library and a constant fixture in all your projects. `pinit` is a type of variable, and is essentially a simple typedef of a struct in the C language.

The `pinit_create` function creates an pinit and initializes it. Finally, it returns the address of that init. Therefore, we must always use a pointer variable of type pinit :

```C
pinit *my_init = pinit_create ();
```

---
### Memory Deallocation

The `pinit` function reserves space on the heap. Therefore, we shouldn't forget to `free` it."

But wait! Is the standard `free` function sufficient? No!

This is because pinit is a struct whose fields, in turn, also reserve space on the Heap. We need another function to free them as well! Its name is `pinit_free`:

```C
pinit_free ( my_init );
```