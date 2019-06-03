
#include <kernel.h>
#define ticks 15

//Helper functions
int len(char *str, int windowId)
{
   	int x = 0;
   	while (*str != '\0') 
   	{
      	x++;
      	str++;
   	}
   	return x;
}

char itoa(int x)
{
	x = x + 48;
	return x;
}

// Initializing switches for zamboni
void initSwitches(int windowId)
{
	char clearBuffer[] = "R\0";

	wm_print(windowId, "\nSeeting the loop for Zamboni");
	//set 5 to green
	char cmd[] = "M5G\0";
	sendCommand(windowId, cmd, 0);

	//set 8 to green
	cmd[1] = '8';
	sendCommand(windowId, cmd, 0);
	
	//set 9 to red
	cmd[1] = '9';
	cmd[2] = 'R';
	sendCommand(windowId, cmd, 0);

	//set 1 to Green
	cmd[1] = '1';
	cmd[2] = 'G';
	sendCommand(windowId, cmd, 0);
	
	//set 4 to green
	cmd[1] = '4';
	sendCommand(windowId, cmd, 0);
	
	//clean the buffer
	sendCommand(windowId, clearBuffer, 0);
}

//function to implement different commands
int sendCommand(int windowId, char *command, int inputLen)
{

	int x = 0;
	char *inputBuf;
	char userInput[10]="";
	while (*command != '\0') 
    {
    	userInput[x] = *command;
      	x++;
      	command++;
   	}
   	
	COM_Message msg;
	
	int lengthofOutputBuf = len(userInput, windowId);
	
	userInput[lengthofOutputBuf] = '\015';
	msg.output_buffer = userInput;
	msg.input_buffer = inputBuf;
	msg.len_input_buffer = inputLen;

	sleep(ticks);
	send(com_port,&msg);

	if(msg.input_buffer[1] == '1')
		return 1;
	else
		return 0;
}

//function to find the location of the train
int findTrain(int windowId, int zamLocation)
{
	wm_print(windowId, "\nFinding Location of Train");
	char clearBuffer[] = "R\0";
	char cmd1[] = "C8\0";
	char cmd2[] = "C11\0";
	//char cmd3[] = "C2\0";
	//char cmd4[] = "C5\0";

	int onTrack1 = 0;
	int onTrack2 = 0;

	//checking 1st confifuration with and without zamboni
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd1, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId,cmd2, 3 );
	if(onTrack1 ==1 && onTrack2 == 1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 1 it is!");
		return 8;
	}
	
	if(onTrack1 ==1 && onTrack2 == 1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 1 it is without Zamboni!");
		return 8;
	}

	cmd2[1] = '1';
	cmd2[2] = '2';
	cmd2[3] = '\0';

	cmd1[1] = '2';
	cmd1[2] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd1, 3);


	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 2 it is with Zamboni!");
		return 12;
	}
	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 2 it is without Zamboni!");
		return 12;
	}

	cmd2[1] = '2';
	cmd2[2] = '\0';
	//cmd2[3] = '\0';

	cmd1[1] = '1';
	cmd1[2] = '1';
	cmd1[3] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd1, 3);


	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 3 it is with Zamboni!");
		return 2;
	}
	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 3 it is without Zamboni!");
		return 2;
	}

	cmd2[1] = '5';
	cmd2[2] = '\0';
	//cmd2[3] = '\0';

	cmd1[1] = '1';
	cmd1[2] = '2';
	cmd1[3] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd1, 3);


	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 4 it is with Zamboni!");
		return 5;
	}
	if(onTrack1 == 1 && onTrack2 == 1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 4 it is without Zamboni!");
		return 5;
	}


	//checking 2nd configuration with and without zamboni
	/*
	cmd2[1] = '1';
	cmd2[2] = '1';
	cmd2[3] = '\0';

	cmd1[1] = '2';
	cmd1[2] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd1, 3);
	if(onTrack1==1 && onTrack2==1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 2 detected");
		return 11;
	}

	if(onTrack1==1 && onTrack2==1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 6 detected");
		return 11;
	}

	//checking 3rd configuration with and without zamboni
	cmd2[1] = '1';
	cmd2[2] = '6';
	cmd2[3] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd3, 3);
	if(onTrack1==1 && onTrack2==1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 3 detected");
		return 16;
	}

	if(onTrack1==1 && onTrack2==1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 7 detected");
		return 16;
	}

	//checking 4th configuration with and without zamboni
	cmd1[1] = '8';
	cmd1[2] = '\0';
	sendCommand(windowId, clearBuffer, 0);
	onTrack1 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	onTrack2 = sendCommand(windowId, cmd1, 3);
	if(onTrack1==1 && onTrack2==1 && zamLocation == 0)
	{
		wm_print(windowId, "\nConfiguration 4 detected");
		return 16;
	}

	if(onTrack1==1 && onTrack2==1 && zamLocation == 1)
	{
		wm_print(windowId, "\nConfiguration 8 detected");
		return 16;
	}
	*/
}

