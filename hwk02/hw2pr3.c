// Dong Liang
// 002128806
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SUB_COMMANDS   5                                              
#define MAX_ARGS           10    
#define ARGV_SIZE          10
#define COMM_LENGTH        1024

struct SubCommand  {                                                      
    char *line;                      // cat list.txt                              
    char *argv[MAX_ARGS];            // ReadArgs(*line, argv, size)                                 
};                                                                        
                                                           
struct Command {                                                          
    struct SubCommand sub_commands[MAX_SUB_COMMANDS];
    int num_sub_commands;     
    char *stdin_redirect; 
    char *stdout_redirect; 
    int background;                                        
};   

// in: cat list.txt
// argv
// size
void 
ReadArgs(char *in, char **argv, int size) {
    // 1. populate argv
    int count = 0;
    char *str = strtok(in, " "); 
    while (str != NULL && count < size - 1) {
        argv[count++] = str;
        str = strtok(NULL, " ");
    }

    // 2. append null terminator
    argv[count] = '\0';
}

void 
PrintArgs(char **argv) {
    int i = 0;
    while (*argv != NULL && *argv != "\0")
        printf("argc[%d] = '%s' \n", i++, *argv++);
}

// *line => 
void
ReadCommand(char *line, struct Command *command) {
    // 1. strtok line by |; populate sub_commands array
    int count = 0;
    char *str = strtok(line, "|"); 
    while (str != NULL && count < MAX_SUB_COMMANDS) {
        command->sub_commands[count++].line = strdup(str);

        str = strtok(NULL, "|");
    }
    for (int i = 0; i < count; i++)
        ReadArgs(command->sub_commands[i].line, command->sub_commands[i].argv, MAX_ARGS);

    command->num_sub_commands = count;
}

void 
PrintCommand(struct Command *command)  {
    for (int i = 0; i < command->num_sub_commands; i++) {
        printf("\n\nCommand %d:\n", i);
        PrintArgs(command->sub_commands[i].argv);
    }

    printf("\n\nRedirect stdin: %s \n", command->stdin_redirect);
    printf("Redirect stdout: %s \n", command->stdout_redirect);
    if (command->background) {
        printf("Background: Yes\n");
    } else {
        printf("Background: No \n");
    }
}

void
ReadRedirectsAndBackground(struct Command *command) {
    
    for (int i = command->num_sub_commands - 1; i > -1; i--) {
        int j = 0;
        while (command->sub_commands[i].argv[j] != NULL) {

            if (strcmp(command->sub_commands[i].argv[j], "&") == 0 && command->sub_commands[i].argv[j+1] == NULL) {
                command->background = 1;
                command->sub_commands[i].argv[j] = "\0";
            }
            if (strcmp(command->sub_commands[i].argv[j], "<") == 0 && command->sub_commands[i].argv[j+1] != NULL) {
                command->stdin_redirect =  command->sub_commands[i].argv[j+1];
                command->sub_commands[i].argv[j] = "\0";

            } 
            if (strcmp(command->sub_commands[i].argv[j], ">") == 0 && command->sub_commands[i].argv[j+1] != NULL) {
                command->stdout_redirect = command->sub_commands[i].argv[j+1];
                command->sub_commands[i].argv[j] = "\0";

            } 
            j++;
        }
    }
}


int
main() {
    struct Command comm;
    comm.background = 0;
    comm.stdin_redirect = NULL;
    comm.stdout_redirect = NULL;

    char s[COMM_LENGTH];
    printf("Enter a string: ");
    fgets(s, sizeof s, stdin);
    s[strcspn(s, "\n")] = 0;
    
    ReadCommand(s, &comm);
    ReadRedirectsAndBackground(&comm);
    PrintCommand(&comm);
}