#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sortColors(vector<int>& colors) {
    int low = 0, mid = 0, high = colors.size() - 1;
    
    while (mid <= high) {
        if (colors[mid] == 0) { // màu đỏ
            swap(colors[low], colors[mid]);
            low++;
            mid++;
        }
        else if (colors[mid] == 1) { // màu trắng
            mid++;
        }
        else { // màu xanh
            swap(colors[mid], colors[high]);
            high--;
        }
    }
}

int main() {
    vector<int> colors = {2, 0, 2, 0, 0, 1, 0, 2, 1};
    sortColors(colors);
    for (int color : colors) {
        if (color == 0) cout << "red ";
        else if (color == 1) cout << "white ";
        else cout << "blue ";
    }
    
    return 0;
}