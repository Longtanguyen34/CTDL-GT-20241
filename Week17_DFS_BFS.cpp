#include <iostream>

using namespace std;

const int MAX = 8; 
int adjMatrix[MAX][MAX] = {0}; // Ma tran ke cua do thi
char vertices[MAX] = {'a', 'b', 'c', 'd', 'e', 'g', 'h'}; 
bool visited[MAX]; // Mang danh dau dinh da tham

// Ham tim chi so cua mot dinh trong danh sach dinh
int getIndex(char vertex) {
    for (int i = 0; i < MAX; i++) {
        if (vertices[i] == vertex) return i;
    }
    return -1;
}

// Ham them canh vao do thi
void addEdge(char u, char v) {
    int i = getIndex(u);
    int j = getIndex(v);
    if (i != -1 && j != -1) {
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1; // Do do thi la vo huong
    }
}

// Ham duyet BFS
void BFS(char start) {
    int queue[MAX]; 
    int front = 0, rear = 0; // Chi so dau va cuoi

    for (int i = 0; i < MAX; i++) visited[i] = false; // Danh dau tat ca cac dinh chua tham

    int startIndex = getIndex(start);
    if (startIndex == -1) return;

    // Day dinh bat dau vao hang doi
    queue[rear++] = startIndex;
    visited[startIndex] = true;

    cout << "BFS: ";
    while (front < rear) {
        int current = queue[front++];
        cout << vertices[current] << " ";

        // Duyet cac dinh ke
        for (int i = 0; i < MAX; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

// Ham duyet DFS
void DFS(char start) {
    int stack[MAX]; 
    int top = -1; // Chi so cua phan tu tren cung
    for (int i = 0; i < MAX; i++) visited[i] = false; // Danh dau tat ca cac dinh chua tham
    int startIndex = getIndex(start);
    if (startIndex == -1) return;

    // Day dinh bat dau vao ngan xep
    stack[++top] = startIndex;

    cout << "DFS: ";
    while (top >= 0) {
        int current = stack[top--];
        if (!visited[current]) {
            visited[current] = true;
            cout << vertices[current] << " ";
        }

        // Day cac dinh ke vao ngan xep (theo thu tu nguoc de dam bao thu tu dung)
        for (int i = MAX - 1; i >= 0; i--) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
    cout << endl;
}

int main() {
    addEdge('a', 'b');
    addEdge('a', 'c');
    addEdge('a', 'e');
    addEdge('a', 'g');
    addEdge('b', 'c');
    addEdge('b', 'e');
    addEdge('c', 'd');
    addEdge('d', 'e');
    addEdge('d', 'g');
    addEdge('e', 'h');
    addEdge('g', 'h');

    char start = 'a'; // Duyet tu dinh A
    BFS(start);
    DFS(start);

    return 0;
}
