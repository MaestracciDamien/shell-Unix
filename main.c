#include <pwd.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell_fct.h"

int main(int argc, char** argv)
{
	//..........
	char* readlineptr;
	struct passwd* infos;
	char str[1024];
	char hostname[256];
	char workingdirectory[256];

	//..........
	while(1)
	{
		//Get your session info
    	infos=getpwuid(getuid());
		gethostname(hostname, 256);
		getcwd(workingdirectory, 256);
        //Print it to the console
		sprintf(str, "\n{myshell}%s@%s:%s$ \n", infos->pw_name, hostname, workingdirectory);
		readlineptr = readline(str);
		cmd   * test = (cmd *) malloc (sizeof(cmd));
		parse_members(readlineptr, test );
		print_members(test);
		parse_members_args(test);
		print_members_args(test);
		for (int i = 0; i< test->nb_cmd_members; i++)
		{
			parse_redirection(i,test);
			print_redirection(test,i);
		}
		exec_command(test);
	}
	return 0;
}
