#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t first_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t second_mutex = PTHREAD_MUTEX_INITIALIZER;

int MY_VAR = 0;

void *draw_2(void *my_char) {

    pthread_mutex_lock(&second_mutex);
    MY_VAR = 34;
    printf("ma var : %d\n", &MY_VAR);
    pthread_mutex_lock(&first_mutex);

}

void *draw(void *my_char) {

    pthread_mutex_lock(&first_mutex);

    char* cvar = (char*) my_char;

    MY_VAR = 14;

    pthread_mutex_lock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    for(int i = 0; i < 30; i++) {

        write(2, cvar, 1* sizeof(char));
    }

    return 0;
}

int main(int argc, char** argv) {
    char c1 = '*', c2 = '$';

    pthread_t first_thread, second_thread;

    pthread_create(&first_thread, NULL, draw, (void*) &c1);
    pthread_create(&second_thread, NULL, draw, (void*) &c2);



    return 0;
}