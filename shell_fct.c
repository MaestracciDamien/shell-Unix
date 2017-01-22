#include "shell_fct.h"



int exec_command(cmd* my_cmd){
    //Your implementation comes here
    int i;
    int in, fd [2];


  /* The first process should get its input from the original file descriptor 0.  */
  in = 0;

  if (my_cmd->redirection[0][STDIN] !=NULL)
  {
    freopen (my_cmd->redirection[0][STDIN],"r",stdin);
  }

  /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
  for (i = 0; i < my_cmd->nb_cmd_members -1; ++i)
    {
      pipe (fd);

      /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
      spawn_proc (in, fd [1], my_cmd->cmd_members_args[i]);

      /* No need for the write end of the pipe, the child will write here.  */
      close (fd [1]);

      /* Keep the read end of the pipe, the next child will read from there.  */
      in = fd [0];
    }

  /* Last stage of the pipeline - set stdin be the read end of the previous pipe
     and output to the original file descriptor 1. */
  if (in != 0)
    dup2 (in, 0);

  /* Execute the last stage with the current process. */
  if (my_cmd->redirection[i][STDOUT] !=NULL)
  {
    if (my_cmd->redirection_type[i][STDOUT] == 1)
    {
      freopen (my_cmd->redirection[i][STDOUT],"a+",stdout);

    }
    else
    {
      freopen (my_cmd->redirection[i][STDOUT],"w+",stdout);
    }
  }

  if (my_cmd->redirection[i][STDERR] !=NULL)
  {
    if (my_cmd->redirection_type[i][STDERR] == 1)
    {
      freopen (my_cmd->redirection[i][STDERR],"a+",stderr);

    }
    else
    {
      freopen (my_cmd->redirection[i][STDERR],"w+",stderr);
    }
  }
<<<<<<< HEAD

    return execvp (my_cmd->cmd_members_args[i][0], (char * const *)my_cmd->cmd_members_args[i]);

  }
=======
  return execvp (my_cmd->cmd_members_args[i][0], (char * const *)my_cmd->cmd_members_args[i]);
  if (my_cmd->redirection[i][STDOUT] !=NULL)
  {
  fclose (stdout);
  }
  if (my_cmd->redirection[i][STDERR] !=NULL)
  {
  fclose (stderr);
  }
}
>>>>>>> b2445c4781e49ee29dee26432d9c08f1e872e1e5


int spawn_proc (int in, int out, char ** args)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      return execvp (args[0], (char * const *)args);
    }

  return pid;
}
