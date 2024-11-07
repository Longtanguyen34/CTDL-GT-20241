#include <iostream>
using namespace std;

// Dinh nghia cau truc node
struct Node {
    int data;
    Node* next;
};

// Ham tao mot node moi
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Ham them mot node moi vao vi tri sau vi tri con tro T
void insertAfter(Node* T, int newData) {
    if (T == nullptr) {
        cout << "Loi: Con tro T NULL." << endl;
        return;
    }
    Node* newNode = createNode(newData);
    newNode->next = T->next;
    T->next = newNode;
}

// Ham xoa node tai vi tri con tro T
void deleteNode(Node* T) {
    if (T == nullptr || T->next == nullptr) {
        cout << "Loi: Khong the xoa node nay." << endl;
        return;
    }
    Node* temp = T->next;
    T->data = temp->data;
    T->next = temp->next;
    delete temp;
}

// Ham xoa node duoi cua danh sach
void deleteTail(Node*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Ham in danh sach
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    cout << "Danh sach ban dau: ";
    printList(head);

    // Them node moi sau node thu hai
    insertAfter(head->next, 5);
    cout << "Danh sach sau khi chen 5 sau node thu hai: ";
    printList(head);

    // Xoa node thu hai
    deleteNode(head->next);
    cout << "Danh sach sau khi xoa node thu hai: ";
    printList(head);

    // Xoa node duoi
    deleteTail(head);
    cout << "Danh sach sau khi xoa node duoi: ";
    printList(head);

    return 0;
}
