#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

int letterOnly(char *string, int length)
{
    int i = 0, j = 0;
    for (i = 0; i < length; i++)
    {
        //printf("%c\n", string[i]);
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[j] = string[i];
            j++;
        }
        else if (string[i] >= 'a' && string[i] <= 'z')
        {
            string[j] = string[i] - 32;
            j++;
        }
    }

    if (j)
    {
        string[++j] = 0;
        return 0;
    }
    else
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int length = strlen(argv[1]);
        char password[length];
        if (!letterOnly(argv[1], length))
        {
            printf("The argument supplied is %s\n", argv[1]);
        }
        else
        {
            printf("Please input password with letters in it!\n");
            return 0;
        }
    }
    else if (argc > 2)
    {
        printf("Too many arguments input.\n");
    }
    else
    {
        printf("One argument for password expected.\n");
    }
    return 0;
}
