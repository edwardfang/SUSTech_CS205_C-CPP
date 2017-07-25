#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int cipherPreprocess(char *cipher, int length)
{
    int i = 0, j = 0;
    for (i = 0; i < length; i++)
    {
        //printf("%c", cipher[i]);
        if (cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            cipher[j] = cipher[i];
            j++;
        }
        else if (cipher[i] >= 'a' && cipher[i] <= 'z')
        {
            cipher[j] = cipher[i] - 32;
            j++;
        }
        else if (isspace(cipher[i]))
        {
            cipher[j] = cipher[i];
            j++;
        }
    }
    cipher[j] = 0;
    return 0;
}

int cipherDecrypt(char *cipher, int cipherLength, char *key, int keyLength)
{
    // i stands for the position of the char, iM stands for the index of the letter in the cipher
    int i = 0, iM = 0, iK = 0;
    for (i = 0; i < cipherLength; i++)
    {
        // shift 65~90 to 0~25 65*2=130
        if (isalpha(cipher[i]))
        {
            iK = iM % keyLength;
            // plus 26 to make the modulus result positive
            cipher[i] = (cipher[i] + 26 - key[iK]) % 26 + 65;
            //printf("%d", cipher[i]);
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
        char *cipher;
        cipher = inputString(stdin, 10);
        // encrypt
        int cipherLength = strlen(cipher);
        cipherPreprocess(cipher, cipherLength);
        cipherLength = strlen(cipher);
        cipherDecrypt(cipher, cipherLength, key, length);
        fputs(cipher, stdout);
        //fputs("\n", stdout);
        //printf("%s\n", cipher);
        free(cipher);
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