//function to find where the wagon is
int wagonLocation(int windowId, int trainLocation)
{
	char clearBuffer[] = "R\0";
	char cmd1[] = "C11\0";
	char cmd2[] = "C2\0";
	sendCommand(windowId, clearBuffer, 0);
	int onTrack2 = sendCommand(windowId, cmd2, 3);
	sendCommand(windowId, clearBuffer, 0);
	int onTrack1 = sendCommand(windowId, cmd1, 3);
	wm_print(windowId, "\nFinding location of the wagon");
	if (trainLocation == 8)
	{
		return 11;
	}
	else if (trainLocation == 12)
	{
		return 2; 
	}
	else if (trainLocation == 2/*&& onTrack1==1*/)
	{
		return 11;
	}
	else if (trainLocation == 5/* && onTrack2==1*/)
	{
		return 12;
	}
	else
		return 0;
}

//Function to check if Zamboni is there or not
int zamboniLocation(int windowId)
{
	wm_print(windowId, "\nFinding if Zamboni is present today!");
	int z=2;
	char clearBuffer[] = "R\0";
	char Cmd1[] = "C10\0";
	for (z=0; z<20; z++)
	{	
		sendCommand(windowId, clearBuffer, 0);
		int z = sendCommand(windowId, Cmd1, 3);
		if(z==1)
		{
			return 1;
		}
	}
	return 0;
}


//function to stop the train until train gets probed on track t
int waitUntilOnTrack(int windowId, int t)
{
	char clearBuffer[] = "R\0";
	char Cmd1[] = "C7\0";
	char Cmd2[] = "C10\0";
	
	if (t<10)
	{
		Cmd1[1] = itoa(t);
		while(1)
		{	
			sendCommand(windowId, clearBuffer, 0);
			int onTrack1 = sendCommand(windowId, Cmd1, 3);
			if(onTrack1)
			{
				return 1;
			}
		}
	}
	else
	{
		int r = t % 10;
		int l = 1;
		char rq = itoa(r);
		char lq = itoa(l);
		Cmd2[1] = lq;
		Cmd2[2] = rq;
		while(1)
		{	
			sendCommand(windowId, clearBuffer, 0);
			int onTrack1 = sendCommand(windowId, Cmd2, 3);
			if(onTrack1)
			{
				return 1;
			}
		}
	}
}

//function to stop the train and reverse it
/*
void ChangeDirection(int windowId)
{
	char DirCom[] =  "L20D\0";
	char trainCmd[] = "L20S4\0";
	//stop the train
	trainCmd[4] = '0';
	sendCommand(windowId, trainCmd, 0);
	//change the direction
	sendCommand(windowId, DirCom, 0);
	//start the train
	//trainCmd[4] = '4';
	//sendCommand(windowId, trainCmd, 0);
}
*/


