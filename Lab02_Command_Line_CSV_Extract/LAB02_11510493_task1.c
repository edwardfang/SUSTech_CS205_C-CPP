#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define OUTPUT_INCREASE 1000

extern int errno;

int is_colin(int *rows, int rowssize, int rowcur)
{
	int i;
	for (i = 0; i < rowssize; i++)
	{
		if (rowcur == rows[i])
		{
			// printf("in\n");
			return 1;
		}
	}
	return 0;
}

int extract(int *rows, int rowssize, char sep, int igln)
{
	char *output = (char *)malloc(sizeof(char) * OUTPUT_INCREASE);
	char ch;
	size_t outlen = 0, outsize = OUTPUT_INCREASE;
	int colnum = 1, line = 1, colinbefore = 0, colin = 0, doublequotes = 0, hasinfo = 0;
	colin = is_colin(rows, rowssize, colnum);
	while (EOF != (ch = fgetc(stdin)))
	{
		//printf("DEBUG1");
		// main algorithm
		switch (ch)
		{
		case '"': // doublequotes processing
			// printf("DEBUG2");
			doublequotes = (doublequotes + 1) % 2;
			// add this char
			if (colin && line > igln)
			{
				output[outlen++] = '"';
			}
			break;
		case '\n':
			// printf("DEBUG3\n");
			// add '\n' at the previous position to replace the sep
			if (line > igln && hasinfo == 1)
			{
				output[outlen - 1] = '\n';
			}
			line++;
			hasinfo = 0;
			colnum = 1;
			colin = is_colin(rows, rowssize, colnum);
			colinbefore = 0;
			break;
		default:
			if (colin)
			{
				hasinfo = 1;
			}
			// printf("DEBUG4");
			if (ch == sep)
			{
				// printf("DEBUG5");
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
					// printf("DEBUG6");
					if (colin)
					{
						output[outlen++] = sep;
					}
				}
			}
			else if (line > igln) // skip line
			{
				// find column
				// printf("DEBUG7");
				if (colin)
				{
					output[outlen++] = ch;
				}
			}
		}
		// extend size of output
		//printf("%u, %u, %u\n", outlen, outsize, strlen(output));
		if (outlen == outsize)
		{
			//printf("%s", output);
			output = realloc(output, sizeof(char) * (outsize += OUTPUT_INCREASE));
			if (!output)
			{
				perror("Error during reallocation");
				return -1;
			}
		}
	}
	output[outlen] = '\0';

	printf("%s", output);
	if (outlen > 0)
	{
		fflush(stdout);
		fflush(stdin);
		free(output);
	}
	return 0;
}

int check_rows(int *rows, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		// check repeatation and increasing
		for (j = 0; j < i; j++)
		{
			if (rows[i] <= rows[j])
			{
				return -1;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char *usage = "Usage: %s [-s separator] [-i igln] row0 row1 ... \n"
	"where\n"
	"\tseparator is the character to separate different columns.\n"
	"\tigln is the number of lines to ignore from the beginning.\n"
	"\trow0 row1 ... is column numbers to extract.\n";
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
			fprintf(stderr, usage,	argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	// check the order of options
	if (optind < lastoptind)
	{
		fprintf(stderr, "Expected argument after options, no argument before options!\n");
		fprintf(stderr, usage,	argv[0]);
		exit(EXIT_FAILURE);
	}

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
		if (strtol(argv[iarg], NULL, 10) > 0)
		{
			//printf("%d|%d\n",i, (int)strtol(argv[iarg], NULL, 10));
			rows[i++] = (int)strtol(argv[iarg], NULL, 10);
		}
		else
		{
			break;
		}
	}

	// check the validation of the rows
	if (check_rows(rows, size))
	{
		fprintf(stderr, "1. Field numbers should always be provided in increasing sequence\n\
2. You cannot repeat a field\n");
		exit(EXIT_FAILURE);
	}
	extract(rows, size, sep, igln);
	// printf("sep=%c igln=%d\n", sep, igln);
	// printf("name argument = %s, %s\n", argv[optind], argv[optind + 1]);
	fflush(stdin);
	fflush(stdout);
	free(rows);
	exit(EXIT_SUCCESS);
}
