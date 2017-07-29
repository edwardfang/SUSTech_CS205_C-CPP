#include <stdio.h>

int main(){
    //char vigenereMatrix[26][26]
    char tmp;
    int i = 0, j = 0;
    for(i=0;i<26;i++){
        for(j=0;j<26;j++){
            tmp = 'A' + ((i + j) % 26);
            //vigenereMatrix[i][j] = tmp;
            printf("%c ", tmp);
        }
        printf("\n");
    }
    return 0;
}