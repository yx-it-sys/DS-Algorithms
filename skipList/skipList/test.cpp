#include "SkipList.h"
#include <iostream>

void delimiter() {
    for (int i = 0; i < 50; i++) {
        printf("+-");
    }
    printf("\n");
}

int main() {
    SkipList skipList;
    delimiter();
    skipList.insert(1);
    skipList.insert(2);
    skipList.insert(3);
    skipList.insert(4);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(10);
    skipList.insert(11);
    skipList.insert(9);
    skipList.insert(100);
    skipList.insert(18);
    skipList.insert(12);
    skipList.insert(13);
    skipList.insert(14);
    skipList.print();
    delimiter();
    printf("Search(x): \n");
    SkipListNode* p = skipList.search(54);
    if (p == nullptr) {
        printf("Not Found!\n");
    }
    else {
        std::cout << std::endl << p->data << std::endl;
    }
    delimiter();
    return 0;
}