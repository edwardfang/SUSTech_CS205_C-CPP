#include <stdio.h>
#include <string.h>

int main()
{
    // Problem with the input buffer https://stackoverflow.com/questions/24099976/read-two-characters-consecutively-using-scanf-in-c
    char name[100], c = 0;
    int id, i = 0;
    printf("Please enter your name:");
    c = getchar();
    while(c!='\n'){
        name[i++] = c;
        c = getchar();
        if(i==98){
            break;
        }
    };
    name[i] = 0;
    //scanf(" %s", name);
    //fgets(name, 100, stdin);
    //newline = strchr(name,'\n');
    //newline = 0;
    
    //problem shooting https://stackoverflow.com/questions/13049893/working-of-scanf-and-checking-if-input-is-int
    while(1){
        printf("Please enter your student id: ");
        if(scanf("%d", &id)>0){
            break;
        }
        getchar();
    }
    
    
    printf("Welcome %s - %d to the C and C++ world\n", name, id);
    return 0;
}

