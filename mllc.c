/*
    @author: yash
    @file: mllc.c
*/
#include <unistd.h> // for sbrk
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/*
    A dum malloc written from scratch for fun
    malloc => memory allocation
    a standard c lib func that dynamically allocates 
    memory at runtime


    1.The Head and Dynamic memory
        memory is divided to stack and heap and code segment.
        the heap is the large, flexible memory that is reserved for 
        dynamic memory allocation 
        when a program starts, the operating system initialize the 
        heap with a large block of memory. malloc manages this memory.

    2.how malloc works
        -> initialization
            the heap is initialized as one large free mem block
            the metadeta is stored at the begining of each block
        -> handling request
            when malloc is called with a size(n)
            it looks for a free block large enough to satisfy the request
            if no block is large enough
            the heap may request more memory from the operating system
            using [sbrk] or [mmap]. these system call grows the heap size
        -> splitting blocks
            if a block is larger than requested, it is split into two
        -> returning pointer
            the memory block is marked as allocated in the metadata
            a pointer to the usable portion is returned to the user.
        -> freeing memory
            when a block is freed, its metadata is updated to mark it as free.
            {adjacent free blocks are merged often to reduce fragmentation} 

    3.system call and mem management
        -> sbrk
            the system call sbrk(n) increases the program data by n bytes.

*/

typedef struct chunk{
    size_t size;            // block size
    int free;               // 0 or 1 for block free or not
    struct chunk *nxt;
} chunk;

#define chunk_size sizeof(chunk);

void *chunk_strt = NULL; // the start!!!!!

chunk *find_free_chunk(chunk **last, size_t size){

    chunk *current = chunk_strt;
    while(current && (current->free && current->size >= size)){
        *last = current;
        current = current->nxt;
    }

    return current;
}

chunk *req_space(chunk *last, size_t size){
    chunk* t;
    t = sbrk(0);
    void *request = sbrk(size + sizeof(chunk));
    if(request == (void *)-1){
        return NULL;
    }
    if(last){
        last->nxt = t;
    }
    t->size = size;
    t->free = 0;
    t->nxt = NULL;
    
    return t;
}

void *dum_malloc(size_t size){
    chunk *i;

    if(size <= 0){
        return NULL;
    }
    if(!chunk_strt){
        i = req_space(NULL, size);
        if(!i){
            return NULL;
        }
        chunk_strt = i;
    }else{
        chunk *last = chunk_strt;
        i  = find_free_chunk(&last, size);
        if(!i){
            i = req_space(last, size);
            if(!i){
                return NULL;
            }
        }else{
            i->free = 0;
        }
    }

    return (i+1);
}

void dum_free(void *ptr){
    if(!ptr){
        return;
    }
    chunk *i = (chunk *)ptr -1;
    i->free =1;
 
    char *data = (char *)ptr;
    for(size_t j = 0; j <i->size; i++){
        data[j]= 0;
    }

}

int main(){

    int *arr = dum_malloc(10 * sizeof(int));
    if(arr){
        for (int i = 0; i < 10; i++){
            arr[i] = i*2;
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    dum_free(arr);


    for(int i = 0; i<10; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    return 0;
}