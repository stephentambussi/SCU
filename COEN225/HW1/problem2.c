/*  
*   Stephen Tambussi
*   COEN225
*   HW1: problem 2
*   10/4/22
*/
#include <stdio.h>
#include <string.h>
char password[16]; //addr = 0x804a02c = 134,520,876
char passcode[16]; //addr = 0x804a04c = 134,520,908
char input1[16]; //addr = 0x804a03c = 134,520,892
char input2[16]; //addr = 0x804a05c = 134,520,924
int main()
{
    strcpy(password,"california");
    strcpy(passcode,"0123443210");
    printf("enter password:");
    scanf("%s",input1); 

    if (strcmp(input1,password)==0) {
        printf("you guessed right!\n");
        return 0;
    }
        
    printf("Password incorrect, enter backup passcode:");
    scanf("%s",input2);
    if (strcmp(input2,passcode)==0)
        printf("you guessed right!\n");
    else
        printf("you guessed wrong!\n");
}
/*  Solution:
*   Based upon the above memory addresses, I can overwrite the
*   value of passcode by overflowing the buffer for input1 with > 16 characters. By overwriting
*   the value of passcode with something I know, then I can simply provide
*   that value to input2 and the program will output "you guessed right!"
*   
*   Input:
*   0123456789abcdefpassword
*   password
*/