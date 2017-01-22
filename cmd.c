#include "cmd.h"
#include <pwd.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//Your includes come here


//Prints the contents of members_args to the console
void print_members_args(cmd *c){
    //your implementation comes here
    int i,j;
    for (i =0; i < c->nb_cmd_members; i++)
    {
      for (j=0; j<= c->nb_members_args[i]; j++ )
      {
        if (c->cmd_members_args[i][j]== NULL)
        {
          printf("cmd_members_args[%d][%d]=NULL\n",i,j);
        }
        else
        {
        printf("cmd_members_args[%d][%d]=\"%s\"\n",i,j,c->cmd_members_args[i][j] );
        }
      }
    }
    for (i =0; i < c->nb_cmd_members; i++)
    {
      printf("nb_members_args[%d]=%d\n",i,c->nb_members_args[i] );
    }
}

//Frees the memory allocated to store member arguments
void free_members_args(cmd *c){
    int i,j;
    for (i =0; i < c->nb_cmd_members; i++)
    {
      for (j=0; j<= c->nb_members_args[i]; j++ )
      {
          free(c->cmd_members_args[i][j]);
      }
      free(c->cmd_members_args[i]);
    }
    free(c->cmd_members_args);
    free(c->nb_members_args);
}

//Prints the contents of members to the console
void print_members(cmd *c){
  int i;

  printf("\nnb_cmd_members=%d\n",c->nb_cmd_members );
  for (i= 0; i < c->nb_cmd_members; i++)
  {
    printf("cmd_members[%d]=\"%s\"\n",i, c->cmd_members[i]);
  }
    //your implementation comes here
}

//Frees the memory allocated to store member information
void free_members(cmd *c){
  int i;
  for (i= 0; i < c->nb_cmd_members; i++)
  {
    free(c->cmd_members[i]);
  }
  free(c->cmd_members);
    //your implementation comes here
}

//Prints the redirection information for member i
void print_redirection(cmd *c, int i){
    printf("[%d] Standard input redirection : %s\n", i, c->redirection[i][STDIN]); // bug affiche null au lieu de "/var/log/messages"
    printf("[%d] Standard output redirection : %s\n", i, c->redirection[i][STDOUT]);
    printf("[%d] Error output redirection : %s\n", i, c->redirection[i][STDERR]);

    if(c->redirection[i][STDIN] != NULL)
    {
        printf("[%d] Standard input redirection type : %s\n", i, (c->redirection_type[i][STDIN] == 1) ? "OVERRIDE" : "APPEND");
    }

    if(c->redirection[i][STDOUT] != NULL)
    {
        printf("[%d] Standard output redirection type : %s\n", i, (c->redirection_type[i][STDOUT] == 1) ? "OVERRIDE" : "APPEND");
    }

    if(c->redirection[i][STDERR] != NULL)
    {
        printf("[%d] Error output redirection type : %s\n", i, (c->redirection_type[i][STDERR] == 1) ? "OVERRIDE" : "APPEND");
    }
}

//Frees the memory allocated to store redirection info
void free_redirection(cmd *c){
  int i;
for (i= 0; i < c->nb_cmd_members; i++)
{
  free(c->redirection[i][STDIN]);
  free(c->redirection[i][STDOUT]);
  free(c->redirection[i][STDERR]);
  free(c->redirection[i]);
  free(c->redirection_type[i]);
}
free(c->redirection);
free(c->redirection_type);
    //your implementation comes here
}

//Remplit les champs cmd_args et nb_args_membres
void parse_members_args(cmd *c){
	int i=0;
    //int cpt=0;
    c->cmd_members_args =  (char***) malloc (sizeof(char **)*c->nb_cmd_members);
    c->nb_members_args = (unsigned int*) malloc (sizeof(int)*c->nb_cmd_members);
    while (i < (c->nb_cmd_members)){
    		int j=0;
  	    char *token = strtok(c->cmd_members[i]," ");
        c->cmd_members_args[i] = NULL;
  	    while (token!=NULL && strcmp(token,"<")!=0 && strcmp(token,">")!=0 && strcmp(token,">>")!=0)
        {
    	    	int length = strlen(token)+1;
    	    	//printf("%s\n", token );
            c->cmd_members_args[i]= (char ** ) realloc (c->cmd_members_args[i], sizeof(char *) *j+1);
            c->cmd_members_args[i][j] = (char *) malloc (sizeof(char)*length);
    	    	memcpy(c->cmd_members_args[i][j],token,length);
      		    j++;
      		    token = strtok(NULL," ");

  	    }
        c->cmd_members_args[i]= (char ** ) realloc (c->cmd_members_args[i], sizeof(char *) *j+1);
        c->cmd_members_args[i][j] = NULL;

        c->nb_members_args[i] = j;
        i++;
    }

}

