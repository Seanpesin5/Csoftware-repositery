#include "myShell.h"
#include "myFunction.h"
int main() {
    welcome();
    while (1) {
        int piping = 0;
        getLocation();
        char *input = getInputFromUser();

        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        char **arguments = splitArgument(input);
        int isAppendCommand = 0, isOverwriteCommand = 0;
        for (int i = 0; arguments[i] != NULL; i++) {
            if (strcmp(arguments[i], ">>") == 0) {
                isAppendCommand = 1;
                break;
            } else if (strcmp(arguments[i], ">") == 0) {
                isOverwriteCommand = 1;
                break;
            }
        }
        if (isAppendCommand) {
            echoppend(arguments); // Handle the append operation
        } else if (isOverwriteCommand) {
            echorite(arguments); // Handle overwrite operation
        } else if (strcmp(arguments[0], "echo") == 0) {
            echo(arguments); // Handle the echo to terminal operation
        } else if (strcmp(arguments[0], "cd") == 0) {
            cd(arguments); // Change directory
        } else if (strcmp(arguments[0], "cp") == 0) {
            cp(arguments); // Copy files
        } else if (strcmp(arguments[0], "delete") == 0) {
            delete(arguments); // Delete files
        } else if (strcmp(arguments[0], "mv") == 0) {
            move(arguments); // Move files
        } else if (piping) {
            arguments[piping] = NULL;
            mypipe(arguments, arguments + piping + 1);
            wait(NULL);
        } else {
            systemCall(arguments);
            wait(NULL);
        }

        free(arguments);
        free(input);
    }
    return 1;
}
// יש לכתוב את פונקציית הברוכים הבאים כרצונכם אבל קצת יותר ממה שמוצג מטה לדוגמא:
//                     aSPY//YASa
//              apyyyyCY//////////YCa       |
//             sY//////YSpcs  scpCY//Pp     | Welcome to myShell
//  ayp ayyyyyyySCP//Pp           syY//C    | Version 2.4.3
//  AYAsAYYYYYYYY///Ps              cY//S   |
//          pCCCCY//p          cSSps y//Y   | https://github.com/<user>
//          SPPPP///a          pP///AC//Y   |
//               A//A            cyP////C   | Have fun!
//               p///Ac            sC///a   |
//               P////YCpc           A//A   | Craft packets like it is your last
//        scccccp///pSP///p          p//Y   | day on earth.
//       sY/////////y  caa           S//P   |                      -- Lao-Tze
//        cayCyayP//Ya              pY/Ya   |
//         sY/PsY////YCc          aC//Yp
//          sc  sccaCY//PCypaapyCP//YSs
//                   spCPY//////YPSps
//                        ccaacs
//                                        using c                                    using c
void welcome()
{
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*    SSSS   eee   aa  nn  n            *\n");
    printf("*   S      e   e a  a n n n            *\n");
    printf("*    SSS   eeeee aaaa n  nn            *\n");
    printf("*       S  e     a  a n   n            *\n");
    printf("*   SSSS    eee  a  a n   n            *\n");
    printf("*                                       *\n");
    printf("*****************************************\n");
    printf("Welcome to myShell\n");
    printf("have fun \n");
    printf("be happy\n");
    printf("Craft packets like it is your last day on Earth.\n");
    printf("-- Sean\n");
}
