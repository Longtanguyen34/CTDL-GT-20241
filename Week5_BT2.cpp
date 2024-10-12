#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Sàng Eratosthenes để tìm các số nguyên tố
vector<int> sieve(int N) {
    vector<bool> is_prime(N+1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

// Tạo danh sách các số Blum
vector<int> generateBlumNumbers(int N) {
    vector<int> primes = sieve(N);
    vector<int> blumNumbers;
    
    // Chọn các số nguyên tố dạng 4k+3
    vector<int> blumPrimes;
    for (int prime : primes) {
        if (prime % 4 == 3) {
            blumPrimes.push_back(prime);
        }
    }
    
    // Tạo các số Blum từ tích của 2 số nguyên tố dạng 4k+3
    for (size_t i = 0; i < blumPrimes.size(); ++i) {
        for (size_t j = i; j < blumPrimes.size(); ++j) {
            int blum = blumPrimes[i] * blumPrimes[j];
            if (blum < N) {
                blumNumbers.push_back(blum);
            }
        }
    }
    
    // Loại bỏ các số Blum trùng lặp và sắp xếp danh sách
    sort(blumNumbers.begin(), blumNumbers.end());
    blumNumbers.erase(unique(blumNumbers.begin(), blumNumbers.end()), blumNumbers.end());
    
    return blumNumbers;
}

// Tìm tất cả các cặp số Blum có tổng cũng là số Blum
vector<pair<int, int>> findBlumPairs(const vector<int>& blumNumbers, int N) {
    vector<pair<int, int>> blumPairs;
    for (size_t i = 0; i < blumNumbers.size(); ++i) {
        for (size_t j = i; j < blumNumbers.size(); ++j) {
            int sum = blumNumbers[i] + blumNumbers[j];
            if (sum < N && binary_search(blumNumbers.begin(), blumNumbers.end(), sum)) {
                blumPairs.emplace_back(blumNumbers[i], blumNumbers[j]);
            }
        }
    }
    return blumPairs;
}

// Kiểm tra số Blum M có tồn tại trong danh sách không
bool isBlumNumber(int M, const vector<int>& blumNumbers) {
    return binary_search(blumNumbers.begin(), blumNumbers.end(), M);
}

int main() {
    int N, M;
    cout << "Nhap gia tri N: ";
    cin >> N;
    cout << "Nhap so Blum can kiem tra M: ";
    cin >> M;

    // Tạo danh sách các số Blum nhỏ hơn N
    vector<int> blumNumbers = generateBlumNumbers(N);

    // In ra danh sách các số Blum
    cout << "Danh sach cac so Blum nho hon " << N << ":\n";
    for (int blum : blumNumbers) {
        cout << blum << " ";
    }
    cout << endl;

    // Tìm các cặp số Blum có tổng cũng là số Blum
    vector<pair<int, int>> blumPairs = findBlumPairs(blumNumbers, N);
    cout << "Cac cap so cung co the la so Blum:\n";
    for (const auto& p : blumPairs) {
        cout << "(" << p.first << ", " << p.second << ")\n";
    }

    // Kiểm tra số Blum M có tồn tại không
    if (isBlumNumber(M, blumNumbers)) {
        cout << "So " << M << " la mot so Blum.\n";
    } else {
        cout << "So " << M << " khong phai la so Blum.\n";
    }

    return 0;
}