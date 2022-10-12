/*  
*   Stephen Tambussi
*   COEN225
*   HW2: problem 1
*   10/18/22
*/
//Need to compile with -fno-stack-protector, -z execstack (allows stack to run program)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int IsPasswordOK(void) 
{ 
  char Password [256];
  printf("Password at %p\n",&Password[0]);
  (void) gets(Password);
  return 0 == strcmp (Password, "goodpass"); 
}
int main (void) 
{
  int PwStatus;
  puts("Enter Password: "); 
  PwStatus=IsPasswordOK( );
  if (!PwStatus) {
    puts("Access denied");
    exit(-1);
  }
  else
    puts("Access granted"); //0x0804856a --> return address
}