#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//#define MAXLENGTH_PER_LINE 1000
#define OUTPUT_INCREASE 1000
//#define INCREASE 16

extern int errno;

int is_colin(int *rows, int rowssize, int rowcur)
{
	int i;
	for (i = 0; i < rowssize; i++)
	{
		if (rowcur == rows[i])
		{
			return 1;
		}
	}
	return 0;
}

int extract(int *rows, int rowssize, char sep, int igln)
{
	char *output = realloc(NULL, sizeof(char) * OUTPUT_INCREASE);
	char ch;
	size_t outlen = 0, outsize = OUTPUT_INCREASE;
	int colnum = 1, line = 1, colinbefore = 0, colin = 0, doublequotes = 0;
	colin = is_colin(rows, rowssize, colnum);
	while (EOF != (ch = fgetc(stdin)))
	{
		// main algorithm
		switch (ch)
		{
		case '"': // doublequotes processing
			doublequotes = (doublequotes + 1) % 2;
			// add this char
			if (colin && line > igln)
			{
				output[outlen] = '"';
				outlen++;
			}
			break;
		case '\n':
			// add '\n' at the previous position to replace the sep
			if (line > igln)
			{
				output[outlen - 1] = '\n';
			}
			line++;
			colnum = 1;
			colin = is_colin(rows, rowssize, colnum);
			colinbefore = 0;
			break;
		default:
			if (ch == sep)
			{
				if (doublequotes == 0)
				{
					colnum += 1;
					colinbefore = colin;
					colin = is_colin(rows, rowssize, colnum);
					if (colinbefore && line > igln)
					{
						output[outlen++] = sep;
					}
				}
				else
				{
					if (colin)
					{
						output[outlen++] = sep;
					}
				}
			}
			else if (line > igln) // skip line
			{
				// find column
				if (colin)
				{
					output[outlen++] = ch;
				}
			}
		}
		// extend size of output
		if (outlen == outsize)
		{
			output = realloc(output, sizeof(char) * (outsize += OUTPUT_INCREASE));
			if (!output)
			{
				perror("Error during reallocation");
				return -1;
			}
		}
	}
	output[outlen++] = '\0';

	printf("%s", output);
	return 0;
}

int check_rows(int* rows, int size){
	int i,j;
	for(i=0;i<size;i++){
		// check repeatation and increasing
		for(j=0;j<i;j++){
			if(rows[i]<=rows[j]){
				return -1;
			}
		}
		
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int opt, lastoptind = 1;
	char sep = ' '; // default separator: one space
	int igln = 0;   // the number of lines to ignore (default: 0)

	// read options
	while ((opt = getopt(argc, argv, "s:i:")) != -1)
	{
		switch (opt)
		{
		case 's':
			sep = optarg[0];
			lastoptind = optind;
			break;
		case 'i':
			igln = (int)strtol(optarg, NULL, 10);
			lastoptind = optind;
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-s separator] [-i the number of lines to ignore] row numbers to extract \n",
					argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	// printf("sep=%c igln=%d\n", sep, igln);

	// check the order of options
	if (optind < lastoptind)
	{
		fprintf(stderr, "Expected argument after options, no argument before options!\n");
		exit(EXIT_FAILURE);
	}

	//printf("name argument = %s, %s\n", argv[optind], argv[optind + 1]);

	// get num for columns
	int iarg = optind, size = 0;
	for (; iarg < argc; iarg++)
	{
		if (strtol(argv[iarg], NULL, 10) != 0)
		{
			size++;
		}
		else
		{
			break;
		}
	}

	int *rows = (int *)malloc(size * sizeof(int));
	// get rows' numbers
	int i = 0;
	for (iarg = optind; iarg < argc; iarg++)
	{
		if (strtol(argv[iarg], NULL, 10) != 0)
		{
			rows[i++] = (int)strtol(argv[iarg], NULL, 10);
		}
		else
		{
			break;
		}
	}

	// check the validation of the rows
	if(check_rows(rows, size)){
		fprintf(stderr, "1. Field numbers should always be provided in increasing sequence\n\
2. You cannot repeat a field\n");
		exit(EXIT_FAILURE);
	}
	extract(rows, size, sep, igln);

	exit(EXIT_SUCCESS);
}
