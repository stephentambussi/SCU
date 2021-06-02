//Buying milk problem - solution try #2
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

struct d {
    bool note;
    bool milk;
};
void *goA(void *);
void *goB(void *);
bool buyMilk (struct d *data);
pthread_t t1, t2;

int main() {
    struct d *data = (struct d *) malloc (sizeof(struct d));
    data -> note = false;
    data -> milk = false;
    pthread_create(&t1, NULL, goA, data);
    pthread_create(&t2, NULL, goB, data);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("The value of note is %d, the value of milk %d\n", data -> note, data -> milk );
    return 0;
}
void *goA(void *arg) {
    struct d *data = arg;   
    printf("The value of note is %d, the value of milk %d\n", data -> note, data -> milk ); 
    data -> note = true;          
    if (!data -> milk){ 
        sleep(10);   
        if (!data -> note){  
            data -> note = true;          
            printf("Thread A is buying milk\n");
            data -> milk = buyMilk(data);
            data -> note = false;
        }
    }                 
                              
   pthread_exit(0);
}
void *goB(void *arg) {
    struct d *data = arg;
    printf("The value of note is %d, the value of milk %d\n", data -> note, data -> milk );
    data -> note = true;     
    if (!data -> milk){  
        if (!data -> note){  
            data -> note = true;          
            printf("Thread B is buying milk\n");
            data -> milk = buyMilk(data);
            data -> note = false;
        }  
    }                           
                              
    pthread_exit(0);
}
bool buyMilk (struct d *data){
    printf("The value of note is %d, the value of milk %d\n", data -> note, data -> milk );
    return true;
}
