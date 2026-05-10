#include "header.h"
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","fg","bg","jobs", NULL};

extern int pid;
extern int status; 
Slist *head=NULL;    
//Extract all the commands from the file to reduse time complexity
void extract_external_commands(char **external_commands)
{   
    char ch;
    char buff[50];//create a temporary buff
    int fd= open("external_cmd.txt",O_RDONLY);//open file in read onlly mode
   if(fd == -1)
    {
        perror("open");
        return;
    }
    int i=0,j=0;
   while(read(fd,&ch,1)>0)
   {   
    if(ch!='\n')
    {
      buff[i]=ch;
      i++;
    }else
    {
        buff[i]='\0';//give the last position \0

        external_commands[j]=malloc(strlen(buff)+1);//allocate memory dynamically
        strcpy(external_commands[j],buff);//copy the content to array
        j++;
        i=0;
    }
   }
   external_commands[j]=NULL;//give null at end
   close(fd);
}

char cmd[20];//declare it globally
char *get_command(char *input_string)
{
       int i=0;
       while (input_string[i]!=' ' && input_string[i]!='\0')//read the string until space or \0
       {
        cmd[i]=input_string[i];
         i++;
       }
        cmd[i]='\0';
        return cmd;
}

//function to check weather the command is external or internal
int check_command_type(char *command)
{
    for (int i = 0; builtins[i]!=NULL; i++)//loop to check in builtin aarray
    {
        if(strcmp(builtins[i],command)==0)
        {
            return BUILTIN;
        }      
    }
    for (int i = 0;ext_cmd[i]!=NULL; i++)//loop to check in external array
    {
         if(strcmp(ext_cmd[i],command)==0)
        {
            return EXTERNAL;
        }  
    }  
    return NO_COMMAND;
}

//signal handler for Ctrl+C and Ctrl+Z
void signal_handler(int sig_num)
{
  printf("\n");
  if(sig_num==SIGINT)
  {
    if(pid==0)//if terminal is waiting for input we need to print the prompt
    {
    printf(ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET,prompt);
    fflush(stdout);//it will print the buffer immideately
    }
  }
  if(sig_num==SIGTSTP)
  { 
     if(pid==0)//if terminal is waiting for input we need to print the prompt
    {
    printf(ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET,prompt);
    fflush(stdout);//it will print the output immideately
    }
  }
  /*if (sig_num==SIGCHLD)
  {
    waitpid(-1,&status,WNOHANG);
  }*/
}

