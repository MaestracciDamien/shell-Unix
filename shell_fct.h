#include "cmd.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>
//Your imports come here

//Terminate shell
#define MYSHELL_FCT_EXIT 1

//Execute a command
int exec_command(cmd *c);
int spawn_proc (int in, int out, char ** args);
