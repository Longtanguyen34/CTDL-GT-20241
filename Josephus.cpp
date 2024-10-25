#include <iostream>
using namespace std;

struct Node {
    int data; 
    Node *next;
};

// Hàm khởi tạo danh sách liên kết vòng với N người chơi
Node* createCircularList(int N) {
    if (N <= 0) return nullptr;  // Nếu N không hợp lệ, trả về nullptr

    Node *head = new Node{1, nullptr};
    Node *current = head;
    
    for (int i = 2; i <= N; i++) {
        current->next = new Node{i, nullptr};
        current = current->next;
    }
    current->next = head;  // Tạo vòng
    return head;
}

// Hàm để tìm người chiến thắng cuối cùng với bất kỳ giá trị M
int josephus(Node *head, int M) {
    if (head == nullptr) return -1;  // Kiểm tra nếu danh sách rỗng
    if (M < 0) {
        cout << "M phai la so nguyen khong am." << endl;
        return -1;
    }
    
    Node *prev = nullptr;
    Node *current = head;
    
    // Trường hợp đặc biệt khi M = 0
    if (M == 0) {
        // Xóa lần lượt từng người chơi từ 1 đến N-1
        int N;
        for (int i = 1; i < N; i++) {
            cout << "Nguoi choi " << current->data << " bi loai" << endl;
            prev = current;
            current = current->next;
            head->next = current;  // Bỏ qua node bị loại
            delete prev;  // Xóa node bị loại
        }
        int winner = current->data;
        delete current;  // Xóa người chơi cuối cùng
        return winner;
    }

    // Các trường hợp khác với M > 0
    int step = M + 1;
    
    // Tiếp tục cho đến khi còn lại một người
    while (current->next != current) {
        for (int count = 1; count < step; count++) {
            prev = current;
            current = current->next;
        }
        
        // Loại bỏ người chơi hiện tại
        cout << "Nguoi choi " << current->data << " bi loai" << endl;
        prev->next = current->next;
        delete current;
        current = prev->next;  
    }
    
    int winner = current->data;
    delete current;  // Xóa người chơi cuối cùng
    return winner;
}

int main() {
    int N, M;
    cout << "Nhap so nguoi choi N: ";
    cin >> N;
    if (N < 1) {
        cout << "N phai lon hon 0." << endl;
        return 0; // Kết thúc chương trình nếu N không hợp lệ
    }
    cout << "Nhap so M: ";
    cin >> M;

    Node *head = createCircularList(N);
    int winner = josephus(head, M);

    if (winner != -1) { // Kiểm tra người chiến thắng hợp lệ
        cout << "Nguoi chien thang la nguoi choi so " << winner << endl;
    }
    return 0;
}
