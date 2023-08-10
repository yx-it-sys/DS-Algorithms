enum Color { RED, BLACK };
struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fix(Node* node);
    void deleteFixup(Node* x);
    int rank(Node* x);
    void transplant(Node* u, Node* v);
    static Node* searchNode(int val, Node* node);
public:
    RedBlackTree() : root(nullptr) {}
    void insert(int val);
    void print();
    Node* os_select(Node* x, int i);
    Node* os_select(int i);
    void remove(int val);
};

