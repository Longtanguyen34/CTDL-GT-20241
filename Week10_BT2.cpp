#include <iostream>
#include <string>

struct Tep {
    std::string ten;
    int kichThuoc; 
    int thoiGian;  
    Tep* next;
};

class DanhSachTep {
private:
    Tep* head;

    // Xoa node dau danh sach
    void xoaDau() {
        if (!head) return;
        Tep* temp = head;
        head = head->next;
        delete temp;
    }

public:
    DanhSachTep() : head(nullptr) {}

    // Them tep tin vao danh sach theo thu tu tang dan kich thuoc
    void themTep(const std::string& ten, int kichThuoc, int thoiGian) {
        Tep* tepMoi = new Tep{ten, kichThuoc, thoiGian, nullptr};
        if (!head || kichThuoc < head->kichThuoc) {  //Thêm moi tep tin neu ko co san
            tepMoi->next = head;
            head = tepMoi;
            return;
        }
        Tep* current = head;
        while (current->next && current->next->kichThuoc <= kichThuoc) {
            current = current->next;
        }
        tepMoi->next = current->next;
        current->next = tepMoi;
    }

    // Xoa tep co kich thuoc nho nhat va thoi gian luu lau nhat
    void xoaTepNhoNhatVaCuNhat() {
        if (!head) return;

        Tep* current = head;
        Tep* minFile = head;
        Tep* prevMin = nullptr;
        Tep* prev = nullptr;

        while (current) {
            if (current->kichThuoc == minFile->kichThuoc && current->thoiGian < minFile->thoiGian) {
                minFile = current;
                prevMin = prev;
            }
            prev = current;
            current = current->next;
        }

        if (!prevMin) {  //Ko co thi xoa luon tep dau tien
            xoaDau();
        } else {
            prevMin->next = minFile->next;
            delete minFile;
        }
    }

    // Hien thi danh sach tep
    void hienThiTep() {
        Tep* current = head;
        while (current) {
            std::cout << "File: " << current->ten 
                      << ", Size: " << current->kichThuoc 
                      << "KB, Time: " << current->thoiGian << "s\n";
            current = current->next;
        }
    }

    ~DanhSachTep() {
        while (head) {
            xoaDau();
        }
    }
};

int main() {
    DanhSachTep folder;

    // Them tep tin vao danh sach
    folder.themTep("FileA", 100, 1200);
    folder.themTep("FileB", 50, 1100);
    folder.themTep("FileC", 50, 1000);
    folder.themTep("FileD", 200, 900);
    folder.themTep("FileE", 500, 900);
    folder.themTep("FileF", 1200, 2900);
    folder.themTep("FileG", 20, 900);
    folder.themTep("FileH", 210, 800);

    std::cout << "Danh sach tep ban dau:\n";
    folder.hienThiTep();

    folder.xoaTepNhoNhatVaCuNhat();
    std::cout << "Danh sach sau khi xoa tep co kich thuoc nho nhat va thoi gian luu lau nhat sau do sap xep lai:\n";
    folder.hienThiTep();

    return 0;
}
