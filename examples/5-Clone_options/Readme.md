## Pgetopt E5: Clone Options
We've reached the interesting and simple section of **pgetopt**! The entire concept is summarized as follows:

You can assign the **same `opt_id`** to **multiple options**. In **palw**, when you set values for options like **Masters** or **flags/keys**, you can use a single `opt_id` for several options.

Pay attention to the example in this exercise, which shows how the same `opt_id` is assigned to Masters and other options.
To avoid unnecessary complication of the exercise, no example has been provided for **`clone_master`s**. You can create your own clone masters by drawing inspiration from the `palw` example.

**Note**: In the **`while` loop**, when analyzing user inputs, be mindful that a specific **`opt_id`** corresponds to **multiple options**.