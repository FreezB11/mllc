/*
    @file: mllc.c
    @author: yash
*/
#include <stdio.h>

#define alignment 8 // must be pwr(2)
#define align(size) (((size) + (alignment-1)) & ~(alignment-1))
#define t_size (align(sizeof(size_t)))

#ifdef NMALLOC
//  naive_allocator
void *nmalloc(size_t size){
    size_t block_size = align(size + t_size);
    size_t *header = sbrk(block_size);

    *header = block_size | 1; // marking as allocated bit
    return (char *)header + t_size;
}

void free(void *ptr){
    size_t *header = (char *) ptr - t_size;
    *header = *header & ~1L; // unmarking
}
#endif



int main(){

    for (int i = 1; i <+ 32; i+=1){
        /* code */
        printf("align(%d) = %d\n", i, align(i));
    }
    return 0;
}