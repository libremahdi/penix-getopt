# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.

## Pgetopt E2: flags

Options that do not take any input are called `flags`. Flags notify the software of a specific status. In this example, the option `-f` is a flag. Flags can be single-letter or multi-letter. Any option that is a single letter is called a `short option`, and any option with multiple letters is called a `long option`. Short options can start with either `-` or `--`, but long options must always start with `--`.

### Functions

The function `pclass_set_allowed_options` is used to define `flag` and `key` options. As its name suggests, **this function requires classes, not init!**

The programmer must send the flags they want to be available to this function in a structure called palw.

`palw` is a typedef of an internal structure in `pgetopt`. The code below demonstrates how to create and initialize a palw :

```c
    palw variable_name_you_want [] =  {
    //  { opt_id, opt_name },
        { 1, "option_one" },
        { 2, "option_two" },
        EOL
    };
```

### Warnings
- The first part is called opt_id, which is a natural number. It must be zero or a positive integer. You cannot use negative or fractional numbers.


- The second part is called opt_name, which is the name of the option you want to define. You are not allowed to use spaces, but if you do, no error will be raised unless you compile your software with the PDEBUG flag.

- Don’t forget EOL. This is a macro that indicates the end of your list. If you forget it, who knows what might happen!


> Here, we have only defined a series of options. Don’t expect anything to happen or for your software to produce any specific output!