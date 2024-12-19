#include <iostream>
#include <cstring>

using namespace std;

#define MAX_CHILDREN 10
#define MAX_TITLE_LENGTH 100

// Cau truc mot node trong cay
struct TreeNode {
    char title[MAX_TITLE_LENGTH]; 
    int pages;                    
    TreeNode* children[MAX_CHILDREN]; 
    int childCount;               

    TreeNode(const char* t, int p) : pages(p), childCount(0) {
        strncpy(title, t, MAX_TITLE_LENGTH);
        title[MAX_TITLE_LENGTH - 1] = '\0'; 
        for (int i = 0; i < MAX_CHILDREN; ++i) {
            children[i] = nullptr;
        }
    }
};

// Ham tinh tong so trang cua mot node
int calculateTotalPages(TreeNode* node) {
    int total = node->pages;
    for (int i = 0; i < node->childCount; ++i) {
        total += calculateTotalPages(node->children[i]);
    }
    return total;
}

// Xac dinh so chuong cua cuon sach
int countChapters(TreeNode* root) {
    return root->childCount;
}

// Tim chuong dai nhat 
TreeNode* findLongestChapter(TreeNode* root) {
    TreeNode* longest = nullptr;
    int maxPages = -1;

    for (int i = 0; i < root->childCount; ++i) {
        int chapterPages = calculateTotalPages(root->children[i]);
        if (chapterPages > maxPages) {
            maxPages = chapterPages;
            longest = root->children[i];
        }
    }

    return longest;
}

// Tim va xoa mot muc trong sach
bool findAndRemove(TreeNode* parent, const char* target) {
    for (int i = 0; i < parent->childCount; ++i) {
        if (strcmp(parent->children[i]->title, target) == 0) {
            delete parent->children[i]; 
            for (int j = i; j < parent->childCount - 1; ++j) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->childCount--;
            return true;
        }

        if (findAndRemove(parent->children[i], target)) {
            parent->pages = calculateTotalPages(parent);
            return true;
        }
    }

    return false;
}

// Ham tao mot node moi
TreeNode* createNode(const char* title, int pages) {
    return new TreeNode(title, pages);
}

// Ham xuat thong tin cay
void printTree(TreeNode* node, int level = 0) {
    for (int i = 0; i < level; ++i) cout << "  ";
    cout << node->title << " (" << node->pages << " trang)\n";

    for (int i = 0; i < node->childCount; ++i) {
        printTree(node->children[i], level + 1);
    }
}

// Them chuong moi 
void addChapterFromInput(TreeNode* book) {
    char title[MAX_TITLE_LENGTH];
    int pages;
    cout << "Nhap ten chuong moi: ";
    cin.ignore();
    cin.getline(title, MAX_TITLE_LENGTH);
    cout << "Nhap so trang cua chuong moi: ";
    cin >> pages;

    if (book->childCount < MAX_CHILDREN) {
        book->children[book->childCount++] = createNode(title, pages);
        cout << "Da them chuong: " << title << " (" << pages << " trang).\n";
    } else {
        cout << "Khong the them chuong moi. So luong muc con da toi da.\n";
    }
}

// Xoa muc 
void removeSectionFromInput(TreeNode* book) {
    char target[MAX_TITLE_LENGTH];
    cout << "Nhap ten muc can xoa: ";
    cin.ignore();
    cin.getline(target, MAX_TITLE_LENGTH);

    if (findAndRemove(book, target)) {
        cout << "Da xoa muc: " << target << "\n";
    } else {
        cout << "Khong tim thay muc: " << target << "\n";
    }
}

int main() {
    
    TreeNode* book = createNode("Cuon Sach", 0);

    TreeNode* chapter1 = createNode("Chuong 1", 10);
    TreeNode* chapter2 = createNode("Chuong 2", 15);

    book->children[book->childCount++] = chapter1;
    book->children[book->childCount++] = chapter2;

    chapter1->children[chapter1->childCount++] = createNode("Muc 1.1", 5);
    chapter1->children[chapter1->childCount++] = createNode("Muc 1.2", 7);

    chapter2->children[chapter2->childCount++] = createNode("Muc 2.1", 8);
    chapter2->children[chapter2->childCount++] = createNode("Muc 2.2", 9);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Xuat thong tin cuon sach\n";
        cout << "2. Them chuong moi\n";
        cout << "3. Xoa muc\n";
        cout << "4. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nThong tin cuon sach:\n";
                printTree(book);
                break;
            case 2:
                addChapterFromInput(book);
                break;
            case 3:
                removeSectionFromInput(book);
                break;
            case 4:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 4);

    delete book;
    return 0;
}
