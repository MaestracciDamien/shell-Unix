#include "cmd.h"
#include <pwd.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//Your includes come here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prints the contents of members_args to the console
void print_members_args(cmd *c){
    //your implementation comes here
}

//Frees the memory allocated to store member arguments
void free_members_args(cmd *c){
    //your implementation comes here
}

//Prints the contents of members to the console
void print_members(cmd *c){
  int i;

  printf("nb_cmd_members=%d\n",c->nb_cmd_members );
  for (i= 0; i < c->nb_cmd_members; i++)
  {
    printf("cmd_members[%d]=\"%s\"\n",i, c->cmd_members[i]);
  }
    //your implementation comes here
}

//Frees the memory allocated to store member information
void free_members(cmd *c){
    //your implementation comes here
}

//Prints the redirection information for member i
void print_redirection(cmd *c, int i){
    //your implementation comes here
}

//Frees the memory allocated to store redirection info
void free_redirection(cmd *c){
    //your implementation comes here
}

//Remplit les champs cmd_args et nb_args_membres
void parse_members_args(cmd *c){
	int i=0;
    int cpt=0;
    c->cmd_members_args =  NULL;
    while (cpt < (c->nb_cmd_members)){
  		int j=0;
	    char *token = strtok(c->cmd_members[cpt]," ");
	    while (token!=NULL){
	    	int length = strlen(token);
	    	printf("%s\n", token );
	    	c->cmd_members_args=(char***)realloc(c->cmd_members_args, sizeof(char*) * (i+1));
	    	memcpy(c->cmd_members_args[cpt][j],token,length);
  		    j++; 
  		    token = strtok(NULL," "); 		    
  		    i++;
	    }
	    cpt++;
    }

}

//Remplit les champs initial_cmd, membres_cmd et nb_membres
void parse_members(char *s,cmd *c){
    //your implementation comes here
    c->init_cmd = (char *) malloc (sizeof(char) * strlen(s));
    memcpy(c->init_cmd,s,strlen(s));
    printf("%s",c->init_cmd );

    int i =0;
    char * token;
    const char pipe[1] = "|";
    token = strtok(s, pipe);
      c->cmd_members =  NULL;
    while( token != NULL )
    {
      c->cmd_members = (char **) realloc(c->cmd_members, sizeof(char *) * (i+1));
      int  length = strlen(token)+1;
      c->cmd_members[i] = (char *) malloc (1000);
      memcpy(c->cmd_members[i],token,length);
      token = strtok(NULL, pipe);
      i++;
      }
      c->nb_cmd_members = i;

}

//Remplit les champs redir et type_redir
void parse_redirection(unsigned int i, cmd *c){
    //your implementation comes here
}
