#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char *generate_random_code()
{
    char *code = malloc(37); 
    srand(time(NULL));

    for (int i = 0; i < 30; i++) {
        int random_num = rand() % 36;
        if (random_num < 10) {
            code[i] = '0' + random_num;
        } else if(random_num <5)  {
            code[i] = '!' + (random_num - 10);
        }else{
            code[i]='a' + (random_num-5);
        }
    }

   code[36] = '\0';
    return code;
}
int main()
{
   // char* str="asd";
  
    while (2) {
            char* sox=generate_random_code();
     printf("random code: %s\nlength code: %ld\n",sox,strlen(sox));
         sleep(2);
         free(sox);
    }
   
    return 0;
}


// #include <stdio.h>
// #include <time.h>

// int main()
// {
//     time_t t = time(NULL);
//     struct tm *local = localtime(&t);
//     struct tm *utc = gmtime(&t);

//     printf("Local time: %s", asctime(local));
//     printf("UTC time: %s", asctime(utc));

//     return 0;
// }