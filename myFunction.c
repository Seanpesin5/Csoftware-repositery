#include "myFunction.h"

char *strwok(char *str, const char *delim) {
    static char *next_token = NULL;
    if (str) next_token = str; // Initialize on first call
    if (!next_token || *next_token == '\0') return NULL; // End of string

    char *token_start = next_token; // Start of the next token
    char *current; // Current character being checked

    // Skip leading delimiters
    for (current = next_token; *current != '\0'; current++) {
        const char *d;
        for (d = delim; *d != '\0'; d++) {
            if (*current == *d) {
                
                token_start++;
                break;
            }
        }
        if (*d == '\0') break; // Found the start of a token
    }  
    if (*token_start == '\0') {
        next_token = token_start; // Prepare for the next call to return NULL
        return NULL;
    }
    next_token = token_start; // Begin searching for the end of the token
    for (current = token_start; *current != '\0'; current++) {
        const char *d;
        for (d = delim; *d != '\0'; d++) {
            if (*current == *d) {
                
                *current = '\0'; // Terminate the token
                next_token = current + 1; // Set up for the next token
                return token_start; // Return the current token
            }
        }
    }

    // Reached the end of the string
    next_token = current; // No more tokens
    return token_start; // Return the last token
}
char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size * sizeof(char));
    }
    *(str + index) = '\0';

    return str;
}
char **splitArgument(char *str)
{
    // str = cp file file file
    //[cp,file,file,file,NULL]
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strwok(str, " ");
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = strwok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(argumnts + index) = subStr;
        argumnts = (char **)realloc(argumnts, size * sizeof(char *));
    }
    *(argumnts + (index + 1)) = NULL;

    return argumnts;
}
void getLocation() {
    char location[BUFF_SIZE];
    char hostname[BUFF_SIZE];
    char *username = getenv("USER"); // On Unix-like systems; use "USERNAME" for Windows

    if (getcwd(location, BUFF_SIZE) == NULL) {
        perror("Error retrieving current directory");
        return;
    }

    if (gethostname(hostname, BUFF_SIZE) != 0) {
        perror("Error retrieving hostname");
        return;
    }

    if (username == NULL) {
        fprintf(stderr, "Error retrieving username\n");
        return;
    }

    bold();
    blue();
    printf("%s@%s:%s", username, hostname, location);
    reset();
    printf("$ ");
}

// Function to simulate logout
void logout(char *input)
{
    free(input);
    puts("log out");
    exit(EXIT_SUCCESS); // EXIT_SUCCESS = 0
}
void echo(char **arg)
{
    // int i = 1;

    // while (arg[i] != NULL)
    //     printf("%s ", arg[i++]);
    // while (*(arg + i) != NULL)
    //     printf("%s ", *(arg + i++));
    // while (*(arg + i))
    // {
    //     printf("%s ", *(arg + i));
    //     i++;
    // }
    while (*(++arg))
        printf("%s ", *arg);
    puts("");
}
// יש לטפל במקרים בהם מקבלים נתיב המכיל רווחים, תזכרו - נתיב כזה צריך להיות מסומן בגרשיים ולכן יש לוודא זאת ואם הוא אכן כזה
// שמכיל סוגריים אז יש לבנות מחרוזת חדשה שאותה יש לשלוח לפונקציה שמשנה נתיב לתהליך.

void cd(char **arg) {
    char path[1024] = {0}; // Adjust size as needed

    if (arg[1] == NULL) {
        printf("-myShell: cd: missing operand\n");
        return;
    }

    // Direct handling for "cd .."
    if (strcmp(arg[1], "..") == 0 && arg[2] == NULL) {
        if (chdir("..") != 0) {
            perror("-myShell: cd: error changing to parent directory");
        }
        return;
    }

    // For quoted paths or paths without spaces
    if (arg[1][0] == '\"') {
        // Quoted path
        strncpy(path, arg[1] + 1, sizeof(path) - 1); // Copy without the leading quote
        size_t path_len = strlen(path);
        if (path[path_len - 1] == '\"') {
            path[path_len - 1] = '\0'; // Remove trailing quote
        } else if (arg[2] != NULL) { // Handle case where path is split across arguments
            for (int i = 2; arg[i] != NULL; i++) {
                strcat(path, " ");
                strncat(path, arg[i], sizeof(path) - strlen(path) - 1);
                if (arg[i][strlen(arg[i]) - 1] == '\"') {
                    path[strlen(path) - 1] = '\0'; // Remove trailing quote and break
                    break;
                }
            }
        }
    } else {
        // Non-quoted but possibly space-containing path
        strncpy(path, arg[1], sizeof(path) - 1);
        for (int i = 2; arg[i] != NULL; i++) {
            if (strlen(path) + strlen(arg[i]) + 2 > sizeof(path)) {
                printf("-myShell: cd: path is too long\n");
                return;
            }
            strcat(path, " ");
            strcat(path, arg[i]);
        }
    }

    // Attempt to change directory
    if (chdir(path) != 0) {
        printf("-myShell: cd: %s: No such file or directory\n", path);
    }
}
void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("Erorr");
        return;
    }
    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("Erorr");
        fclose(src);
        return;
    }

    while((ch=fgetc(src))!=EOF){
        fputc(ch,des);
    }
    fclose(src);
    fclose(des);
}
// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות