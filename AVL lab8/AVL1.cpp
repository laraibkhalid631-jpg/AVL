#include <iostream>
#include <algorithm>
using namespace std;

// Structure defining an AVL Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
    int height; // Every node stores its own height for balance checks

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1; // New nodes are initially added at leaf level (height 1)
    }
};

class AVLTree {
public:
    // Helper function to safely get the height of a node (handles NULL pointers)
    int getHeight(Node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    // Helper function to calculate the Balance Factor of a node
    int getBalanceFactor(Node* n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    // 1. RIGHT ROTATION (Used to fix Left-Left heavy imbalances)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation steps
        x->right = y;
        y->left = T2;

        // Update heights (order matters: child 'y' first, then parent 'x')
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // Return the new root structure pointer
        return x;
    }

    // 2. LEFT ROTATION (Used to fix Right-Right heavy imbalances)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation steps
        y->left = x;
        x->right = T2;

        // Update heights (order matters: child 'x' first, then parent 'y')
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        // Return the new root structure pointer
        return y;
    }

    // Function to insert a node and apply automatic rotations based on conditions
    Node* insert(Node* node, int key) {
        // Step 1: Perform normal BST insertion
        if (node == nullptr) return new Node(key);

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node; // Duplicate keys are not allowed in basic AVL
        }

        // Step 2: Update height of the current ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Step 3: Get balance factor to check if it became unbalanced
        int balance = getBalanceFactor(node);

        // CASE 1: Left-Left (LL) Imbalance -> Requires Single Right Rotation
        if (balance > 1 && key < node->left->data) {
            cout << "Applying Right Rotation on node " << node->data << endl;
            return rightRotate(node);
        }

        // CASE 2: Right-Right (RR) Imbalance -> Requires Single Left Rotation
        if (balance < -1 && key > node->right->data) {
            cout << "Applying Left Rotation on node " << node->data << endl;
            return leftRotate(node);
        }

        // CASE 3: Left-Right (LR) Imbalance -> Requires Left-Right Rotation
        if (balance > 1 && key > node->left->data) {
            cout << "Applying Left-Right Rotation around node " << node->data << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // CASE 4: Right-Left (RL) Imbalance -> Requires Right-Left Rotation
        if (balance < -1 && key < node->right->data) {
            cout << "Applying Right-Left Rotation around node " << node->data << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the unchanged pointer if balanced
    }

    // In-order traversal output validation utility
    void inOrder(Node* root) {
        if (root == nullptr) return;
        inOrder(root->left);
        cout << root->data << " (H:" << root->height << ") ";
        inOrder(root->right);
    }
};

int main() {
    AVLTree avl;
    Node* root = nullptr;

    cout << "--- Building AVL Tree and testing rotations ---\n";
    
    // Testing LL Case (Triggers Single Right Rotation)
    cout << "Inserting 30, 20, 10:\n";
    root = avl.insert(root, 30);
    root = avl.insert(root, 20);
    root = avl.insert(root, 10); 
    
    // Testing RR Case (Triggers Single Left Rotation)
    cout << "\nInserting 40, 50:\n";
    root = avl.insert(root, 40);
    root = avl.insert(root, 50); 
    
    // Testing RL Case (Triggers Double Right-Left Rotation)
    cout << "\nInserting 45:\n";
    root = avl.insert(root, 45); 

    cout << "\nFinal Balanced AVL Tree Structure (In-Order with Heights):\n";
    avl.inOrder(root);
    cout << endl;

    return 0;
}