//function to implement configuration 1 with zamboni
int configuration_1(int windowId)
{
	/*

	// Solution 1

	char Switchcmd[] = "M8R\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";


	// set stiches for this connection
	Switchcmd[2] = 'R';
	Switchcmd[1] = '6';
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[2] = 'R';
	Switchcmd[1] = '5';
	sendCommand(windowId, Switchcmd, 0);


	//Wait for zamboni to be probed on track 7
	waitUntilOnTrack(windowId, 7);
	//start the train
	wm_print(windowId, "\nStarting the Train");
	sendCommand(windowId, trainCmd, 0);

	Switchcmd[2] = 'R';
	Switchcmd[1] = '8';
	wm_print(windowId, "\nProbing track 10");
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);


	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, trainCmd, 0);

	trainCmd[4]='5';
	waitUntilOnTrack(windowId, 13);
	sendCommand(windowId, trainCmd, 0);

//  wait until train arrives on track 12
	wm_print(windowId, "\nProbing track 12");
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, Switchcmd, 0);

//	wait until train arrives on track 12
	wm_print(windowId, "\nProbing track 12");
	Switchcmd[2] = 'R';
	Switchcmd[1] = '8';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);

// Stop and reverse
	wm_print(windowId, "\nProbing track 14");
	wm_print(windowId, "\nStop and Reverse");
	waitUntilOnTrack(windowId, 4);
	trainCmd[4]='0';
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, DirCom, 0);
	//ChangeDirection(windowId);
	trainCmd[4]='4';
	sendCommand(windowId, trainCmd, 0);


	wm_print(windowId, "\nProbing track 8");
	wm_print(windowId, "\nStop the train: Reached");
	waitUntilOnTrack(windowId, 8);
	trainCmd[4]='0';
	sendCommand(windowId, trainCmd, 0);
	*/

	// Solution 2

	char Switchcmd[] = "M8R\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";


	// set stiches for this connection
	Switchcmd[2] = 'R';
	Switchcmd[1] = '6';
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[2] = 'R';
	Switchcmd[1] = '5';
	sendCommand(windowId, Switchcmd, 0);


	//Wait for zamboni to be probed on track 7
	waitUntilOnTrack(windowId, 7);
	//start the train
	wm_print(windowId, "\nStarting the Train");
	sendCommand(windowId, trainCmd, 0);

	Switchcmd[2] = 'R';
	Switchcmd[1] = '8';
	wm_print(windowId, "\nProbing track 10");
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[2] = 'G';
	Switchcmd[1] = '8';
	wm_print(windowId, "\nProbing track 12");
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, Switchcmd, 0);


	// trainCmd[4]='0';
	// waitUntilOnTrack(windowId, 12);
	// sendCommand(windowId, trainCmd, 0);

	// trainCmd[4]='5';
	// waitUntilOnTrack(windowId, 13);
	// sendCommand(windowId, trainCmd, 0);

//  wait until train arrives on track 12
	// wm_print(windowId, "\nProbing track 12");
	// Switchcmd[1] = '8';
	// Switchcmd[2] = 'G';
	// waitUntilOnTrack(windowId, 12);
	// sendCommand(windowId, Switchcmd, 0);

//	wait until train arrives on track 12
	wm_print(windowId, "\nProbing track 10");
	Switchcmd[2] = 'R';
	Switchcmd[1] = '8';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);

// Stop and reverse
	wm_print(windowId, "\nProbing track 14");
	wm_print(windowId, "\nStop and Reverse");
	waitUntilOnTrack(windowId, 4);
	trainCmd[4]='0';
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, DirCom, 0);
	//ChangeDirection(windowId);
	trainCmd[4]='4';
	sendCommand(windowId, trainCmd, 0);


	wm_print(windowId, "\nProbing track 8");
	wm_print(windowId, "\nStop the train: Reached");
	waitUntilOnTrack(windowId, 8);
	trainCmd[4]='0';
	sendCommand(windowId, trainCmd, 0);

	become_zombie();

	

	return 1;
}

int configuration_2(int windowId)
{

	// solution 1
	char Switchcmd[] = "M8R\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";

	// set swiches for this configuration
	Switchcmd[1] = '7';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[1] = '8';
	//Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[1] = '2';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[1] = '6';
	//Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);


	//ChangeDirection(windowId);
	wm_print(windowId, "\nStarting the Train");
    wm_print(windowId, "\nProbing track 3");
	sendCommand(windowId, DirCom, 0);
	Switchcmd[1] = '1';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 3);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);


	// Switchcmd[1] = '1';
	// Switchcmd[2] = 'R';
	// waitUntilOnTrack(windowId, 11);
	// sendCommand(windowId, Switchcmd, 0);
	wm_print(windowId, "\nProbing track 1");
	wm_print(windowId, "\nStop the train");
	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 1);	
	sendCommand(windowId, trainCmd, 0);

	wm_print(windowId, "\nProbing track 13");
	Switchcmd[1] = '1';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 13);
	sendCommand(windowId, Switchcmd, 0);

	wm_print(windowId, "\nProbing track 7");
	trainCmd[4]='5';
	waitUntilOnTrack(windowId, 7);	
	sendCommand(windowId, trainCmd, 0);

	wm_print(windowId, "\nProbing track 6");
	wm_print(windowId, "\nStart train again");
	Switchcmd[1] = '5';
	Switchcmd[2] = 'R';
	trainCmd[4]='4';
	waitUntilOnTrack(windowId, 6);
	sendCommand(windowId, Switchcmd, 0);
	sendCommand(windowId, trainCmd, 0);

	wm_print(windowId, "\nProbing track 12");
	wm_print(windowId, "\nReached");
	trainCmd[4]='0';
	Switchcmd[1] = '5';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 12);	
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);

	// Switchcmd[1] = '5';
	// Switchcmd[2] = 'G';
	// waitUntilOnTrack(windowId, 6);
	// sendCommand(windowId, Switchcmd, 0);


	// Solution 2




	become_zombie();

	return 1;
}


