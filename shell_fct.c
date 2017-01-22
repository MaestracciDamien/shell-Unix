#include "shell_fct.h"

int exec_command(cmd* my_cmd){
    //Your implementation comes here
    int i;
  pid_t pid;
  int in, fd [2];

  /* The first process should get its input from the original file descriptor 0.  */
  in = 0;

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
  return execvp (my_cmd->cmd_members_args[i][0], (char * const *)my_cmd->cmd_members_args[i]);
}


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
