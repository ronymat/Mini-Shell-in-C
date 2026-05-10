#include "header.h"
//Builtin function exicution 
extern int status; 
extern Slist *head;
void execute_internal_commands(char *input_string)
{
    if (strcmp(input_string,"exit")==0)//to terminte the process
    {
     exit(0);
    }
    else if (strcmp(input_string,"pwd")==0)//to print the current path of present directory
    {
        char buff[50];
        getcwd(buff,50);//use  this system call to get path
        printf(ANSI_COLOR_BLUE"%s\n"ANSI_COLOR_RESET,buff);
    }else if (strncmp(input_string,"cd",2)==0)//change the directory
    {
      if(chdir(input_string+3)==-1)//use systemcall to change directory
      {
       printf(ANSI_COLOR_RED"Error: Given directory doesnot exist !!!\n"ANSI_COLOR_RESET);
      }else
      {//used to show  the directory to user
         char buff[50];
        getcwd(buff,50);
        printf(ANSI_COLOR_BLUE"%s\n"ANSI_COLOR_RESET,buff);
      }
    }
    else if (strcmp(input_string,"echo $$")==0)//used to print the pid of the shell
    {
       printf("%d\n",getpid());
    }
    else if (strcmp(input_string,"echo $?")==0)
    {
       if(WIFEXITED(status))
       {
         printf("%d\n",WEXITSTATUS(status));
       }
       else if(WIFSIGNALED(status))
      {
          printf("%d\n",128 + WTERMSIG(status));
      }
      else if(WIFSTOPPED(status))   
    {
        printf("%d\n",128 + WSTOPSIG(status));
    }
    }
    else if (strcmp(input_string,"echo $SHELL")==0)
    {
      printf("%s\n",getenv("SHELL"));
    }
    else if (strcmp(input_string,"jobs")==0)
    {
      print_list(head);
    }
    else if (strncmp(input_string,"fg",2)==0)
{
    if (head != NULL)
    {
        printf("%s\n", head->string);

        kill(head->pid, SIGCONT);

        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);

        waitpid(head->pid, &status, WUNTRACED);

        signal(SIGINT, signal_handler);
        signal(SIGTSTP, signal_handler);

        if (WIFSTOPPED(status))
        {
            printf("\nStopped    %s\n", head->string);
        }
        else if (WIFSIGNALED(status) || WIFEXITED(status))
        {
            delete_first(&head);
        }

    }
    else
    {
        printf(ANSI_COLOR_RED"No jobs found\n"ANSI_COLOR_RESET);
    }
}
    else if (strncmp(input_string,"bg",2)==0)
    {
      if(head!=NULL)
      {
      Slist *s = head;
      printf("[1]+   %s &\n", s->string);
     kill(s->pid,SIGCONT);
     delete_first(&head);
      }else
      {
          printf(ANSI_COLOR_RED"No jobs found\n"ANSI_COLOR_RESET);
      }
    } 
    else
    printf(ANSI_COLOR_RED"Error : Command doesnot exist !!!\n"ANSI_COLOR_RESET);
}
