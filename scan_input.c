#include "header.h"
char *ext_cmd[153];
int pid;
int status; 
extern Slist *head;
void scan_input(char *prompt,char *input_string)//call the external command function to store back all commands into a 2D array 
{
   signal(SIGINT,signal_handler);
   signal(SIGTSTP,signal_handler);
    extract_external_commands(ext_cmd);
    while (1)
    {
        
       printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET,prompt);//print prompt
       fflush(stdout);
       if(fgets(input_string, 100, stdin) == NULL)
      {
        clearerr(stdin);
        continue;
      } 

    // strip the trailing \n that fgets keeps
    int len = strlen(input_string);
    if(len > 0 && input_string[len-1] == '\n')
        input_string[len-1] = '\0';

        if(strlen(input_string) == 0)// Ignore empty input 
        {
            continue;
        }
       if(strncmp(input_string,"PS1=",4)==0)//check weather the user need to customize the prompt using env-PS1
       {
        if(strlen(input_string) == 4)//check if onlu PS1 is given
        {
        printf(ANSI_COLOR_RED "Error: Prompt cannot be empty\n" ANSI_COLOR_RESET);
        }else
         { 
            char *ptr=strchr(input_string,' ');//check if any space is there
           if(ptr==NULL)
           {
            strcpy(prompt,input_string+4);//print the new prompt
            strcat(prompt,":~$ ");
           }else
           {
            printf(ANSI_COLOR_RED "Error: Shouldnot use a spsace between prompt !!!\n"ANSI_COLOR_RESET);
           }
        }
        continue;
       }
       char *command=get_command(input_string);//call get command to get the command which we need to exicute
       int type = check_command_type(command);//we need to check weather the command is internal(builtin) or external
       if (type==BUILTIN)
         {
            execute_internal_commands(input_string);
            __fpurge(stdin);
            status = 0;
         }
       else if (type==EXTERNAL)
       {
        pid=fork();
        if(pid>0)
        {
         waitpid(pid,&status,WUNTRACED);
          if (WIFSTOPPED(status))          // ← Add this
            {
               insert_first(&head, input_string, pid);
                // Print stop message immediately in shell
               int job_count = 1;
               Slist *tmp = head;
               while(tmp->link != NULL) { tmp = tmp->link; job_count++; }
               printf("\n[%d]+  Stopped    %s\n", job_count, input_string);
            }
            pid = 0;
        }else if (pid==0)
        {
         signal(SIGINT,SIG_DFL);//need to reset it to default for better handling
         signal(SIGTSTP,SIG_DFL);
         execute_external_commands(input_string);
         exit(0);
        }   
       }else
       printf(ANSI_COLOR_RED "Error: '%s' command not found\n" ANSI_COLOR_RESET, command);//if command is not present in list of external or internal
                
    }   
}