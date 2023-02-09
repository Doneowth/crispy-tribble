#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUB_COMMANDS 5
#define MAX_ARGS 10

struct SubCommand {
        char *line;
        char *argv[MAX_ARGS];
};

struct Command {
        struct SubCommand sub_commands[MAX_SUB_COMMANDS];
        int num_sub_commands;
};

void ReadArgs(char *in, char **argv, int size) {
        int i = 0;
        char *token = strtok(in, " ");

        while (token != NULL && i < size - 1) {
                argv[i] = token;
                i++;
                token = strtok(NULL, " ");
        }
        argv[i] = NULL;
}

void PrintArgs(char **argv) {
        int i = 0;
        while (argv[i] != NULL) {
                printf("argv[%d] = '%s'\n", i, argv[i]);
                i++;
        }
}

void ReadCommand(char *line, struct Command *command) {
        int i = 0;
        char *token = strtok(line, "|");

        while (token != NULL && i < MAX_SUB_COMMANDS) {
            command->sub_commands[i].line = strdup(token);
            i++;
            token = strtok(NULL, "|");
        }
        for (int j = 0;j<i;j++){
            ReadArgs(command->sub_commands[j].line, command->sub_commands[j].argv, MAX_ARGS);
        }

        command->num_sub_commands = i;
}

void PrintCommand(struct Command *command) {
        for (int i = 0; i < command->num_sub_commands; i++) {
                printf("\nCommand %d:\n", i);
                PrintArgs(command->sub_commands[i].argv);
        }
}

int main() {
        char line[1024];
        struct Command command;

        printf("Enter a string: ");
        fgets(line, 1024, stdin);
        line[strcspn(line, "\n")] = '\0';

        ReadCommand(line, &command);
        PrintCommand(&command);

        return 0;
}
