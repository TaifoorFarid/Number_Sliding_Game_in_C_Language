#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

void dfLvl(int *sizPtr, int *triesPtr)
{
	int OK = 1;
	while(OK)
	{
		int choice;
    	printf("\n\tChose The Difficulty Level:");
    	printf("\n\t1. Easy.");
    	printf("\n\t2. Medium.");
    	printf("\n\t3. Hard.");
    	printf("\n\t4. Very Hard.\n");
    	scanf("%d", &choice);
    	system("cls");
	
    	switch(choice)
    	{
    		case 1:
	    		*sizPtr = 3;
	    		*triesPtr = 300;
	    		OK = 0;
	    		break;
	    	case 2:
	    		*sizPtr = 4;
	    		*triesPtr = 330;
	    		OK = 0;
	    		break;
	    	case 3:
	    		*sizPtr = 5;
	    		*triesPtr = 375;
	    		OK = 0;
	    		break;
	    	case 4:
	    		*sizPtr = 6;
	    		*triesPtr = 475;
	    		OK = 0;
	    		break;
	    	default:
	    		printf("\n\tChoice Doesnot Exist!!!\n");
    	}
	}
}


void rules(int size)
{
	 printf("                 RULE OF THIS GAME                 \n");
    printf("\n1.You can move only 1 step at a time by arrow key ");
    printf("\nMove Up   : by Up arrow key ");
    printf("\nMove Down : by Down arrow key");
    printf("\nMove Left : by Left arrow key");
    printf("\nMove Right: by Right arrow key");

    printf("\n2.You can move number at empty position only ");
    printf("\n");
    printf("\n3.For each valid move : your total number of move will decreased by 1 \n");
    printf("4.Wining situation : ");
    printf("number in a %dx%d matrix should be in order from 1 to %d ", size, size, size*size-1);
    printf("\n\n            winning situation:         \n");

    for(int i = 0 ; i < size*size ; i++)
    {
    	if(i == (size*size-1))
    	printf("|    |");
    	else if((i+1) % size == 0)
    	printf("| %-3d|\n", i + 1);
    	else
    	printf("| %-3d", i + 1);
    	
	}
    printf("\n5.You can exit the game at any time by pressing 'E' or 'e' ");


    printf("\nSo Try to win in minimum no of move \n");
    printf("\n         Happy gaming , Good Luck\n");

    printf("\nEnter any key to start.....   ");
}

int findZero(int num[], int size)
{
	for(int i = 0 ; i < size*size ; i++)
		if(num[i] == 0)
    		return i;
}

void storeNum(int num[], int size)
{
	int n[size*size];
	for(int j = 0 ; j < size*size ; j++)
	n[j] = j;
	int last_ind = size*size - 1;
	int index;
	
	srand(time(NULL));
	for(int i = 0 ; i < size*size ; i++)
	{
		index = rand() % (last_ind + 1);
		num[i] = n[index];
		n[index] = n[last_ind--];
	}
}

void printNum(int num[], int size, int tries)
{
	printf("\n\tMove Remaining: %d\n\n\t", tries);
	for(int i = 0 ; i < size*size ; i++)
	{
		if(num[i] == 0)
    		printf("|    ");
		else
    		printf("| %-3d", num[i]);
		if((i + 1) % size == 0)
    		printf("|\n\t");
	}
}

void UpKey(int num[], int size, int *triesPtr)
{
	int index = findZero(num, size);
	int shift = index + size;
	if(shift > (size*size-1))
    	return;
    else
    {
    	num[index] = num[shift];
    	num[shift] = 0;
    	--*triesPtr;
	}
}


void DownKey(int num[], int size, int *triesPtr)
{
	int index = findZero(num, size);
	int shift = index - size;
	if(shift < 0)
    	return;
    else
    {
    	num[index] = num[shift];
    	num[shift] = 0;
    	--*triesPtr;
	}
}

void LeftKey(int num[], int size, int *triesPtr)
{
	int index = findZero(num, size);
	int shift = index + 1;
	if(shift % size == 0)
    	return;
    else
    {
    	num[index] = num[shift];
    	num[shift] = 0;
    	--*triesPtr;
	}
}

void RightKey(int num[], int size, int *triesPtr)
{
	int index = findZero(num, size);
	int shift = index - 1;
	if((shift + 1) % size == 0)
    	return;
    else
    {
    	num[index] = num[shift];
    	num[shift] = 0;
    	--*triesPtr;
	}
}

int checkPattern(int num[], int size)
{
	for(int i = 1 ; i < size*size ; i++)
	{
		if(num[i-1] == i)
	    	continue;
		else
	    	return 1;
	}
	return 0;
}

int main()
{
	char name[20];
	printf("Please Enter Your Good Name: ");
	fgets(name, 20, stdin);
	
	
	int size;
	int max_tries;
	
	dfLvl(&size, &max_tries);
	int num[size*size];
	storeNum(num, size);
	
	rules(size);
	
	if(getch() != 'e' && getch() != 'E')
	{
    	while(checkPattern(num, size) && max_tries != 0)
    	{
    		system("cls");
    		printNum(num, size, max_tries);
    		int key = getche();
    		switch(key)
    		{
    			case 72:// Up key
    	    		UpKey(num, size, &max_tries);
    	    		break;
    			case 80:// Down key
    	    		DownKey(num, size, &max_tries);
    	    		break;
    			case 75:// Left key
    	        	LeftKey(num, size, &max_tries);
    				break;	
    			case 77:// Right key
    	    		RightKey(num, size, &max_tries);
    	    		break;
    	    	case 'e':
    	    		printf("\nThanks %s for playing this game hope you enjoyed", name);
    	    		exit(0);
    	    	case 'E':
    	    		printf("\nThanks %s for playing this game hope you enjoyed", name);
    	    		exit(0);
    	    	default:
    	    		printf(" ");//you can write anything here.
    		}
    	}//end of while
    	if(max_tries == 0)
    	{
    		system("cls");
        	printNum(num, size, max_tries);
        	printf("\n\tSorry %s You Lose!!!\nYou ran out of moves.", name);
		}
		else
		{
			system("cls");
          	printNum(num, size, max_tries);
        	printf("\n\tCongratulations %s You Won!!", name);
		}
    }//end of if
	return 0;
}
