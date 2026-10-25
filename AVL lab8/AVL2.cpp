#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Node structure specifically for creating our own pointer tracking Queue
struct QueueNode {
    Node* treeNode;
    QueueNode* next;
    QueueNode(Node* n) {
        treeNode = n;
        next = nullptr;
    }
};

class AVLTreeLevelOrder {
public:
    // Basic height utility helper
    int getHeight(Node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    // Basic balancing evaluation utility helper
    int getBalanceFactor(Node* n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);
        else return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->data) return rightRotate(node);
        if (balance < -1 && key > node->right->data) return leftRotate(node);
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // CORE FUNCTION: Level Order Traversal implementation
    void levelOrder(Node* root) {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        // Initialize simple Queue system trackers
        QueueNode* front = nullptr;
        QueueNode* rear = nullptr;

        // Enqueue the root node path to start
        front = rear = new QueueNode(root);

        cout << "Level-Order Traversal sequence: ";

        while (front != nullptr) {
            // Extract front item from queue boundary
            Node* current = front->treeNode;
            cout << current->data << " ";

            // If a left child exists, insert it into the tracking queue
            if (current->left != nullptr) {
                rear->next = new QueueNode(current->left);
                rear = rear->next;
            }

            // If a right child exists, insert it into the tracking queue
            if (current->right != nullptr) {
                rear->next = new QueueNode(current->right);
                rear = rear->next;
            }

            // Advance front node item forward to pop item out of scope safely
            QueueNode* temp = front;
            front = front->next;
            delete temp; 
        }
        cout << endl;
    }
};

int main() {
    AVLTreeLevelOrder avl;
    Node* root = nullptr;

    // Building balanced baseline setup layout 
    // Inserting numbers to produce an balanced layout structure automatically
    root = avl.insert(root, 40);
    root = avl.insert(root, 20);
    root = avl.insert(root, 60);
    root = avl.insert(root, 10);
    root = avl.insert(root, 30);
    root = avl.insert(root, 50);
    root = avl.insert(root, 70);

    // Run Traversal Layout printout check
    avl.levelOrder(root); 
    // Expected output order: 40 20 60 10 30 50 70

    return 0;
}

