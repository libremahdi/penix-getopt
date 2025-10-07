# Pgetopt Examples

Here, we'll examine examples related to the pgetopt library.

- Pay attention to the documentation!
  
- don't forget to compile!
  
- Perform the exercises sequentially because each example depends on the preceding examples.
  

## Pgetopt E4: keys
We’ve reached the crime section of the story!  
Every option defined in the palw structure and set by the function `pclass_set_allowed_options` is, by default, of type flag until it is converted to a key by the function `pclass_set_key`.  
This function has three parameters. The first parameter is the address of the class, the second parameter `opt_id` is the option we want to convert into a key, and finally, the third parameter is the key type, which in this example is `NONE`. This means it has no specific type and is a regular key that accepts any type of value.  

To iterate over the values entered by the user, two functions help us.  
The function `pclass_get_key_size` returns the number of values for a key, and the function `pclass_key_loop_get_value` returns the value itself.  

Combining these two in a `for` loop enables iteration:

```C
for ( int vi=0 ; vi < pclass_get_key_size ( class, opt_id ) ; ++vi )
    {
        printf ( "k = %s\n", pclass_key_loop_get_value ( class, opt_id, vi ) );
    }
```

## Pgetopt E4-1: ALW_CUSTOM
`ALW_CUSTOM` is a simple enum that assigns a style to the intended key.  
For example, in the previous exercise, `NONE` indicates that the key accepts any value, but with `ALW_CUSTOM`, we can specify that only values we define are accepted, and in other cases, an error is issued.  

The function `pclass_set_key` returns a typedef called `pkey`, and since it is a typedef, there is no need to free it.  
In the `NONE` style, there is no need to store the return value of the function, but in other styles, it should be stored in a variable of type `pkey`.  

To specify allowed values, we use the function `pkey_set_custom_value`, which takes the `pkey` and the desired value.  
For each value, this function should be called once.


## Pgetopt E4-2: DENY_CUSTOM
The third style, `DENY_CUSTOM`, works exactly opposite to `ALW_CUSTOM` and blocks the values we enter,  
preventing the user from using such values as a `value`.
