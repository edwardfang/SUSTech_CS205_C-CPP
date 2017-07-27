#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAXLENGTH_PER_LINE 1000
#define OUTPUT_INCREASE 1000
#define INCREASE 16

extern int errno ;

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
			if (!str){
				perror("Error during reallocation");
				return NULL;
			}
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char) * len);
}
int update_colin(int* rows, int rowssize, int rowcur){
	for(i=0;i<rowssize;i++){
		if(colnum == rows[i]){
			return 1;
		}
	}
	return 0;
}
void extract(int* rows, int rowssize, char sep, int igln){
	//char* input = inputString(stdin, 100);
	char* output =  realloc(NULL, sizeof(char) * OUTPUT_INCREASE);
	char* line = realloc(NULL, sizeof(char) * MAXLENGTH_PER_LINE); //size is start size;
	size_t len = 0, size = MAXLENGTH_PER_LINE, outlen = 0, outsize = OUTPUT_INCREASE;
	int colnum = 1, line = 1, out_position = 0, colin = 0;
	while(EOF != (ch = fgetc(fp)))
	{
		str[len++] = ch;
		// main algorithm
		switch(ch){
			case '\n':
				line++;
				colnum = 1;
				colin = update_colin(rows, rowssize, colnum);
				break;
			case sep:
				colnum += 1;
				colin = update_colin(rows, rowssize, colnum);
				break;
			default:
				// skip line
				if(line > igln){
					if(colin){
						
					}
				}
		}	
		
		
		if(len == MAXLENGTH_PER_LINE){
			str = realloc(str, sizeof(char) * (size += INCREASE));
			if(!str){
				perror("Error during reallocation");
				return NULL;
			}	
		}
		
	}
	str[len++] = '\0';
	
	//printf("%s\n%d", input, strlen(input));
}
int main(int argc, char *argv[])
{
	int opt;
	char sep = ' '; // default separator: one space
	int igln = 0; // the number of lines to ignore (default: 0)

	while ((opt = getopt(argc, argv, "s:i:")) != -1) {
		switch (opt) {
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

	printf("sep=%c igln=%d\n",sep, igln);

	if (optind >= argc) {
		fprintf(stderr, "Expected argument after options\n");
		exit(EXIT_FAILURE);
	}
	
	printf("name argument = %s, %s\n", argv[optind],argv[optind+1]);

	int *rows = NULL, size = 0;
	// get rows
	extract(rows, size, sep, igln);

	exit(EXIT_SUCCESS);
}
