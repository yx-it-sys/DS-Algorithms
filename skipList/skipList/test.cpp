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
    skipList.insert(8);
    skipList.insert(9);
    skipList.insert(10);
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
    skipList.remove(10);
    skipList.remove(9);
    skipList.remove(8);
    //skipList.remove(7);
    //skipList.remove(6);
    //skipList.remove(5);
    //skipList.remove(4);
    //skipList.remove(3);
    //skipList.remove(2);
    //skipList.remove(1);
    skipList.print();
    delimiter();
    return 0;
}