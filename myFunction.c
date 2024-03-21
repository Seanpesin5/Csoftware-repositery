#include "myFunction.h"

char *strwok(char *str, const char *delim)
{
    static char *next_token = NULL;
    if (str)
        next_token = str; // Initialize on first call
    if (!next_token || *next_token == '\0')
        return NULL; // End of string

    char *token_start = next_token; // Start of the next token
    char *current;                  // Current character being checked

    // Skip leading delimiters
    for (current = next_token; *current != '\0'; current++)
    {
        const char *d;
        for (d = delim; *d != '\0'; d++)
        {
            if (*current == *d)
            {

                token_start++;
                break;
            }
        }
        if (*d == '\0')
            break; // Found the start of a token
    }
    if (*token_start == '\0')
    {
        next_token = token_start; // Prepare for the next call to return NULL
        return NULL;
    }
    next_token = token_start; // Begin searching for the end of the token
    for (current = token_start; *current != '\0'; current++)
    {
        const char *d;
        for (d = delim; *d != '\0'; d++)
        {
            if (*current == *d)
            {

                *current = '\0';          // Terminate the token
                next_token = current + 1; // Set up for the next token
                return token_start;       // Return the current token
            }
        }
    }

    // Reached the end of the string
    next_token = current; // No more tokens
    return token_start;   // Return the last token
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
void getLocation()
{
    char location[BUFF_SIZE];
    char hostname[BUFF_SIZE];
    char *username = getenv("USER"); // On Unix-like systems; use "USERNAME" for Windows

    if (getcwd(location, BUFF_SIZE) == NULL)
    {
        perror("Error retrieving current directory");
        return;
    }

    if (gethostname(hostname, BUFF_SIZE) != 0)
    {
        perror("Error retrieving hostname");
        return;
    }

    if (username == NULL)
    {
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

void cd(char **arg)
{
    char path[1024] = {0}; // Adjust size as needed

    if (arg[1] == NULL)
    {
        printf("-myShell: cd: missing operand\n");
        return;
    }

    // Direct handling for "cd .."
    if (strcmp(arg[1], "..") == 0 && arg[2] == NULL)
    {
        if (chdir("..") != 0)
        {
            perror("-myShell: cd: error changing to parent directory");
        }
        return;
    }

    // For quoted paths or paths without spaces
    if (arg[1][0] == '\"')
    {
        // Quoted path
        strncpy(path, arg[1] + 1, sizeof(path) - 1); // Copy without the leading quote
        size_t path_len = strlen(path);
        if (path[path_len - 1] == '\"')
        {
            path[path_len - 1] = '\0'; // Remove trailing quote
        }
        else if (arg[2] != NULL)
        { // Handle case where path is split across arguments
            for (int i = 2; arg[i] != NULL; i++)
            {
                strcat(path, " ");
                strncat(path, arg[i], sizeof(path) - strlen(path) - 1);
                if (arg[i][strlen(arg[i]) - 1] == '\"')
                {
                    path[strlen(path) - 1] = '\0'; // Remove trailing quote and break
                    break;
                }
            }
        }
    }
    else
    {
        // Non quoted but  space-containing path
        strncpy(path, arg[1], sizeof(path) - 1);
        for (int i = 2; arg[i] != NULL; i++)
        {
            if (strlen(path) + strlen(arg[i]) + 2 > sizeof(path))
            {
                printf("-myShell: cd: path is too long\n");
                return;
            }
            strcat(path, " ");
            strcat(path, arg[i]);
        }
    }

    // Attempt to change directory
    if (chdir(path) != 0)
    {
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

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, des);
    }
    fclose(src);
    fclose(des);
}

void delete(char **path)
//the function goes to the path of course deletes "" if exists and by unlink deletes the file
//if something goes wrong it uses error to invoke you
{
    if (path == NULL || path[1] == NULL)
    {
        fprintf(stderr, "Error: Path is NULL or not provided.\n");
        return;
    }
    char fullPath[1024] = {0};
    for (int i = 1; path[i] != NULL; ++i)
    {
        if (i > 1)
            strcat(fullPath, " ");
        strcat(fullPath, path[i]);
    }
    printf("Attempting to delete file: %s\n", fullPath);
    if (unlink(fullPath) == 0)
    {
        printf("File '%s' successfully deleted.\n", fullPath);
    }
    else
    {
        perror("Error deleting file");
    }
}

void systemCall(char **arg)
{

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arg[0], arg) == -1)
        exit(1);
}


