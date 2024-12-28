#include <iostream>
/*
    this is done for betterment and 
    for proper memory alignment 
    faster access to the data and also 
    keeps the system safe 

#define alignment 8
#define align(size) (((size) + (alignment-1)) & ~(alignment-1))
*/
char heap[1024*1024] ={0};
size_t heap_size = 0;

typedef struct chunk{
    size_t size;
    bool is_free;
    // struct chunk *nxt;
    void* start_addr;
} chunk;

chunk chunks[(1024*1024)/sizeof(chunk)] = {0};
size_t chunks_size = 0;

 
#define log(c) std::cout << c << std::endl;

void * heap_alloc(size_t ssize){
    if(ssize <= 0 || ssize > (1024*1024)){
        return NULL;
    }
    void *result = heap + heap_size;
    heap_size += ssize;

    // chunks[chunks_size++] ;
    chunk curr = {ssize,false,result};
    chunks[chunks_size++] = curr;

    return result;
}

void heap_free(void *ptr){
    if(ptr == NULL){
        log("ERR: Invalid pointer\n")
    }
    for (size_t i = 0; i < chunks_size; i++){
        /* code */
        if(chunks[i].start_addr == ptr){
            //set
            chunks[i].is_free = true;
            heap_size -= chunks[i].size;
            return;

        }
    }
    log("Pointer not found in alloced chunks\n")
}

int main() {
    
    void *test = heap_alloc(26);
    // void *test2 = heap_alloc(10);
    log(test)
    // heap_free(test);

    void *test2 = heap_alloc(10);
    
    // heap_free(test);
    // heap_free(test2);
    void *test3 = heap_alloc(30);
    heap_free(test2);
    void *test4 = heap_alloc(10);
    log(test2)
    log(test3)
    log(test4)
    return 0;
}