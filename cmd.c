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
    if(c->redirection[i][STDIN] != NULL)
    {
        printf("redirection[%d][STDIN]=\"%s\"\n", i, c->redirection[i][STDIN]);
    }
    else {
        printf("redirection[%d][STDIN]=NULL\n", i);
    }

/*    if(c->redirection[i][STDOUT] != NULL)
    {
        printf("redirection[%d][STDOUT]=\"%s\"\n", i, c->redirection[i][STDOUT]);
    }
    else {
        printf("redirection[%d][STDOUT]=NULL \n",i);
    }

    if(c->redirection[i][STDERR] != NULL)
    {
        printf("redirection[%d][STDERR]=\"%s\"\n", i, c->redirection[i][STDERR]);
    }
    else {
        printf("redirection[%d][STDERR]=NULL \n", i);
    }
    if(c->redirection[i][STDOUT] != NULL)
    {
        printf("redirection_type[%d][STDOUT]=%s\n", i, (c->redirection_type[i][STDOUT] == 1) ? "OVERRIDE" : "APPEND");
    }
    if(c->redirection[i][STDERR] != NULL)
    {
        printf("redirection_type[%d][STDERR]=%s\n", i, (c->redirection_type[i][STDERR] == 1) ? "OVERRIDE" : "APPEND");
    }*/
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
        char * tmp= strdup(c->cmd_members[i]);
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
        c->cmd_members[i] = strdup(tmp);
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
    c->redirection = (char***) malloc (sizeof(char **)*i);
    c->redirection_type = (int**) malloc (sizeof(int)*i);

}

//Remplit les champs redir et type_redir
void parse_redirection(unsigned int i, cmd *c){
    unsigned int current_position= 0;
    c->redirection[i]=NULL;
    c->redirection_type[i]=NULL;
    c->redirection[i]= (char **)realloc(c->redirection[i],sizeof(char *)*3);
    c->redirection_type[i] = (int *)realloc(c->redirection_type[i],sizeof(int)*3);
    while(c->cmd_members[i][current_position] != '\0'){
        if((char)c->cmd_members[i][current_position] == '2' && (char)c->cmd_members[i][current_position + 1] == '>'){
             if(c->cmd_members[i][current_position + 2] == '>'){
                char * token = strtok(c->cmd_members[i] + current_position + 3, "\n\t\0");
                if(token != NULL){
                  c->redirection[i][STDERR] = malloc(sizeof(char *) * (strlen(token)));
                  c->redirection_type[i][STDERR] = (int)malloc(sizeof(int));
                  memcpy(c->redirection[i][STDERR],token,strlen(token)+1);
                  c->redirection_type[i][STDERR] = 0;
                  c->redirection[i][STDOUT]=NULL;
                  c->redirection[i][STDIN]=NULL;
                }
                current_position += 3;
            }
            else{

                char * token = strtok(c->cmd_members[i] + current_position + 2, "\n\t\0");
                if(token != NULL){
                  c->redirection[i][STDERR] = malloc(sizeof(char *) * (strlen(token)));
                  c->redirection_type[i][STDERR] = (int)malloc(sizeof(int));
                  memcpy(c->redirection[i][STDERR],token,strlen(token)+1);
                  c->redirection_type[i][STDERR] = 1;
                  c->redirection[i][STDOUT]=NULL;
                  c->redirection[i][STDIN]=NULL;
                }
                current_position+=2;
            }
        }
        else if((char)c->cmd_members[i][current_position] == '>' && (char)c->cmd_members[i][current_position + 1] == '>'){
            char * token = strtok(c->cmd_members[i] + current_position + 2, "\n\t\0");
            if(token != NULL){
                c->redirection[i][STDOUT] = malloc(sizeof(char *) * (strlen(token)));
                c->redirection_type[i][STDOUT] = (int)malloc(sizeof(int));
                memcpy(c->redirection[i][STDOUT],token,strlen(token)+1);
                c->redirection_type[i][STDOUT] = 0;
                c->redirection[i][STDIN]=NULL;
                c->redirection[i][STDERR]=NULL;
            }
            current_position+=2;
        }
        else if((char)c->cmd_members[i][current_position] == '>'){
            char * token = strtok(c->cmd_members[i] + current_position + 1, "\n\t\0");
            if(token != NULL){
                c->redirection[i][STDOUT] = malloc(sizeof(char *) * (strlen(token)));
                c->redirection_type[i][STDOUT] = (int)malloc(sizeof(int));
                memcpy(c->redirection[i][STDOUT],token,strlen(token)+1);
                c->redirection_type[i][STDOUT] = 1;
                c->redirection[i][STDIN]=NULL;
                c->redirection[i][STDERR]=NULL;
            }
            current_position++;
        }
        else if((char)c->cmd_members[i][current_position] == '<'){
            char * token = strtok(c->cmd_members[i] + current_position + 1, "\n\t\0");
            if(token != NULL){
                c->redirection[i][STDIN] = malloc(sizeof(char *) * (strlen(token)));
                c->redirection_type[i][STDIN] = (int)malloc(sizeof(int));
                memcpy(c->redirection[i][STDIN],token,strlen(token)+1);
                c->redirection[i][STDOUT]=NULL;
                c->redirection[i][STDERR]=NULL;
            }
            current_position++;
        }
        else{
            current_position++;
        }
    }
}
