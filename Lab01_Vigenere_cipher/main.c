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
        string[j] = 0;
        return 0;
    }
    else
    {
        return -1;
    }
}

int messagePreprocess(char *message, int length)
{
    int i = 0, j = 0;
    for (i = 0; i < length; i++)
    {
        //printf("%c", message[i]);
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            message[j] = message[i];
            j++;
        }
        else if (message[i] >= 'a' && message[i] <= 'z')
        {
            message[j] = message[i] - 32;
            j++;
        }
        else if (message[i] == 32)
        {
            message[j] = 32;
            j++;
        }
    }
    message[j] = 0;
    return 0;
}

int messageEncrypt(char *message, int messageLength, char *key, int keyLength)
{
    // i stands for the position of the char, iM stands for the index of the letter in the message
    int i = 0, iM = 0, iK = 0, charM, charK;
    for (i = 0; i < messageLength; i++)
    {
        // shift 65~90 to 0~25 65*2=130
        if (message[i] != 32)
        {
            iK = iM % keyLength;
            message[i] = (message[i] + key[iK] - 130) % 26 + 65;
            iM ++;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // process the password
        // strlen https://stackoverflow.com/questions/22084848/c-programming-functionality-of-strlen
        char *key = argv[1];
        int length = strlen(key);
        if (letterOnly(key, length))
        {
            printf("Please input password with letters in it!\n");
            return 0;
        }
        // get the text to encode
        char *message;
        message = inputString(stdin, 10);
        // encrypt
        int messageLength = strlen(message);
        messagePreprocess(message, messageLength);
        messageLength = strlen(message);
        messageEncrypt(message, messageLength, key, length);
        fputs(message, stdout);
        fputs("\n", stdout);
        //printf("%s\n", message);
        free(message);
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
