#include <iostream>
#include <algorithm>

using namespace std;

// Cau truc Node cho cay AVL
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Ham lay chieu cao cua mot nut
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Ham tinh he so can bang cua mot nut
int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Ham cap nhat chieu cao cua mot nut
void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Xoay phai
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Xoay trai
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Ham can bang cay
Node* balance(Node* node) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Cay lech trai
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Cay lech phai
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Ham chen mot khoa moi vao cay AVL
Node* insert(Node* root, int key) {
    if (!root) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    return balance(root);
}

// Ham duyet cay theo thu tu giua
void inOrderTraversal(Node* root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

// Ham duyet cay theo thu tu truoc
void preOrderTraversal(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Ham chinh
int main() {
    int keys[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int n = sizeof(keys) / sizeof(keys[0]);
    Node* root = nullptr;

    cout << "Xay dung cay AVL theo tung buoc:\n\n";
    for (int i = 0; i < n; ++i) {
        int key = keys[i];
        root = insert(root, key);
        cout << "Duyet giua sau khi chen " << key << ": ";
        inOrderTraversal(root);
        cout << "\nDuyet truoc sau khi chen " << key << ": ";
        preOrderTraversal(root);
        cout << "\n\n";
    }

    cout << "Cay AVL cuoi cung (Duyet giua): ";
    inOrderTraversal(root);
    cout << "\n";

    cout << "Cay AVL cuoi cung (Duyet truoc): ";
    preOrderTraversal(root);
    cout << "\n";

    return 0;
}