int configuration_3(int windowId)
{
	char Switchcmd[] = "M6G\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";

	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '2';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '7';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '2';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	wm_print(windowId, "\nStarting the Train");
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, trainCmd, 0);

	wm_print(windowId, "\nProbing track 6");
	Switchcmd[1] = '5';
	Switchcmd[2] = 'R';
	trainCmd[4]='4';
	waitUntilOnTrack(windowId, 6);
	sendCommand(windowId, Switchcmd, 0);


	wm_print(windowId, "\nProbing track 12");
	wm_print(windowId, "\nStop the train");
	trainCmd[4]='0';
	Switchcmd[1] = '5';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);
	sendCommand(windowId, DirCom, 0);
	//ChangeDirection(windowId);



	wm_print(windowId, "\nProbing track 3");
	wm_print(windowId, "\nStart again");
	trainCmd[4]='5';
	waitUntilOnTrack(windowId, 3);
	sendCommand(windowId, trainCmd, 0);


	wm_print(windowId, "\nProbing track 13");
	Switchcmd[1] = '1';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 13);
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '2';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);


	wm_print(windowId, "\nProbing track 2");
	wm_print(windowId, "\nStop the train: Reached");
	trainCmd[4]='0';
	Switchcmd[1] = '1';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 2);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);


	return 1;
}


int configuration_4(int windowId)
{
	char Switchcmd[] = "M3R\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";
	

	

	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '6';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '5';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '3';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	
	wm_print(windowId, "\nStarting the Train");

	waitUntilOnTrack(windowId, 4);
	sendCommand(windowId, trainCmd, 0);


	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 9);
	sendCommand(windowId, trainCmd, 0);



	trainCmd[4]='5';
	waitUntilOnTrack(windowId, 14);
	sendCommand(windowId, trainCmd, 0);

	Switchcmd[1] = '4';
	Switchcmd[2] = 'R';
	trainCmd[4]='4';
	waitUntilOnTrack(windowId, 4);
	sendCommand(windowId, Switchcmd, 0);
	sendCommand(windowId, trainCmd, 0);


	Switchcmd[1] = '4';
	Switchcmd[2] = 'G';
	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 5);
	sendCommand(windowId, Switchcmd, 0);
	sendCommand(windowId, trainCmd, 0);





	/*

	

	sendCommand(windowId, Switchcmd, 0);

	waitUntilOnTrack(windowId, 4);
	sendCommand(windowId, trainCmd, 0);



	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 6);
	sendCommand(windowId, trainCmd, 0);
	//sendCommand(windowId, DirCom, 0);
	Switchcmd[1] = '4';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	trainCmd[4]='5';
	sendCommand(windowId, trainCmd, 0);


	trainCmd[4]='0';
	Switchcmd[1] = '4';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 1);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '3';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	


	trainCmd[4]='5';
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);

	
	Switchcmd[1] = '4';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 4);
	sendCommand(windowId, Switchcmd, 0);

	wm_print(windowId, "\nStop the train: Reached");
	Switchcmd[1] = '4';
	Switchcmd[2] = 'G';
	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 5);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, Switchcmd, 0);

	*/
	become_zombie();

	//return 1;

	
	//solution2

	/*

	sendCommand(windowId, Switchcmd, 0);


	waitUntilOnTrack(windowId, 4);
	sendCommand(windowId, trainCmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 6);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, DirCom, 0);
	trainCmd[4]='5';
	sendCommand(windowId, trainCmd, 0);


	Switchcmd[1] = '8';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='0';
	//Switchcmd[1] = '8';
//	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 11);
	sendCommand(windowId, trainCmd, 0);
	//sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='5';
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);
	sendCommand(windowId, trainCmd, 0);

	Switchcmd[1] = '8';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 10);
	sendCommand(windowId, Switchcmd, 0);

	Switchcmd[1] = '4';
	Switchcmd[2] = 'R';
	waitUntilOnTrack(windowId, 7);
	sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 7);
	sendCommand(windowId, trainCmd, 0);

	return 1;

	*/

}
int configuration_1_withoutZamboni(int windowId)
{
	char Switchcmd[] = "M4G\0";
	char trainCmd[] = "L20S5\0";
	char DirCom[] =  "L20D\0";

	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '8';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '5';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '6';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	sendCommand(windowId, trainCmd, 0);
	
	waitUntilOnTrack(windowId, 12);
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 7);
	sendCommand(windowId, trainCmd, 0);
	sendCommand(windowId, DirCom, 0);
	trainCmd[4]='3';
	sendCommand(windowId, trainCmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 8);
	sendCommand(windowId, trainCmd, 0);

	return 1;
}

