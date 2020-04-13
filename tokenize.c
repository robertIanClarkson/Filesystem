#define LINE_LENGTH 256 // CHAR
#define MAX_ARGS 8
#define ARG_LENGTH 32 // CHAR
#define DELIMITERS " \t\n"

struct arguments {
    char args[MAX_ARGS][ARG_LENGTH];
    char* opt;
    int argc;
};

/* print(command); */
void print(struct arguments command) {
    for(int i = 0; i < command.argc; i++) {
        printf("%d : %s\n", i, command.args[i]);
    }
}

/* tokenize(line, &command); */
void tokenize(char line[LINE_LENGTH], struct arguments *command) {
    char* token;
    char* rest = line;
    command->argc = 0;
    while ((token = strtok_r(rest, DELIMITERS, &rest))) {
        if(command->argc > MAX_ARGS) {
            printf("****** TO MANY ARGS ******\n");
            break;
        }
        strcpy(command->args[command->argc], token);
        command->argc += 1;
    }
    command->opt = command->args[0];
}