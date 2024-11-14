#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

struct WordNode {
    std::string word;
    WordNode* next;
};

class WordList {
private:
    WordNode* head;
    WordNode* tail; 

public:
    WordList() : head(nullptr), tail(nullptr) {}

    // Them tu vao cuoi danh sach
    void addWord(const std::string& word) {
        WordNode* newNode = new WordNode{word, nullptr};
        if (!head) {  
            head = tail = newNode;
        } else {  
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Tim tu xuat hien nhieu nhat
    std::string findMostFrequentWord() {
        std::unordered_map<std::string, int> wordCount;
        WordNode* current = head;
        while (current) {
            wordCount[current->word]++;
            current = current->next;
        }

        std::string mostFrequent;
        int maxCount = 0;
        for (const auto& pair : wordCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequent = pair.first;
            }
        }
        return mostFrequent;
    }

    // Bo tu lay
    void removeReduplication() {
        WordNode* current = head;
        WordNode* prev = nullptr;
        while (current && current->next) {
            if (current->word == current->next->word) {
                WordNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Dem so luong tu khac nhau
    int countUniqueWords() {
        std::unordered_map<std::string, bool> uniqueWords;
        WordNode* current = head;
        while (current) {
            uniqueWords[current->word] = true;
            current = current->next;
        }
        return uniqueWords.size();
    }

    // Hien thi cau
    void displayWords() const {
        WordNode* current = head;
        while (current) {
            std::cout << current->word << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~WordList() {
        while (head) {
            WordNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    WordList wordList;
    std::string inputLine;
    
    std::cout << "Nhap cac tu (khong dau, ngan cach bang khoang trang): ";
    std::getline(std::cin, inputLine);
    
    std::stringstream ss(inputLine);
    std::string word;
    
    while (ss >> word) {
        wordList.addWord(word);
    }

    std::cout << "\nDanh sach tu ban dau:\n";
    wordList.displayWords();

    std::string mostFrequent = wordList.findMostFrequentWord();
    std::cout << "\nTu xuat hien nhieu nhat: " << mostFrequent << "\n";

    wordList.removeReduplication();
    std::cout << "\nDanh sach tu sau khi loai bo tu lay:\n";
    wordList.displayWords();

    int uniqueCount = wordList.countUniqueWords();
    std::cout << "\nSo tu vung khac nhau trong cau: " << uniqueCount << "\n";

    return 0;
}
