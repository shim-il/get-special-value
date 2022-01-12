#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"

/*
Shimon Port.
This program returns the ascii decimal value of a chosen chaerecter inside of a file. The charecter is chosen acording to the number the user provides at the input. If there is a problme with a spicific file the program will notify and continue to next file. If there is a problem with user input the program will notefy and stop the program. */

int main(int argc, char *argv[])
{
	int target_num, found_val, i;

	/* Check if argument is valid and get number for search */
	target_num = get_num(argc, argv[1]);

	if (target_num == ERROR_MISSING_ARGUMENT) /* Error */
	{
		printf("Missing target number\n");
		return ERROR;
	}
	else if (target_num == ERROR_WRONG_ARGUMENT)
	{
		printf("Second argument must be a number and bigger than 0\n");
		return ERROR;
	}

	/* Send files to get target value in ascii decimal number */
	for (i = 2; i < argc; i++)
	{
		found_val = find_char(argv[i], target_num);

		if (found_val == ERROR_F_DOSENT_EXIST)
		{
			printf("File %s not found, check if file exists. Trying next file\n" , argv[i]);
		}
		else if (found_val == ERROR_FUNCTION)
		{
			printf("Error while accessing file %s. Trying next file\n" , argv[i]);
		}
		else if (found_val == ERROR_OUT_OF_BOUND)
		{
			printf("File %s has less text charecters than %d. Trying next file\n" , argv[i], target_num);
		}
		else /* Success */
		{
			printf("The value of the chosen charecter in file - %s - is : %d \n" , argv[i], found_val);
		}
	}

	return 0;
}

/* Check if input has less than one argument or 2nd argument is not a number or negetive number => error, else get number for search */
int get_num(int argc, char *argv)
{
	int num;

	if (argc < 2)
		return ERROR_MISSING_ARGUMENT;

	num = atoi(argv);
	if (num <= 0) /* 0 means not a number was found in second argument */
		return ERROR_WRONG_ARGUMENT;	

	return num;
}

/* Return the charecter's value in ascii decimal number acording to users target number choice. If there is an ERROR will send propper error value acordingly. */ 
char find_char(char *file_path, int target_num)
{
	char target_val;
	FILE *fptr = fopen(file_path, "r");

	if (fptr == NULL) /* No such file */
	{
		return ERROR_F_DOSENT_EXIST;
	}
	else if (fseek(fptr, target_num - 1, SEEK_SET) != 0) /* Error opon function */
	{
		fclose(fptr);
		return ERROR_OUT_OF_BOUND;
	}
	else
	{
		target_val = getc(fptr);
		fclose(fptr);
		if (target_val < 0) /* Out of bound, reached garbage value */
			return ERROR_OUT_OF_BOUND;
		else
			return target_val;
	}
}
