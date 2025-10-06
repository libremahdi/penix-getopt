# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.

## Pgetopt E3: implementing parsing

Thus far, we've managed to create a `main class` and generate a series of options referred to as `flags`. However, we still haven't been able to process the user's **arguments**. We will achieve that in this example!

The first step after defining the flags and passing them to the target class via the `pclass_set_allowed_options` function is to also send the user's arguments to `pgetopt`. This enables it to recognize which option the user is currently employing. The function `pinit_parser` is responsible for performing exactly this task for us.

As mentioned before, `init` is a `typedef` to a tree structure within pgetopt. This tree has several branches. Two of them are named `palw` and `pavl`. `palw` stores the allowed options—information provided by the programmer during the software's construction. `pavl` stores the options that the user has entered.

The function `pinit_parser` initializes the **pavl** structure.


### Parsing Arguments!

The `pinit_parser` function compares the data entered by the user **(pavl)** with the allowed data **(palw)**. If a discrepancy exists, it returns an error structure, which we won't focus on for now.

However, this isn't enough! We still don't know what data the user has actually entered!

The function `pclass_loop_get_opt_id` helps us figure out which data the user has passed as arguments to the software. This function returns the `opt_id` for every option the user has utilized. This function should be reused for each `class`, but since we have only defined one class so far, we won't concern ourselves with that issue yet.

The function `pclass_loop_get_opt_id` must be used within a `while` loop, and if the list of user options reaches its end, this function returns the value `-1`. Since an `opt_id` cannot be a negative number, we can be confident in this approach!

It's better to control the scope (lifetime) of variables dependent on `pclass_loop_get_opt_id` using curly braces {} to prevent potential issues. Note the following code (or concept):

```C
// The upper codes!
    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 )
        {
            switch ( opt_id )
            {
                case (1): // The number 1 is merely a simple identifier of option! (opt_id).
                    printf ("this is long_flag\n");
                    break;
                case (2):
                    printf ("this is f\n");
                    break;
            }
            ++i;
        }
    }
// The lower codes!
```