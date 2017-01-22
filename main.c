#include <pwd.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell_fct.h"

//To complete
int main(int argc, char** argv)
{
	//..........
	int ret = MYSHELL_CMD_OK;
	char* readlineptr;
	struct passwd* infos;
	char str[1024];
	char hostname[256];
	char workingdirectory[256];

	//..........
	while(ret != MYSHELL_FCT_EXIT)
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
		print_members_args(test);//fait bugger parse_redirection
		for (int i = 0; i< test->nb_cmd_members; i++)
		{
			parse_redirection(i,test);
			print_redirection(test,i);


		}


		exec_command(test);

        //Your code goes here.......
        //Parse the comand
        //Execute the comand
        //Clean the house
        //..........

	}
	//..........
	return 0;
}