int configuration_2_withoutZamboni(int windowId)
{
	char Switchcmd[] = "M4R\0";
	char trainCmd[] = "L20S5\0";
	
	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	// Switchcmd[1] = '5';
	// Switchcmd[2] = 'R';
	// sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '3';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);
	// Switchcmd[1] = '6';
	// Switchcmd[2] = 'G';
	// sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);

	sendCommand(windowId, trainCmd, 0);

	Switchcmd[1] = '8';
	Switchcmd[2] = 'R';	
	waitUntilOnTrack(windowId, 7);
	sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, trainCmd, 0);

	return 1;
}

int configuration_3_withoutZamboni(int windowId)
{
	char Switchcmd[] = "M5g\0";
	char trainCmd[] = "L20S5\0";
	
	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '9';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '1';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '2';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '7';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	sendCommand(windowId, trainCmd, 0);

	Switchcmd[1] = '2';
	Switchcmd[2] = 'G';	
	waitUntilOnTrack(windowId, 12);
	sendCommand(windowId, Switchcmd, 0);

	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 2);
	sendCommand(windowId, trainCmd, 0);

	return 1;
}

int configuration_4_withoutZamboni(int windowId)
{

	char Switchcmd[] = "M5R\0";
	char trainCmd[] = "L20S5\0";
	
	// set swiches for this configuration
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '6';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '8';
	Switchcmd[2] = 'G';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '4';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);
	Switchcmd[1] = '3';
	Switchcmd[2] = 'R';
	sendCommand(windowId, Switchcmd, 0);

	sendCommand(windowId, trainCmd, 0);


	trainCmd[4]='0';
	waitUntilOnTrack(windowId, 5);
	sendCommand(windowId, trainCmd, 0);

	return 1;
}





void train_process(PROCESS self, PARAM param)
{

	// int window_id = wm_create(1,1,50,17);
	// wm_print(window_id,"Let the Train Process begin");
	int windowId = wm_create(1, 1, 50, 17);
	wm_print(windowId, "Let the journey begin");
	initSwitches(windowId);


	//Zamboni's Location
	int zamLocation = zamboniLocation(windowId);

	//Train's Location
	int trainAt = findTrain(windowId, zamLocation);
	
	//find the location of wagon
	int wagonAt = wagonLocation(windowId, trainAt); 

	wm_print(windowId, "\nTrain is on Track : %d", trainAt);
	wm_print(windowId, "\nWagon is on Track : %d", wagonAt);

	if(zamLocation == 1)
	{
		
		wm_print(windowId, "\nZamboni is present");
		if (trainAt == 8 && wagonAt == 11 && zamLocation == 1)
		{
			configuration_1(windowId);
		}
		else if (trainAt == 12 && wagonAt == 2 && zamLocation == 1)
		{

			configuration_2(windowId);
		}
		else if (trainAt == 2 && wagonAt == 11 && zamLocation == 1)
		{

			configuration_3(windowId);
		}
		else if (trainAt == 5 && wagonAt == 12 && zamLocation == 1)
		{

			configuration_4(windowId);
		}
		else
		{
			wm_print(windowId, "\nError Occured");
		}
	}
	else
	{
		wm_print(windowId, "\nZamboni is absent");
		if (trainAt == 8 && wagonAt == 11)
		{
			configuration_1_withoutZamboni(windowId);
		}
		else if (trainAt == 12 && wagonAt == 2)
		{

			configuration_2_withoutZamboni(windowId);
		}
		else if (trainAt == 2 && wagonAt == 11)
		{

			configuration_3_withoutZamboni(windowId);
		}
		else if (trainAt == 5 && wagonAt == 12)
		{

			configuration_4_withoutZamboni(windowId);
		}		
		else
		{
			wm_print(windowId, "\nError Occured");
		}
	}	
	



	
	

	remove_ready_queue(active_proc);
	resign();
}


void init_train()
{
	create_process(train_process, 5, 0, "trainProcess");
}
