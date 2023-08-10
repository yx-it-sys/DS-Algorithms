#include "RedBlackTree.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<int, string> color = { {1, "BLACK"}, {0, "RED"} };

int main() {
    RedBlackTree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    std::cout << "Red-Black Tree: " << std::endl;
    tree.print();

    for (int i = 0; i < 50; i++) {
        std::cout << "-+";
    }
    std::cout << std::endl;

    std::cout << "os_select:\n";
    Node* sec = tree.os_select(3);
    Node* fif = tree.os_select(5);

    auto it1 = color.find(sec->color);
    auto it2 = color.find(fif->color);

    cout << "The third smallest elements is " << sec->data << "(" << it1->second << ")\n";
    cout << "The fifth smallest elements is " << fif->data << "(" << it2->second << ")\n";
    
    for (int i = 0; i < 50; i++) {
        std::cout << "-+";
    }
    std::cout << std::endl;

    std::cout << "Remove: \n";
    tree.remove(11);
    std::cout << "Red-Black Tree: " << std::endl;
    tree.print();

    for (int i = 0; i < 50; i++) {
        std::cout << "-+";
    }
    std::cout << std::endl;

    return 0;
}