#include <stdio.h>

#define BUFFER_SIZE 5

int main()
{
    /*Recuerden que la implementacion
    cambia dependiendo del contexto
    en el cual ustedes trabajen
    y como ustedes definan sus
    funciones...*/
    
    int ring_buffer[] = {0,0,0,0,0};
    int *ptr_read, *ptr_write;
    
    ptr_read  = ring_buffer;
    ptr_write = ring_buffer;
    
void buffer_write(size_t largo_DATA, int DATA[]){
    int i;
    *ptr_write = DATA[0];
    ptr_write++;
    if(ptr_write  > &ring_buffer[BUFFER_SIZE-1]){
        ptr_write = ring_buffer;
    }
    for(i = 1;i<largo_DATA;i++){
        if(ptr_read == ptr_write){
            if(ptr_write == &ring_buffer[BUFFER_SIZE-1]){
                *ptr_write = DATA[i];
                ptr_write = ring_buffer;
                ptr_read  = ptr_write;
            }
            else{
                *ptr_write = DATA[i];
                ptr_write++;
                ptr_read = ptr_write;
            }
        }
        else{
            if(ptr_write == &ring_buffer[BUFFER_SIZE-1]){
                *ptr_write = DATA[i];
                ptr_write = ring_buffer;
            }
            else{
                *ptr_write = DATA[i];
                ptr_write++;
            }
            
        }
    }
}

void buffer_read(){
    if(ptr_read == ptr_write){
        printf("Valor de buffer: %d\n",*ptr_read);
        *ptr_read = 0;
        ptr_read++;
        if(ptr_read - 1 == &ring_buffer[BUFFER_SIZE-1]){
            ptr_read = ring_buffer;
        }
    }
    while(ptr_read != ptr_write){
        printf("Valor de buffer: %d\n",*ptr_read);
        *ptr_read = 0;
        ptr_read++;
        if(ptr_read - 1 == &ring_buffer[BUFFER_SIZE-1]){
            ptr_read = ring_buffer;
        }
    }
    printf("\n\n");
}   
    /*Informacion de entrada:
    Esto podria ser perfectamente comunicacion
    serial TX -> RX o alguna equivalente... */
    int DATA_IN[] = {1,1,2,3};
    buffer_write(4,DATA_IN);
    buffer_read(ring_buffer);

    
    int DATA_IN2[] = {20,50,70};
    buffer_write(3,DATA_IN2);
    buffer_read(ring_buffer);

    int DATA_IN3[] = {15,30,6,7,8,9};
    buffer_write(6,DATA_IN3);
    buffer_read(ring_buffer);
    
    return 0;
    
}

