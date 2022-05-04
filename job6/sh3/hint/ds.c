// basic
// redirect
// &
struct command {
    int argc;
    char *argv[MAX_ARGC];
    char *input;
    char *output;
    char *append;
    int is_backend;                 // back
};

int commandc, struct command *commands // PIPE

cond
then_part commands
else_part commands

text => word => tree => insn 

void parse_command(char *line, struct command *command);

int parse_commands(char *line, struct command *commands);

void exec_commands(char *line, int commandc, struct command *commands);

int main()
{
    int commandc;
    struct command commands[10];
    commandc = parse_commands(line, commands);
}

"echo abc"
"echo abc >log"
"cat <input >output"
"cc -c main.c &"
"echo abc | wc -l"

+ return 2
+ commands[0] = "echo abc"
+ commands[1] = "wc -l"
"echo abc | wc -l | wc -l"

