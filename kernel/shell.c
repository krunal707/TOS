/*
Krunal Shah
917262871
*/
#include <kernel.h>

void execute_process(int window_id, char*  user_input);

// compares two strings str1 and str2.
int string_compare(int window_id, char *str1, char *str2)
{
  while(*str1 == *str2)
  {
    if(*str1 == '\0' || *str2 == '\0')
      break;

    str1++;
    str2++;
  }
  if(*str1 == '\0' && *str2 == '\0')
    return 0;
  else if(*str2 == '\0')
    return 0;
  else
    return -1;
}

// History function
//Linked List for history.
struct history_list
{
		 int index;
		 char val[10];
		 struct history_list *next;
};

struct history_list *head = NULL;
struct history_list *curr = NULL;
//creating an linked list for history.
struct history_list* createHistoryLL(int index, char *val)
{
		int i=0;
		struct history_list *ptr = (struct history_list*)malloc(sizeof(struct history_list));
		if(ptr == NULL)
		{
				return NULL;
		}
		ptr->index = index;
		//ptr->val = val;
		for(i = 0; val[i] != '\0'; ++i)
		{
				ptr->val[i] = val[i];
		}
		ptr->next = NULL;
		head = curr = ptr;
		return ptr;
}
//adding to history_list.
struct history_list* addHistory(int index, char *val)
{
		int i=0;
		if(head == NULL)
		{
				return (createHistoryLL(index, val));
		}
		struct history_list *ptr = (struct history_list*)malloc(sizeof(struct history_list));
		if(ptr == NULL)
		{
				return NULL;
		}
		ptr->index = index;
		for(i = 0; val[i] != '\0'; ++i)
		{
				ptr->val[i] = val[i];
		}
		ptr->next = NULL;
		curr->next = ptr;
		curr = ptr;

		return ptr;
}
//Printing all the commands in the history_list
void printHistoryLL(int window_id)
{
		struct history_list *ptr = head;

		while(ptr != NULL)
		{
				wm_print(window_id, "\n%d. ", ptr->index);
				wm_print(window_id, "%s", ptr->val);
				ptr = ptr->next;
		}
	 return;
}

//lookup for previous command in the command history linked list
struct history_list* searchInList(int index)
{
	struct history_list **prev;
    struct history_list *ptr = head;
    struct history_list *tmp = NULL;
    int found = 0;

