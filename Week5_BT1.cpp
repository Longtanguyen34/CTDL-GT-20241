#include <iostream>
using namespace std;
void swap(int &a,int &b )
{
      int temp = a;
      a = b;
      b = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx; 
    for (i = 0; i < n - 1; i++)
    { 
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(arr[min_idx], arr[i]);
        for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
        cout << endl;
    }
}


int main()
{
    int A[12]={240,73,101,21,13,25,11,37,89,30,15,51};
    cout << "Selection sort:" << endl;
    selectionSort(A, 12);

}