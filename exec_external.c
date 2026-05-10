#include "header.h"
//external command exicution
void execute_external_commands(char *input_string)
{
  //add the input string to an argument array 
 char *argv[10];
 char str[100];
 int i=0,j=0,k=0;
 while ( input_string[i]!='\0')// Loop to split words based on space
 {
    if (input_string[i]!=' ')
    {
            str[k]=input_string[i];
            i++;
            k++;
    }else
    {
        str[k]='\0';   // terminate the word when space is found
        argv[j]=malloc(strlen(str)+1);
        strcpy(argv[j],str);
        j++;
        i++;;    
        k=0;
    }
  }
  if(k > 0)//to get the last string in the array 
  {
      str[k] = '\0';
      argv[j] =malloc(strlen(str)+1);
      strcpy(argv[j],str);
      j++;
  }
// mark end of argument array with NULL
 argv[j]=NULL;
 int argc=j;

//check if pipe is present or nor
int pipe_exist=0;
for (int i = 0; i<argc; i++)
{
 if(strcmp(argv[i],"|")==0)
 {
  pipe_exist=1;
  break;
 }
}

//if pipe not exist
if(pipe_exist==0)
{
  int pid=fork();
  if(pid==0)
  {
    execvp(argv[0],argv);
   printf(ANSI_COLOR_RED"Error: Command not found\n"ANSI_COLOR_RESET);
    exit(1);
  }else 
  {
    waitpid(pid,NULL,0);
  }
}else//if pipe exists
{
  //run a program for n number of pipes
  int arr[argc];
    arr[0]=0;
    int ind=1;
    int i;
   for(i=0;i<argc;i++)
   {
    if(strcmp(argv[i],"|")==0)
    {
    argv[i]=NULL;
    arr[ind]=i+1;
    ind++;
    }
   }
   int fd[2];
   int input=0;//used to store readent of previous pipe
   for ( i = 0; i < ind; i++)
   {
    if(i!=ind-1)
    {
      pipe(fd);
    }
      int pid=fork();

      if(pid>0)
      {
        if(i!=ind-1)
        {
        close(fd[1]);
        input=fd[0]; // store read end for next command
        }
      }else if(pid==0)
      {
        dup2(input,0);// redirect stdin from previous pipe
        if(i!=ind-1)
        {
          dup2(fd[1],1);
        }
        close(fd[0]);
      execvp(argv[arr[i]],argv+arr[i]);//execute command
      printf(ANSI_COLOR_RED"Error: Command not found\n"ANSI_COLOR_RESET);
       exit(1);
      }
    } 
    for (i=0;i<ind;i++)// parent waits for all child processes
    {
       wait(NULL);
    }  
}
}