#include <stdio.h>

const int BUFFER_SIZE = 5;

int main(){
    int buffer[] = {0,0,0,0,0};
    int *ptr_end;
    ptr_end = buffer;

void read_buffer(){
    int i;
    for(i = 0;i<BUFFER_SIZE;i++){
        printf("En la pos %d el valor de buffer: %d \n",i+1,buffer[i]);
        buffer[i] = 0;
    }
    ptr_end = &buffer;
    printf("\n\n");
}

void buffer_in(size_t largo_DATA, int DATA[]){
    int i;
    for(i = 0;i<largo_DATA;i++){
        if(ptr_end-1 == &buffer[4]){
            printf("El buffer se ha llenado\n");
            break;
            }
        else{
            *ptr_end = DATA[i];
            ptr_end++;
            }
        }
}

    int DATA_IN[] = {1,1,2,3};
    buffer_in(4,DATA_IN);
    read_buffer(buffer);
    
    int DATA_IN2[] = {20,50,70};
    buffer_in(3,DATA_IN2);
    read_buffer(buffer);
    
    int DATA_IN3[] = {15,30,45,12,67,87};
    buffer_in(6,DATA_IN3);
    read_buffer(buffer);
    
    
    return 0;
    
}