    while(ptr != NULL)
    {
        if(ptr->index == index)
        {
            found = 1;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }
    if(found == 1)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

//! function
int checking_function(int window_id, char *userInput)
{
  if(*userInput == '!')
  {
    return 0;
  }
  else
    return -1;
}
struct history_list* history_list_extend(int window_id, char *userInput)
{
	int n = 0;
	struct history_list *ptr = NULL;
	userInput++;
	while(*userInput != 0)
	{
		if(*userInput >= '0' && *userInput <= '9')
		{
			n = n * 10 + *userInput - '0';
			userInput++;
		}
		else if(*userInput == '\0')
		{
		}
		else
		{
			wm_print(window_id, "\nPlease enter a valid number");
			return NULL;
		}
	}
  	ptr = searchInList(n);
  	if(ptr == NULL)
    {
        wm_print(window_id, "\nNo entry found for this index");
    }
    else
    {
        wm_print(window_id, "\nExecuting Command: %s", ptr->val);
        return ptr;
    }
    return NULL;
}


// help function
void help(int window_id, char *message)
{
	wm_print(window_id,"\nThese are the list of commands that this shell supports");
	wm_print(window_id,"\n1. help -> Will print a text explaining all supported tos commands");
	wm_print(window_id,"\n2. cls -> Clears the window");
	wm_print(window_id,"\n3. shell -> Launches another shell");
	wm_print(window_id,"\n4. pong -> Launches the pong game");
	wm_print(window_id,"\n5. echo -> Echoes to the console the string that follows the command.");
	wm_print(window_id,"\n6. ps -> Prints out the process table");
	wm_print(window_id,"\n7. history -> Prints all commands that have been typed into the shell");
	wm_print(window_id,"\n8. !<number> -> Repeats the command with given number");
	wm_print(window_id,"\n9. about -> About the shell");
}


// Functions for printing all the processes
void process_heading(int window_id)
{
    wm_print(window_id, "State           Active Prio Name\n");
    wm_print(window_id, "------------------------------------------------\n");
}
void process_details(int window_id, PROCESS p)
{
    static const char *state[] = { "READY          ",
        "ZOMBIE         ",
        "SEND_BLOCKED   ",
        "REPLY_BLOCKED  ",
        "RECEIVE_BLOCKED",
        "MESSAGE_BLOCKED",
        "INTR_BLOCKED   "
    };
    if (!p->used) {
        wm_print(window_id, "PCB slot unused!\n");
        return;
    }
    /* State */
    wm_print(window_id, state[p->state]);
    /* Check for active_proc */
    if (p == active_proc)
        wm_print(window_id, " *      ");
    else
        wm_print(window_id, "        ");
    /* Priority */
    wm_print(window_id, "  %2d", p->priority);
    /* Name */
    wm_print(window_id, " %s\n", p->name);
}
void ps(int window_id)
{
    int i;
    PCB *p = pcb;

    process_heading(window_id);
    for (i = 0; i < MAX_PROCS; i++, p++) {
        if (!p->used)
            continue;
        process_details(window_id, p);
    }
}

// Echo Functions for processig and removing echo word.
char * echo_process(int window_id, char *input)
{
  static char output[20] = "";
  int i=0;
  while(*input != '\0' && *input != ' ')
  {
    input++;
  }

  while(*input != '\0' && i<20)
  {
    output[i++] = *input;
    input++;
  }
  output[i] = '\0';
  return output;
}
void echo(window_id, input)
 {
     char* display_message = echo_process(window_id, input);
     wm_print(window_id, "\n");
     wm_print(window_id,display_message);
 }


// This process will take the input from the user and then process it in execute_process
void shell_process(PROCESS self, PARAM param)
{
	    int i = 0;
    	int window_id = wm_create(10,3,50,17);
    	wm_print(window_id, "Welcome to TOS Shell");
    	while(1)
    	{
        	wm_print(window_id,"\nshell->$");
        	char input[10]="";
        	int j=0;
          // getting the user input
        	while(1)
        	{
            	char ch= keyb_get_keystroke(window_id, TRUE);
            	if(ch==13)
            	{
                	break;
            	}
              //removing of backspace
            	else if(ch==8)
            	{
                	j--;
                	input[j]=0;
                	wm_print(window_id, "%c", ch);
            	}
            	else
            	{
                	wm_print(window_id, "%c", ch);
                	input[j]=ch;
                	j++;
            	}
        	}
        	i++;
					addHistory(i, input);
          execute_process(window_id,input);
    	}
}

// This function will check the userinput and process appropriate output
void execute_process(int window_id, char*  user_input)
{

	struct history_list *h1 = NULL;

	if(string_compare(window_id, user_input, "help") == 0 )
	{
    help(window_id, user_input);
		//init_train(window_id);
	}
	else if(string_compare(window_id, user_input, "cls") == 0 )
	{
		wm_clear(window_id);
	}
  else if(string_compare(window_id, user_input, "train") == 0 )
  {
    init_train(window_id);
  }
	else if(string_compare(window_id, user_input, "shell") == 0 )
	{
		create_process(shell_process,6,0,"Shell Process");
	}
	else if(string_compare(window_id, user_input, "pong") == 0 )
	{
		start_pong();
	}
	else if(string_compare(window_id, user_input, "echo") == 0 )
	{
		echo(window_id, user_input);
	}
	else if(string_compare(window_id, user_input, "ps") == 0 )
  {
		wm_print(window_id,"\n");
		ps(window_id);
	}
	else if(string_compare(window_id, user_input, "history") == 0 )
  {
		printHistoryLL(window_id);
	}
	else if(checking_function(window_id, user_input) == 0 )
	{
		h1 = history_list_extend(window_id, user_input);
		execute_process(window_id, h1->val);
	}
	else if(string_compare(window_id, user_input, "about") == 0 )
	{
		wm_print(window_id, "\nThis is the TOS Shell");
	}
	else
		wm_print(window_id, "\nInvalid input argument. Type 'help' to check for options");
}

void start_shell()
{
	create_process(shell_process,6,0,"Shell Process");
	resign();
}
