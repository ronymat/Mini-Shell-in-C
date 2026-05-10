#include "header.h"
char input_string[100];
char prompt[50]="minishell:~$ ";//it is the default name 
int main()
{
    setbuf(stdout, NULL);
    system("clear");//it is used  to clear the terminal 
    scan_input(prompt,input_string);
    return 0;
}