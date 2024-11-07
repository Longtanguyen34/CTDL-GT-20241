#include <iostream>
using namespace std;

// Định nghĩa cấu trúc cho Node của danh sách đa thức
struct Node {
    float heso;   // Hệ số của đơn thức
    int somu;     // Số mũ của đơn thức
    Node* link;   // Con trỏ đến phần tử tiếp theo trong danh sách
};

// Định nghĩa cấu trúc cho danh sách đa thức
struct ListDT {
    Node* first;  // Con trỏ đến phần tử đầu tiên của danh sách
    Node* last;   // Con trỏ đến phần tử cuối cùng của danh sách
};

// Khởi tạo danh sách đa thức rỗng
void initDT(ListDT& l) {
    l.first = l.last = nullptr;
}

// Tạo một node mới với hệ số và số mũ cho trước
Node* createNode(float hs, int sm) {
    Node* p = new Node;  // Tạo một node mới
    if (p == nullptr) return nullptr; // Kiểm tra cấp phát bộ nhớ
    p->heso = hs;       // Gán hệ số
    p->somu = sm;       // Gán số mũ
    p->link = nullptr;  // Ban đầu node này chưa liên kết đến node nào
    return p;
}

// Thêm một node vào cuối danh sách đa thức
void addNode(ListDT& lDT, Node* p) {
    if (lDT.first == nullptr) {   // Nếu danh sách rỗng
        lDT.first = lDT.last = p; // Node mới là cả đầu và cuối của danh sách
    } else {
        lDT.last->link = p;       // Liên kết node cuối hiện tại với node mới
        lDT.last = p;             // Cập nhật node cuối
    }
}

// Tạo và thêm một node với hệ số và số mũ cho trước vào danh sách
void attachNode(ListDT& lDT, float hs, int sm) {
    Node* newNode = createNode(hs, sm); // Tạo node mới
    if (newNode != nullptr) {
        addNode(lDT, newNode);          // Thêm node vào cuối danh sách
    }
}

// Nhập đa thức (cần truyền theo tham chiếu để thay đổi có hiệu lực)
void taoDT(ListDT& lDT) {
    float hs;
    int sm;
    int i = 1; // Biến đếm số phần tử
    cout << "- Bat dau nhap da thuc (nhap he so 0 de ket thuc): " << endl;
    while (true) {
        cout << "Nhap he so cua phan tu thu " << i << ": ";
        cin >> hs;  // Nhập hệ số
        if (hs == 0) break;  // Thoát nếu hệ số bằng 0
        cout << "Nhap so mu cua phan tu thu " << i << ": ";
        cin >> sm;           // Nhập số mũ
        attachNode(lDT, hs, sm); // Thêm đơn thức vào danh sách
        ++i;
    }
}

// In đa thức
void inDT(const ListDT& lDT) {
    Node* p = lDT.first;     // Bắt đầu từ đầu danh sách
    bool firstTerm = true;   // Biến kiểm tra đơn thức đầu tiên
    cout << "f(x) = ";
    while (p != nullptr) {
        if (!firstTerm && p->heso > 0) cout << " + "; // In dấu cộng cho các đơn thức tiếp theo
        if (p->somu == 0) {    // Nếu số mũ là 0, chỉ in hệ số
            cout << p->heso;
        } else if (p->heso == 1) { // Nếu hệ số là 1, chỉ in x^somu
            cout << "x^" << p->somu;
        } else {               // In hệ số và số mũ
            cout << p->heso << " * x^" << p->somu;
        }
        firstTerm = false;     // Cập nhật là đã qua đơn thức đầu tiên
        p = p->link;           // Chuyển đến đơn thức tiếp theo
    }
    cout << endl;
}

int main() {
    ListDT DT1, DT2;     
    initDT(DT1);        
    initDT(DT2);      
    
    cout << "Nhap da thuc f(x):\n";
    taoDT(DT1);
    cout << "Nhap da thuc g(x):\n";
    taoDT(DT2);

    cout << "\nDa thuc f(x): ";
    inDT(DT1);
    cout << "\nDa thuc g(x): ";
    inDT(DT2);

    return 0;
}
