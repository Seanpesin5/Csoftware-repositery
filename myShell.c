#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome();

  
        getLocation();
        //char *input = getInputFromUser();
        // cp\0<file>\0<file>\0
        // cp <file> <file>\0
        // [cp, <file>, <file> ]
        // [input,input+3,input+10]

        //char **arg = splitArgument(input);
       // int i = 0;
        //while (*(arg + i) != NULL)
        //{
         //   puts(arg[i]);
          //  i++;
       // }

       // if (strcmp(input, "exit") == 0)
       // {
      //      free(arg);
        //    free(input);
       //     puts("log out");
       //     break;
       // }



        
      //  free(arg);
      //  free(input);
   /// }
    return 0;
//}
    }
void welcome()
{
    puts("Welcome to sean's epic Shell");
}