//Remplit les champs initial_cmd, membres_cmd et nb_membres
void parse_members(char *s,cmd *c){
    //your implementation comes here
    c->init_cmd = (char *) malloc (sizeof(char) * strlen(s));
    memcpy(c->init_cmd,s,strlen(s));
    int i =0;
    char * token;
    const char pipe[1] = "|";
    token = strtok(s, pipe);
      c->cmd_members =  NULL;
    while( token != NULL )
    {
      c->cmd_members = (char **) realloc(c->cmd_members, sizeof(char *) * (i+1));
      int  length = strlen(token)+1;
      c->cmd_members[i] = (char *) malloc (length);
      memcpy(c->cmd_members[i],token,length);
      token = strtok(NULL, pipe);
      i++;
      }
      c->nb_cmd_members = i;

}

//Remplit les champs redir et type_redir
void parse_redirection(unsigned int i, cmd *c){
    printf("%s\n",c->cmd_members[i] ); // bug avec l'espace
    unsigned int current_position= 0;
    c->redirection = NULL;
    c->redirection = realloc(c->redirection, sizeof(char *) * (3+1));
    c->redirection_type = realloc(c->redirection, sizeof(int) * (3+1));
    c->redirection_type[i][STDIN] = 0;
    c->redirection_type[i][STDOUT] = 0;
    c->redirection_type[i][STDERR] = 0;
    printf("%d\n",strlen(c->cmd_members[i])); // affiche 3  pour "cat" au lieu de "cat < /var/log/messages" si on fait parse_members_args avant
    while(c->cmd_members[i][current_position] != '\0'){ // pb avec espace 
        if((char)c->cmd_members[i][current_position] == '2' && (char)c->cmd_members[i][current_position + 1] == '>'){
            if(c->cmd_members[i][current_position + 2] == '>'){
                char * token = strtok(c->cmd_members[i] + current_position + 3, " \n\t\0");
                if(token != NULL){
                    c->redirection[i][STDERR] = strdup(token);
                    c->redirection_type[i][STDERR] = 0;
                }
                current_position += 3;
            }
            else{
                char * token = strtok(c->cmd_members[i] + current_position + 2, " \n\t\0");
                if(token != NULL){
                    c->redirection[i][STDERR] = strdup(token);
                    c->redirection_type[i][STDERR] = 1;
                }
                current_position+=2;
            }
        }
        else if((char)c->cmd_members[i][current_position] == '>' && (char)c->cmd_members[i][current_position + 1] == '>'){
            char * token = strtok(c->cmd_members[i] + current_position + 2, " \n\t\0");
            if(token != NULL){
                c->redirection[i][STDOUT] = strdup(token);
                c->redirection_type[i][STDOUT] = 0;
            }
            current_position+=2;
        }
        else if((char)c->cmd_members[i][current_position] == '>'){
            char * token = strtok(c->cmd_members[i] + current_position + 1, " \n\t\0");
            if(token != NULL){
                c->redirection[i][STDOUT] = strdup(token);
                c->redirection_type[i][STDOUT] = 1;
            }
            current_position++;
        }
        else if((char)c->cmd_members[i][current_position] == '<'){
            char * token = strtok(c->cmd_members[i] + current_position + 1, "\0"); 
            if(token != NULL){
                c->redirection[i][STDIN] = realloc(c->redirection[i][STDIN],sizeof(char *) * (strlen(token)));
                printf("%d\n",i);
                memcpy(c->redirection[i][STDIN],token,strlen(token)+1);
                c->redirection_type[i][STDIN] = 0;
            }
            current_position++;
        }
        else{
            current_position++;
        }
    }
}
