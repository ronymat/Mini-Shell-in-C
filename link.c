#include "header.h"

//insert first
int insert_first(Slist **head, char *input_string,int pid)
{
Slist *new;
new=malloc(sizeof(Slist));
if(new==NULL)
{
    return 0;
}
  new->pid=pid;
  strcpy(new->string, input_string);
  new->link=NULL;
   if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        Slist *temp = *head;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
    }

  return 1;
}

//delete first
int delete_first(Slist **head)
{
if(*head==NULL)
{
    return 0;//defined in header file
}
 Slist *temp=*head;//copy head to temp
 *head=temp->link;//copy link address of second node to head
 free(temp);//free the first node addres
 return 1;
}

//print list
void print_list(Slist *head)
{
	int count=1;
	if (head == NULL)
	{
		printf(ANSI_COLOR_RED"No jobs present\n"ANSI_COLOR_RESET);
		return;
	}
    else
    {
	    while (head)		
	    {
		   printf("[%d]+  Stopped    %s\n", count, head->string);
		    head = head -> link;
			count++;
	    }
    }
}