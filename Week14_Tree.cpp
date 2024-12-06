#include <iostream>
#include <string>

using namespace std;

// Cau truc nut trong cay bieu thuc
struct TreeNode {
    string value;   // Gia tri cua nut (toan tu hoac toan hang)
    TreeNode* left; // Con trai
    TreeNode* right;// Con phai

    // Constructor khoi tao nut
    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Kiem tra mot chuoi co phai toan tu hay khong
bool isOperator(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

// Xay dung cay bieu thuc tu bieu thuc hau to
TreeNode* buildExpressionTree(string postfix[], int n) {
    TreeNode* nodes[100]; // Mang luu cac nut cua cay
    int index = 0;        // Chi so cua mang

    for (int i = 0; i < n; ++i) {
        string token = postfix[i];

        // Neu la toan tu, tao nut voi 2 con
        if (isOperator(token)) {
            TreeNode* newNode = new TreeNode(token);
            newNode->right = nodes[--index]; // Lay nut ben phai
            newNode->left = nodes[--index];  // Lay nut ben trai
            nodes[index++] = newNode;        // Day nut moi vao mang
        } else {
            // Neu la toan hang, tao nut moi va luu vao mang
            nodes[index++] = new TreeNode(token);
        }
    }

    // Nut cuoi cung la goc cua cay bieu thuc
    return nodes[0];
}

// Duyet cay theo thu tu giua de in bieu thuc trung to
void printInfix(TreeNode* root) {
    if (!root) return;
    printInfix(root->left);      
    cout << root->value;         
    printInfix(root->right);     
}

int main() {
    string postfix[] = {"a", "5", "b", "*", "6", "/", "+", "c", "8", "^", "-", "d", "e", "0.5", "^", "*", "+"};
    int n = sizeof(postfix) / sizeof(postfix[0]);

    TreeNode* expressionTree = buildExpressionTree(postfix, n);

    cout << "Bieu thuc trung to la: ";
    printInfix(expressionTree);
    cout << endl;

    return 0;
}