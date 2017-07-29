#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//#define MAXLENGTH_PER_LINE 1000
#define OUTPUT_INCREASE 1000
//#define INCREASE 16

extern int errno;

// from https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
char *inputString(FILE *fp, size_t size)
{
	//The size is extended by the input with the value of the provisional
	char *str;
	int ch;
	size_t len = 0;
	str = realloc(NULL, sizeof(char) * size); //size is start size
	if (!str)
		return str;
	//while (EOF != (ch = fgetc(fp)) && ch != '\n')
	while (EOF != (ch = fgetc(fp))) // only encontering EOF will the reading stop;
	{
		str[len++] = ch;
		if (len == size)
		{
			str = realloc(str, sizeof(char) * (size += 16));
			if (!str)
			{
				perror("Error during reallocation");
				return NULL;
			}
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char) * len);
}


int update_colin(int *rows, int rowssize, int rowcur)
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
	//char* input = inputString(stdin, 100);
	char *output = realloc(NULL, sizeof(char) * OUTPUT_INCREASE);
	char ch;
	//char *line = realloc(NULL, sizeof(char) * MAXLENGTH_PER_LINE); //size is start size;
	size_t outlen = 0, outsize = OUTPUT_INCREASE; //size = MAXLENGTH_PER_LINE,len = 0,
	int colnum = 1, line = 1, colinbefore = 0, colin = 0, doublequotes = 0;
	// initilize
	colin = update_colin(rows, rowssize, colnum);
	while (EOF != (ch = fgetc(stdin)))
	{
		//str[len++] = ch;
		// main algorithm
		switch (ch)
		{
		case '"': // doublequotes processing
			doublequotes = (doublequotes + 1) % 2;
			// add this char
			if (colin && line > igln)
			{
				output[outlen] = sep;
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
			colin = update_colin(rows, rowssize, colnum);
			colinbefore = 0;
			break;
		default:
			if (ch == sep)
			{
				if (doublequotes != 0)
				{
					colnum += 1;
					colinbefore = colin;
					colin = update_colin(rows, rowssize, colnum);
					if (colinbefore && line > igln)
					{
						output[outlen] = sep;
						outlen++;
					}
				}
			}
			else if (line > igln) // skip line
			{
				// find column
				if (colin)
				{
					output[outlen] = sep;
					outlen++;
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
		// extend size of input line
		// if (len == MAXLENGTH_PER_LINE)
		// {
		// 	str = realloc(str, sizeof(char) * (size += INCREASE));
		// 	if (!str)
		// 	{
		// 		perror("Error during reallocation");
		// 		return NULL;
		// 	}
	}
	output[outlen++] = '\0';

	printf("%s\n%lu", output, strlen(output));
}
int main(int argc, char *argv[])
{
	int opt;
	char sep = ' '; // default separator: one space
	int igln = 0;   // the number of lines to ignore (default: 0)

	while ((opt = getopt(argc, argv, "s:i:")) != -1)
	{
		switch (opt)
		{
		case 's':
			sep = optarg[0];
			break;
		case 'i':
			igln = strtod(optarg, NULL);
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-s separator] [-i the number of lines to ignore] row numbers to extract \n",
					argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	printf("sep=%c igln=%d\n", sep, igln);
	
	if (optind >= argc)
	{
		fprintf(stderr, "Expected argument after options\n");
		exit(EXIT_FAILURE);
	}

	printf("name argument = %s, %s\n", argv[optind], argv[optind + 1]);

	int *rows = NULL, size = 0;
	// get rows
	extract(rows, size, sep, igln);

	exit(EXIT_SUCCESS);
}
