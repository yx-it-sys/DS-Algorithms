#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> color = { "RED", "BLACK" };

void RedBlackTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node = node->parent->left) {
        node->parent->left = rightChild;
    }
    else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;

}

void RedBlackTree::rotateRight(Node* node)
{
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node->parent->left == leftChild) {
        node->parent->left = leftChild;
    }
    else {
        node->parent->right = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::fix(Node* node)
{
    while (node != root && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;

                node = node->parent->parent;
            }
        }
        else {
            Node* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;

                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

int RedBlackTree::rank(Node* x)
{
    if (x == nullptr) {
        return 0;
    }
    else {
        return rank(x->left) + rank(x->right) + 1;
    }
}

void RedBlackTree::transplant(Node* u, Node* v)
{
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

Node* RedBlackTree::searchNode(int val, Node* node)
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (val > node->data) {
        searchNode(val, node->right);
    }
    else if (val < node->data) {
        searchNode(val, node->left);
    }
    else {
        return node;
    }
}

void RedBlackTree::insert(int val)
{
    Node* newNode = new Node(val);
    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (val < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    newNode->parent = parent;

    if (parent == nullptr) {
        root = newNode;
    }
    else if (val < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    fix(newNode);
}

void InOrderPrintTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    InOrderPrintTree(node->left);
    std::cout << node->data << "(" << color[node->color] << ")" << " ";
    InOrderPrintTree(node->right);
}

void PreOrderPrintTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->data << "(" << color[node->color] << ")" << " ";
    PreOrderPrintTree(node->left);
    PreOrderPrintTree(node->right);
}

void RedBlackTree::print() {
    std::cout << "先序遍历序列：" << std::endl;
    PreOrderPrintTree(root);
    std::cout << std::endl << "中序遍历序列： " << std::endl;
    InOrderPrintTree(root);
    std::cout << std::endl;
}

Node* RedBlackTree::os_select(Node* x, int i)
{
    int k = rank(x->left) + 1;
    if (i == k) {
        return x;
    }
    else if (i < k) {
        return os_select(x->left, i);
    }
    else
        return os_select(x->right, i - k);
}

Node* RedBlackTree::os_select(int i)
{
    return os_select(root, i);
}

void RedBlackTree::remove(int val)
{
    Node* node = searchNode(val, root);
    Node* y = node;
    Node* x = nullptr;
    Color yOriginalColor = y->color;
    
    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    }
    else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    }
    else {
        y = os_select(node->right, 1); // find minimum
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != nullptr) {
                x->parent = y;
            }
        }
        else {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
    delete node;
}
void RedBlackTree::deleteFixup(Node* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left != nullptr) {
                        w->left->color = BLACK;
                    }
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr) {
                    w->right->color = BLACK;
                }
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right != nullptr) {
                        w->right->color = BLACK;
                    }
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr) {
                    w->left->color = BLACK;
                }
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}