void echorite(char **args) {
   //it overwrites to a path or creates one if it cant find it
   // using some kind of buufres/storage i cut the ""
   //using fprint i write to the file
   //using strcat i cut the previous content
   //the write to the file and close it
   //added errors handling   
   
    char textToWrite[2048] = {0};
    char filePath[2048] = {0};

    // Finding the ">"
    int foundRedirection = 0;
    for (int i = 1; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            foundRedirection = 1;
            if (args[i + 1] != NULL) {
                for (int j = i + 1; args[j] != NULL; j++) {
                    if (j > i + 1) strcat(filePath, " ");
                    strcat(filePath, args[j]);
                }
            } else {
                fprintf(stderr, "File path not provided.\n");
                return;
            }
            break;
        } else {
    //here i empty the file       
            if (i > 1) strcat(textToWrite, " "); 
            strcat(textToWrite, args[i]);
        }
    }
    if (!foundRedirection) {
        fprintf(stderr, "Redirection operator '>' not found.\n");
        return;
    }
    // here i write to the file
    FILE *file = fopen(filePath, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s\n", textToWrite);
    fclose(file);

    printf("Content written to '%s'.\n", filePath);
}

void echoppend(char **args) {
    // basiclly the same as echorite it just doenst overwrites the file just appends to it
    
    // Variables to hold the concatenated text and file path
    char textToAppend[2048] = {0};
    char filePath[2048] = {0};
    int redirectIndex = -1; // Index of ">>" in args
    for (int i = 0; args[i] != NULL; ++i) {
        if (strcmp(args[i], ">>") == 0) {
            redirectIndex = i;
            break;
        }
    }
    if (redirectIndex == -1) {
        fprintf(stderr, "Error: Command format incorrect. Expected '>>' for redirection.\n");
        return;
    }
    for (int i = 1; i < redirectIndex; ++i) {
        strcat(textToAppend, args[i]);
        if (i < redirectIndex - 1) strcat(textToAppend, " "); 
    }
    for (int i = redirectIndex + 1; args[i] != NULL; ++i) {
        strcat(filePath, args[i]);
        if (args[i + 1] != NULL) strcat(filePath, " "); 
    }
    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    // Append the text and a newline, then close the file
    fprintf(file, "%s\n", textToAppend);
    fclose(file);

    printf("Appended '%s' to '%s'.\n", textToAppend, filePath);
}

void move(char **args)
{
    //cutting the "" using the same tactic of kind of storage
    //finding the source arg 2 and dest arg 3+4 depends on the spaces
    //arg [0] = mv
    char srcPath[2048] = {0};
    char destPath[2048] = {0};
   //cutting spaces
    strcat(srcPath, args[1]);
    if (args[2] != NULL)
    {
        strcat(srcPath, " ");
        strcat(srcPath, args[2]);
    }
    if (args[3] != NULL)
    {
        //cutting spaces
        strcat(destPath, args[3]);
        if (args[4] != NULL)
        {
            //cutting spaces
            strcat(destPath, " ");
            strcat(destPath, args[4]);
        }
    }
    printf("Attempting to move from '%s' to '%s'\n", srcPath, destPath);
    if (rename(srcPath, destPath) == 0)
    {
        printf("File successfully moved.\n");
    }
    else
    {
        perror("Error moving file");
    }
}
void readd(char **args) {
    // the easiest function just handling the spaces
    // open file using fopen
    //getting file conten using fgets
    //the content is loaded into a buffer and then printed
    if (args[1] == NULL) {
        fprintf(stderr, "Usage: read <path>\n");
        return;
    }
    char filePath[2048] = {0};
    for (int i = 1; args[i] != NULL; ++i) {
        if (i > 1) strcat(filePath, " ");
        strcat(filePath, args[i]);
    }
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}
void wordCount(char **args) {
    //finding the symbol -l||-w
    //again cutting spaces
    //going through the file using fopen
    
    // Check for at least two arguments: the option and part of the file path
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: wordCount -l|-w <path>\n");
        return;
    }

    // Concatenate all arguments after the option to form the file path
    char filePath[2048] = {0};
    for (int i = 2; args[i] != NULL; ++i) {
        if (i > 2) strcat(filePath, " "); // Add spaces back in
        strcat(filePath, args[i]);
    }

    // Open the file
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
//declaring lines and words if file exist automaticlly at least one line
    int lines = 1, words = 0;
    char buffer[2048];
    int inWord = 0;
   
   //while has content basiclly while counting words and lines using backslash n
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] == '\n') lines++;
            if (isspace(buffer[i])) {
                inWord = 0;
            } else if (!inWord) {
                inWord = 1;
                words++;
                //adjusting via ++
            }
        }
    }
    fclose(file);
// checking for the sign
    if (strcmp(args[1], "-l") == 0) {
        printf("Lines: %d\n", lines);
    } else if (strcmp(args[1], "-w") == 0) {
        printf("Words: %d\n", words);
    } else {
        fprintf(stderr, "Invalid option. Use -l for lines or -w for words.\n");
    }
}

void mypipe(char **argv1, char **argv2)
{
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            
            execvp(argv1[0], argv1);
        }
        
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        
        execvp(argv2[0], argv2);
    }
}