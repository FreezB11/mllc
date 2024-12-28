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
size_t heap_size = 1024*1024;
size_t heap_alloc_size = 0;

typedef struct chunk{
    size_t size;
    bool is_free;
    // struct chunk *nxt;
    void* start_addr;
} chunk;

chunk chunks[(1024*1024)/sizeof(chunk)] = {0};
size_t chunks_size = 0;

 
#define log(c) std::cout << c << std::endl;

// first iteration for heap alloc
// void * heap_alloc(size_t ssize){
//     if(ssize <= 0 || ssize > (1024*1024)){
//         return NULL;
//     }
//     void *result = heap + heap_size;
//     heap_size += ssize;

//     // chunks[chunks_size++] ;
//     chunk curr = {ssize,false,result};
//     chunks[chunks_size++] = curr;

//     return result;
// }

//heap_alloc v2
void *heap_alloc(size_t size){
    if(size == 0 || size > heap_size){
        return NULL;
    }
    for (size_t i = 0; i < chunks_size; i++){
        if (chunks[i].is_free && chunks[i].size >= size){
            chunks[i].is_free = false;
            return chunks[i].start_addr;
        }
    }
    if(chunks_size == 0){
        chunks[chunks_size].start_addr = heap;
    }else{
        chunks[chunks_size].start_addr = (void *)((unsigned char*)chunks[chunks_size-1].start_addr + chunks[chunks_size-1].size);
    }

    if((char*)chunks[chunks_size].start_addr + size > heap + heap_size){
        log("memory allocation failed: not enough space\n");
        return NULL;
    }

    chunks[chunks_size].size = size;
    chunks[chunks_size].is_free = false;

    log("allocated " << size << " bytes at address " << chunks[chunks_size].start_addr)
    chunks_size++;
    heap_alloc_size += size;
    return chunks[chunks_size-1].start_addr;    
}

void heap_free(void *ptr){
    if(ptr == NULL || ptr < (void *)heap || ptr >= (void*)(heap+heap_size)){
        log("ERR: Invalid pointer\n")
    }
    for (size_t i = 0; i < chunks_size; i++){
        /* code */
        if(chunks[i].start_addr == ptr){
            //set
            chunks[i].is_free = true;
            heap_alloc_size -= chunks[i].size;
            log("Freed chunk of size " << chunks[i].size << " at address " << ptr)
            
            return;

        }
    }
    log("Pointer not found in alloced chunks\n")
}

void heap_status(){

}

int main() {
    
    void *test = heap_alloc(26);
    // void *test2 = heap_alloc(10);
    // log(test)
    // heap_free(test);

    void *test2 = heap_alloc(10);
    
    // heap_free(test);
    // heap_free(test2);
    // void *test3 = heap_alloc(30);
    // heap_free(test2);
    // void *test4 = heap_alloc(10);
    // log(test2)
    // log(test3)
    // log(test4)
    return 0;
}