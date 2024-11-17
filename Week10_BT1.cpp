#include <iostream>
#include <string>

struct Node {
    std::string data;
    Node* next;
};

class DanhSachLienKet {
private:
    Node* head;

public:
    DanhSachLienKet() : head(nullptr) {}

    // Them mot phan tu vao cuoi danh sach
    void themVaoCuoi(const std::string& value) {
        Node* newNode = new Node{value, nullptr};
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Xoa phan tu o dau danh sach
    void xoaDau() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Xoa phan tu o cuoi danh sach
    void xoaCuoi() {
        if (!head) return;
        if (!head->next) {  //Neu danh sach chi co 1 node duy nhat
            delete head;
            head = nullptr;
            return;
        }
        Node* current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    // Xoa phan tu sau mot node duoc chi dinh
    void xoaSau(const std::string& value) {
        Node* current = head;
        while (current && current->data != value) {
            current = current->next;
        }
        if (current && current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Hien thi danh sach
    void hienThi() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~DanhSachLienKet() {
        while (head) {
            xoaDau();
        }
    }
};

int main() {
    DanhSachLienKet list;
    list.themVaoCuoi("Long");
    list.themVaoCuoi("Nam");
    list.themVaoCuoi("Dat");
    list.themVaoCuoi("Huy");
    list.themVaoCuoi("Hanh");
    list.themVaoCuoi("Hiep");
    list.themVaoCuoi("Khanh");
    list.themVaoCuoi("Son");
    list.themVaoCuoi("Duc");

    std::cout << "Danh sach ban dau: ";
    list.hienThi();

    list.xoaDau();
    std::cout << "Sau khi xoa node dau: ";
    list.hienThi();

    list.xoaCuoi();
    std::cout << "Sau khi xoa node cuoi: ";
    list.hienThi();

    list.xoaSau("Hanh");
    std::cout << "Sau khi xoa node dung sau node Hanh cho truoc: ";
    list.hienThi();

    return 0;
}
