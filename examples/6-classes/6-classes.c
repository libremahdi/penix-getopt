#include <pgetopt-4.3/pgetopt.h>

#include <stdio.h> // just for printf :)

int main ( int argc, char **argv )
{
    pinit *init = pinit_create ();
    
    pclass *class = pclass_create ( init, "mahdi" );
    
    pinit_set_main_class ( init, class );

    palw main_allowed_options [] = {
        { 1, "long_flag" },
        { 2, "f" },
        EOL
    };

    pclass_set_allowed_options ( class, main_allowed_options );
    
    pclass *user = pclass_create ( init, "user" );
    palw user_allowed_options [] = {
        { 1, "create" },
        { 2, "remove" },
        EOL
    };
    pclass_set_allowed_options ( user, user_allowed_options );       
    
    pinit_parser ( init, argc, argv );

    {
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( class, i ) ) != -1 ) 
        {
            switch ( opt_id )
            {
                case (1):
                    printf ("this is long_flag\n");
                    break;
                case (2):
                    printf ("this is f\n");
                    break;
            }
            ++i;
        }
    }
    

    { // `pclass *user` parsing segment
        int opt_id, i=0;
        
        while ( ( opt_id = pclass_loop_get_opt_id ( user, i ) ) != -1 )
        {
            switch ( opt_id )
            {
                case (1): // The number 1 is merely a simple identifier of option! (opt_id).
                    printf ("this is Create\n");
                    break;
                case (2):
                    printf ("this is Remove\n");
                    break;
            }
            ++i;
        }
    }

    pclass_free (class);
    pclass_free (user);
    pinit_free (init);
}

/* Example Export :
 * If you provide no arguments to the software, you should see no output.

 $ ./example -f --long_flag @user.create @user.remove
 this is f
 this is long_flag
 this is Create
 this is Remove

 * You can also call the class that you have defined as main using @
 * For example, in this exercise, we used "mahdi" as the name of the class defined as main, 
   unlike the previous exercises.
 * Therefore, you can access the options of the mahdi class both without the @ and with the @. 
   The two structures are completely identical :

 $ ./example -f
 this is f

 $ ./example @mahdi.f
 this is f

 * The current example does not perform any error handling, so no user errors are issued.
*/