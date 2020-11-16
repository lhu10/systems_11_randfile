#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int gen_rand(){
    int fd, buff, result; 
    fd = open("/dev/random", O_RDONLY);
    //checking return value
    if(fd == -1){
        printf("Open Failed\nError: %s\n", strerror(errno));
        return -1; 
    }

    result = read(fd, &buff, sizeof(buff)); 
    //checking return value
    if(result == -1){
        printf("Read Failed\nError: %s\n", strerror(errno));
        return -1; 
    }
    close(fd);
    return buff; 
}

void print_array(int *arr){
    int i; 
    for(i = 0; i < 10; i++){
        printf("\trandom %d: %d\n", i, *(arr+i));
    }
}

int main(){
    int arr[10], copy[10];
    int i, write_fd, read_fd, result; 
    //populates arr with gen_rand();
    for(i = 0; i < 10; i++){
        arr[i] = gen_rand();
    }
    //prints out contents of array
    printf("Generating random numbers:\n");
    print_array(arr);

    printf("Writing numbers to file...\n\n");
    write_fd = open("output.txt", O_WRONLY | O_CREAT, 0666);
    //checking return value
    if(write_fd == -1){
        printf("Open Failed\nError: %s\n", strerror(errno));
        return -1; 
    }

    result = write(write_fd, arr, sizeof(arr));
    //checking return value
    if(result == -1){
        printf("Write Failed\nError: %s\n", strerror(errno));
        return -1; 
    }

    close(write_fd); 

    printf("Reading numbers from file...\n\n"); 
    read_fd = open("output.txt", O_RDONLY);
    result = read(read_fd, copy, sizeof(copy)); 
    //checking return value
    if(result == -1){
        printf("Read Failed\nError: %s\n", strerror(errno));
        return -1; 
    }

    printf("Verification that written values were the same:\n"); 
    print_array(copy);

    close(read_fd);

    return 0; 
}
