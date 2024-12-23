#include <iostream>

void *p;

template <typename T, size_t n> void *mlloc(){
    return p;
}

int main() {

    std::cout << mlloc<int,3> << std::endl;

    return 0;
}