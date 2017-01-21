#include "cmd.h"
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
    //your implementation comes here
}

//Frees the memory allocated to store member information
void free_members(cmd *c){
    //your implementation comes here
}

//Prints the redirection information for member i
void print_redirection(cmd c, int i){
    //your implementation comes here
}

//Frees the memory allocated to store redirection info
void free_redirection(cmd *c){
    //your implementation comes here
}

//Remplit les champs cmd_args et nb_args_membres
void parse_members_args(cmd *c){
    int cpt=0;
    while (cpt < (c->nb_cmd_members)){
  		int j=0;
	    char *token = strtok(c->cmd_members[cpt]," ");
	    while (token!=NULL){
	    	int length = strlen(token);
	    	printf("%s\n", token );
	    	(char *) c->cmd_members_args[cpt][j]=(char*)malloc(sizeof(char)*length);
	    	memcpy(c->cmd_members_args[cpt][j],token,length);
  		    j++; 
  		    token = strtok(NULL," "); 		    
	    }
	    cpt++;
    }

}

//Remplit les champs initial_cmd, membres_cmd et nb_membres
void parse_members(char *s,cmd *c){
    //your implementation comes here
}

//Remplit les champs redir et type_redir
void parse_redirection(unsigned int i, cmd *c){
    //your implementation comes here
}