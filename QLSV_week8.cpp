#include <iostream>
using namespace std;

struct Ngay { 
    int ngay, thang, nam; 
}; 

struct SinhVien { 
    char maSV[9]; 
    char hoTen[50]; 
    int gioiTinh;   
    Ngay ngaySinh; 
    char diaChi[100]; 
    char lop[12]; 
    char khoa[7]; 
};

struct Node { 
    SinhVien data; 
    Node *link; 
}; 

struct List {   
    Node *first;
    Node *last; 
};

// Hàm khởi tạo danh sách
void initList(List &list) {
    list.first = nullptr;
    list.last = nullptr;
}

// Hàm tạo node mới cho sinh viên
Node* createNode(const SinhVien &sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = nullptr;
    return newNode;
}

// Hàm so sánh hai chuỗi (Sắp xếp list sinh viên dựa trên MSSV)
int soSanhChuoi(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return (str1[i] < str2[i]) ? -1 : 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') return 0;
    return (str1[i] == '\0') ? -1 : 1;
}

// Hàm thêm sinh viên 
void themSinhVien(List &list, const SinhVien &sv) {
    Node* newNode = createNode(sv);

    if (list.first == nullptr || soSanhChuoi(sv.maSV, list.first->data.maSV) < 0) {
        newNode->link = list.first;
        list.first = newNode;
        if (list.last == nullptr) list.last = newNode;
    } else {
        Node* prev = nullptr;
        Node* current = list.first;
        while (current != nullptr && soSanhChuoi(current->data.maSV, sv.maSV) < 0) {
            prev = current;
            current = current->link;
        }
        newNode->link = current;
        prev->link = newNode;
        if (current == nullptr) list.last = newNode;
    }
}

// Hàm nhập thông tin sinh viên
void nhapSinhVien(SinhVien &sv) {
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cin.ignore(); 
    cout << "Nhap ten: ";
    cin.getline(sv.hoTen, sizeof(sv.hoTen));
    cout << "Nhap gioi tinh (0: Nam, 1: Nu): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh (ngay thang nam): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore(); 
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, sizeof(sv.diaChi));
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cin.ignore(); 
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
}

// Hàm in danh sách sinh viên
void inList(const List &list) {
    Node* current = list.first;
    while (current != nullptr) {
        cout << "Ma SV: " << current->data.maSV
             << ", Ho ten: " << current->data.hoTen
             << ", Gioi tinh: " << current->data.gioiTinh
             << ", Ngay sinh: " << current->data.ngaySinh.ngay << "/"
             << current->data.ngaySinh.thang << "/" << current->data.ngaySinh.nam
             << ", Dia chi: " << current->data.diaChi
             << ", Lop: " << current->data.lop
             << ", Khoa: " << current->data.khoa << endl;
        current = current->link;
    }
}

bool soSanhNgay(const Ngay &ng1, const Ngay &ng2) {
    return ng1.ngay == ng2.ngay && ng1.thang == ng2.thang && ng1.nam == ng2.nam;
}

// Hàm in các sinh viên có cùng ngày sinh
void inSinhVienCungNgaySinh(const List &list) {
    bool found = false;
    for (Node* outer = list.first; outer != nullptr; outer = outer->link) {
        for (Node* inner = outer->link; inner != nullptr; inner = inner->link) {
            if (soSanhNgay(outer->data.ngaySinh, inner->data.ngaySinh)) {
                if (!found) {
                    cout << "Danh sach sinh vien co cung ngay sinh:"<< endl;
                    found = true;
                }
                cout << "Ma SV: " << inner->data.maSV << ", Ho ten: " << inner->data.hoTen << endl;
                break;
            }
        }
    }
    if (!found) cout << "Khong co sinh vien co cung ngay sinh" << endl;
}

// Hàm loại bỏ sinh viên có cùng ngày sinh
void xoaSinhVienCungNgaySinh(List &list) {
    Node* prev = nullptr;
    Node* current = list.first;
    while (current != nullptr) {
        Node* checker = current->link;
        bool hasDuplicate = false;
        while (checker != nullptr) {
            if (soSanhNgay(current->data.ngaySinh, checker->data.ngaySinh)) {
                hasDuplicate = true;
                break;
            }
            checker = checker->link;
        }
        if (hasDuplicate) {
            if (prev == nullptr) list.first = current->link;
            else prev->link = current->link;

            Node* temp = current;
            current = current->link;
            delete temp;
        } else {
            prev = current;
            current = current->link;
        }
    }
}

int main() {
    List listSV;
    initList(listSV);
    
    SinhVien svArr[3] = {
        {"20224442", "Ta Nguyen Long", 0, {3, 4, 2004}, "Phu Tho", "01", "IoT"},
        {"20224436", "Nguyen Duc Hanh", 0, {27, 11, 2004}, "Thai Binh", "01", "IoT"},
        {"20224405", "Bui Ngoc Dat", 0, {13, 1, 2004}, "Hai Phong", "01", "IoT"},
       
    };
    for (int i = 0; i < 3; i++) {
        themSinhVien(listSV, svArr[i]);
    }

    cout << "Danh sach sinh vien" << endl;
    inList(listSV);

    inSinhVienCungNgaySinh(listSV);

    xoaSinhVienCungNgaySinh(listSV);

    cout << "Danh sach sau khi loai bo sinh vien co cung ngay sinh" << endl;
    inList(listSV);

    return 0;
}
