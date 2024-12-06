#include <iostream>
#include <cstring>

#define MAX_NAME_LENGTH 100

// Cau truc luu thong tin mot san pham
struct Product {
    char name[MAX_NAME_LENGTH];
    double price;
    int quantity;

    // Tinh tong tien san pham
    double calculateTotal() const {
        return price * quantity;
    }
};

// Cau truc node trong hang doi
struct Node {
    Product product;
    Node* next;

    Node(const Product& product) : product(product), next(nullptr) {}
};

// Cau truc hang doi
struct Queue {
    Node* front;
    Node* rear;
    int size;

    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Them khach hang vao hang doi
    void enqueue(const Product& product) {
        Node* newNode = new Node(product);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Xoa khach hang ra khoi hang doi
    Product dequeue() {
        if (!front) {
            std::cout << "Hang doi rong!" << std::endl;
            return Product{"", 0.0, 0};
        }
        Node* temp = front;
        Product product = temp->product;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return product;
    }
};

// Tao mot san pham moi
Product createProduct() {
    Product p;
    std::cin.ignore(); // Xoa bo dem
    std::cout << "Nhap ten san pham: ";
    std::cin.getline(p.name, MAX_NAME_LENGTH);
    std::cout << "Nhap gia san pham: ";
    std::cin >> p.price;
    std::cout << "Nhap so luong: ";
    std::cin >> p.quantity;
    return p;
}

int main() {
    Queue queue;
    double totalRevenue = 0.0;

    char continueAdding;
    do {
        // Them khach hang vao hang doi
        std::cout << "\nNhap thong tin khach hang moi:" << std::endl;
        Product product = createProduct();
        queue.enqueue(product);

        std::cout << "Ban co muon them khach hang khac? (y/n): ";
        std::cin >> continueAdding;

    } while (continueAdding == 'y' || continueAdding == 'Y');

    // Xu ly tung khach hang
    std::cout << "\nBat dau xu ly khach hang trong hang doi:" << std::endl;
    while (queue.size > 0) {
        Product processed = queue.dequeue();
        double total = processed.calculateTotal();
        totalRevenue += total;

        std::cout << "Da xu ly khach hang: San pham \"" << processed.name 
                  << "\", Tong tien: $" << total << std::endl;
    }

    // Tong doanh thu
    std::cout << "\nTong doanh thu trong phien lam viec: $" << totalRevenue << std::endl;

    return 0;
}
