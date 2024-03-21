#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define BUFF_SIZE 256
#define blue() printf("\033[0;34m")
#define reset() printf("\033[0m")
#define green() printf("\033[0m")
#define bold() printf("\e[1m")
#define boldOff() printf("\e[m")

char *getInputFromUser();
/**
 * Splits a string into individual tokens based on whitespace.
 *
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 *
 * @param input A pointer to the string to be split.
 *
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 *
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 *
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char **splitArgument(char *);

void getLocation();
/**
 * Performs logout operation for a user session.
 *
 * This function handles the cleanup and termination of a user session. It may
 * perform various tasks such as closing files, logging out from services,
 * and optionally printing a logout message. The function takes no parameters
 * and does not return a value. It should be called when the user decides to
 * end the session or when the program is about to exit.
 *
 * Usage of this function ensures that all session-related activities are
 * properly concluded before the program terminates, preventing resource leaks
 * and ensuring that the user is logged out from all services.
 *
 * @note This function might invoke other cleanup functions and is responsible
 *       for ensuring that all necessary session termination activities are
 *       performed.
 *
 * @warning Depending on the implementation, this function might terminate the
 *          program. Ensure that all necessary data is saved and cleanup
 *          operations are performed before calling this function.
 */
void logout(char *);
/**
 * Splits a string into individual tokens based on whitespace.
 *
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the returned array and its elements using free().
 *
 * @param input A pointer to the string to be split.
 *
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 */
void echo(char **);
/**
 * Changes the current working directory.
 *
 * This function changes the current working directory of the shell process
 * to the specified directory. If the directory is not found or if changing
 * the directory fails, appropriate error messages are printed.
 *
 * @param directory A pointer to a string containing the path of the directory
 *                  to change to.
 *
 * @return None.
 */
void cd(char **);
/**
 * Copies a file from one location to another.
 *
 * This function copies the file located at the source path to the destination
 * path. If the destination file already exists, it will be overwritten. If the
 * source file does not exist or if copying fails for any reason, appropriate
 * error messages are printed.
 *
 * @param source A pointer to a string containing the path of the source file.
 * @param destination A pointer to a string containing the path of the destination
 *                    file.
 *
 * @return None.
 */
void cp(char **);
/**
 * Deletes a file.
 *
 * This function deletes the file specified by the provided file path. If the file
 * does not exist or if deletion fails for any reason, appropriate error messages
 * are printed.
 *
 * @param file_path A pointer to a string containing the path of the file to be deleted.
 *
 * @return None.
 */
void delete(char **);
/**
 * Executes a system command.
 *
 * This function executes the specified system command using the system() function
 * provided by the C standard library. The command is passed as a string to the
 * system() function. If execution of the command fails for any reason, appropriate
 * error messages are printed.
 *
 * @param command A pointer to a string containing the system command to be executed.
 *
 * @return None.
 */
void systemCall(char **);
/**
 * Executes two commands with a pipe between them.
 *
 * This function creates a pipe, forks two child processes, and executes
 * the specified commands in each child process. The standard output of
 * the first command is redirected to the write end of the pipe, and the
 * standard input of the second command is redirected from the read end
 * of the pipe. If execution of either command fails for any reason,
 * appropriate error messages are printed.
 *
 * @param command1 A pointer to a null-terminated array of strings containing
 *                 the first command and its arguments.
 * @param command2 A pointer to a null-terminated array of strings containing
 *                 the second command and its arguments.
 *
 * @return None.
 */
void mypipe(char **, char **);
/**
 * Moves a file from one location to another.
 *
 * This function moves the file located at the source path to the destination
 * path. If the destination file already exists, it will be overwritten. If the
 * source file does not exist or if moving fails for any reason, appropriate
 * error messages are printed.
 *
 * @param source A pointer to a string containing the path of the source file.
 * @param destination A pointer to a string containing the path of the destination
 *                    file.
 *
 * @return None.
 */
void move(char **);
/**
 * Appends a string to the end of a file.
 *
 * This function appends the specified string to the end of the file located
 * at the provided file path. If the file does not exist, it will be created.
 * If appending fails for any reason, appropriate error messages are printed.
 *
 * @param message A pointer to a string containing the message to be appended.
 * @param file_path A pointer to a string containing the path of the file to which
 *                  the message will be appended.
 *
 * @return None.
 */
void echoppend(char **args);
/**
 * Writes a string to a file, overwriting its content.
 *
 * This function writes the specified string to the file located at the provided
 * file path. If the file does not exist, it will be created. If writing fails
 * for any reason, appropriate error messages are printed.
 *
 * @param message A pointer to a string containing the message to be written.
 * @param file_path A pointer to a string containing the path of the file to which
 *                  the message will be written.
 *
 * @return None.
 */
void echorite(char **args);
/**
 * Reads the contents of a file and prints them to the screen.
 *
 * This function opens the file located at the provided file path and prints
 * its contents to the standard output. If the file does not exist, no output
 * is printed.
 *
 * @param file_path A pointer to a string containing the path of the file to be read.
 *
 * @return None.
 */
void readd(char **args);
/**
 * Counts the number of words or lines in a file.
 *
 * This function opens the file located at the provided file path and counts
 * either the number of words or the number of lines in the file, based on the
 * specified option. If the option is "-w", the function counts the number of
 * words. If the option is "-l", the function counts the number of lines. If
 * the file does not exist, appropriate error messages are printed.
 *
 * @param option A pointer to a string containing the option ("-w" for word count,
 *               "-l" for line count).
 * @param file_path A pointer to a string containing the path of the file to be counted.
 *
 * @return None.
 */
void wordCount(char **args);