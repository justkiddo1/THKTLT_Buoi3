#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <string>
#define MAX 100

using namespace std;

void createMatrix(int matrix[][100], int m, int n) {
    srand(time(0)); // Khởi tạo seed cho random  
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100; // Gán giá trị ngẫu nhiên từ 0 đến 99  
        }
    }
}

// Hàm xuất ma trận  
void printMatrix(int matrix[][100], int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm tính tổng các phần tử trong từng dòng  
void sumOfRows(int matrix[][100], int m, int n) {
    for (int i = 0; i < m; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += matrix[i][j];
        }
        cout << "Tổng dòng " << i << ": " << sum << endl;
    }
}

// Hàm tìm phần tử lớn nhất trong từng cột  
void maxInColumns(int matrix[][100], int m, int n) {
    for (int j = 0; j < n; ++j) {
        int maxVal = matrix[0][j];
        for (int i = 1; i < m; ++i) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
        cout << "Giá trị lớn nhất trong cột " << j << ": " << maxVal << endl;
    }
}

// Hàm xuất các phần tử ở rìa của ma trận  
void borderElements(int matrix[][100], int m, int n) {
    cout << "Các phần tử ở rìa: ";
    // Phần trên  
    for (int j = 0; j < n; ++j) {
        cout << matrix[0][j] << " ";
    }
    // Phần bên phải  
    for (int i = 1; i < m; ++i) {
        cout << matrix[i][n - 1] << " ";
    }
    // Phần dưới  
    if (m > 1) {
        for (int j = n - 1; j >= 0; --j) {
            cout << matrix[m - 1][j] << " ";
        }
    }
    // Phần bên trái  
    if (n > 1) {
        for (int i = m - 2; i > 0; --i) {
            cout << matrix[i][0] << " ";
        }
    }
    cout << endl;
}

// Hàm xuất các phần tử cực đại  
void printLocalMax(int matrix[][100], int m, int n) {
    cout << "Các phần tử cực đại: ";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            bool isLocalMax = true;
            for (int a = -1; a <= 1; ++a) {
                for (int b = -1; b <= 1; ++b) {
                    if (a == 0 && b == 0) continue; // Bỏ qua chính nó  
                    int ni = i + a, nj = j + b;
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        if (matrix[i][j] < matrix[ni][nj]) {
                            isLocalMax = false;
                        }
                    }
                }
            }
            if (isLocalMax) {
                cout << matrix[i][j] << " ";
            }
        }
    }
    cout << endl;
}

// Hàm xuất các phần tử hoàng hậu  
void printQueens(int matrix[][100], int m, int n) {
    cout << "Các phần tử hoàng hậu: ";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            bool isQueen = true;
            for (int other : matrix[i]) {
                if (other > matrix[i][j]) {
                    isQueen = false;
                    break;
                }
            }
            if (isQueen) {
                cout << matrix[i][j] << " ";
            }
        }
    }
    cout << endl;
}

// Hàm xuất các dòng chỉ chứa số chẵn  
void printEvenRows(int matrix[][100], int m, int n) {
    for (int i = 0; i < m; ++i) {
        bool allEven = true;
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] % 2 != 0) {
                allEven = false;
                break;
            }
        }
        if (allEven) {
            cout << "Dòng chẵn: ";
            for (int val : matrix[i]) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
}

// Hàm sắp xếp mảng tăng theo từng dòng  
void sortRows(int matrix[][100], int m, int n) {
    for (int i = 0; i < m; ++i) {
        sort(matrix[i], matrix[i] + n);
    }
}

void printOddColumns(int matrix[][MAX], int m, int n) {
    cout << "Cac cot chua so le:\n";
    for (int j = 0; j < n; j++) {
        bool allOdd = true;
        for (int i = 0; i < m; i++) {
            if (matrix[i][j] % 2 == 0) {
                allOdd = false;
                break;
            }
        }
        if (allOdd) {
            for (int i = 0; i < m; i++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
}

// Tìm phần tử lớn nhất trong các phần tử trên biên của ma trận  
int maxBoundaryElement(int matrix[][MAX], int m, int n) {
    int maxVal = matrix[0][0];

    // Biên trên  
    for (int j = 0; j < n; j++) {
        maxVal = max(maxVal, matrix[0][j]);
    }
    // Biên dưới  
    for (int j = 0; j < n; j++) {
        maxVal = max(maxVal, matrix[m - 1][j]);
    }
    // Biên trái và phải  
    for (int i = 0; i < m; i++) {
        maxVal = max(maxVal, matrix[i][0]);
        maxVal = max(maxVal, matrix[i][n - 1]);
    }

    return maxVal;
}

// Tìm số lượng phần tử có chữ số '2' trong các số của ma trận  
int countElementWithDigitTwo(int matrix[][MAX], int m, int n) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (to_string(matrix[i][j]).find('2') != string::npos) {
                count++;
            }
        }
    }
    return count;
}

// Xuất các phần tử cực tiểu của ma trận  
void printLocalMinElements(int matrix[][MAX], int m, int n) {
    cout << "Cac phan tu cuc tieu:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            bool isLocalMin = true;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue; // Bỏ qua chính nó  
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        if (matrix[i][j] >= matrix[ni][nj]) {
                            isLocalMin = false;
                        }
                    }
                }
            }
            if (isLocalMin) {
                cout << matrix[i][j] << " ";
            }
        }
    }
    cout << endl;
}

// Sắp xếp ma trận theo yêu cầu chỉ số dòng  
void sortRowsByIndex(int matrix[][MAX], int m, int n) {
    for (int i = 0; i < m; i++) {
        vector<int> row(matrix[i], matrix[i] + n);
        if (i % 2 == 0) { // Dòng chẵn  
            sort(row.begin(), row.end(), greater<int>());
        }
        else { // Dòng lẻ  
            sort(row.begin(), row.end());
        }
        for (int j = 0; j < n; j++) {
            matrix[i][j] = row[j];
        }
    }
}

// Sắp xếp cột theo yêu cầu chỉ số cột  
void sortColumnsByIndex(int matrix[][MAX], int m, int n) {
    for (int j = 0; j < n; j++) {
        vector<int> column(m);
        for (int i = 0; i < m; i++) {
            column[i] = matrix[i][j];
        }
        if (j % 2 == 0) { // Cột chẵn  
            sort(column.begin(), column.end());
        }
        else { // Cột lẻ  
            sort(column.begin(), column.end(), greater<int>());
        }
        for (int i = 0; i < m; i++) {
            matrix[i][j] = column[i];
        }
    }
}

// Kiểm tra ma trận giảm dần ziczac  
bool isZigZagMatrix(int matrix[][MAX], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            if ((i % 2 == 0 && matrix[i][j] <= matrix[i][j + 1]) ||
                (i % 2 == 1 && matrix[i][j] >= matrix[i][j + 1])) {
                return false;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m - 1; i++) {
            if ((j % 2 == 0 && matrix[i][j] >= matrix[i + 1][j]) ||
                (j % 2 == 1 && matrix[i][j] <= matrix[i + 1][j])) {
                return false;
            }
        }
    }
    return true;
}

// Liệt kê chỉ số các dòng chứa toàn với giá trị chẵn  
void listEvenRowsIndexes(int matrix[][MAX], int m, int n) {
    cout << "Chi so cac dong chua toan so chan: ";
    for (int i = 0; i < m; i++) {
        bool allEven = true;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] % 2 != 0) {
                allEven = false;
                break;
            }
        }
        if (allEven) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Liệt kê các dòng chứa giá trị giảm dần  
void listDecreasingRows(int matrix[][MAX], int m, int n) {
    cout << "Cac dong chua gia tri giam dan: ";
    for (int i = 0; i < m; i++) {
        bool isDecreasing = true;
        for (int j = 0; j < n - 1; j++) {
            if (matrix[i][j] <= matrix[i][j + 1]) {
                isDecreasing = false;
                break;
            }
        }
        if (isDecreasing) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Tìm giá trị xuất hiện nhiều nhất trong ma trận  
int findMostCommonValue(int matrix[][MAX], int m, int n) {
    unordered_map<int, int> frequency;
    int mostCommon = matrix[0][0];
    int maxCount = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            frequency[matrix[i][j]]++;
            if (frequency[matrix[i][j]] > maxCount) {
                maxCount = frequency[matrix[i][j]];
                mostCommon = matrix[i][j];
            }
        }
    }
    return mostCommon;
}

// Hàm main  
int main() {
    int m, n;
    cout << "Nhap so dong : ";
    cin >> m;
    cout << "Nhap so cot : ";
    cin >> n;
    int matrix[MAX][MAX];

    createMatrix(matrix, m, n);

    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Xuat ma tran\n";
        cout << "2. Tinh tong cac dong\n";
        cout << "3. Tim gia tri lon nhat trong cac cot\n";
        cout << "4. Xuat cac phan tu bien\n";
        cout << "5. Xuat cac phan tu cuc dai\n";
        cout << "6. Xuat cac phan tu hoang hau\n";
        cout << "7. Xuat cac dong chi chua so chan\n";
        cout << "8. Sap xep ma tran theo dong\n";
        cout << "9. Thoat\n";
        cout << "Chon mot tuy chon : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Ma trận:\n";
            printMatrix(matrix, m, n);
            break;
        case 2:
            sumOfRows(matrix, m, n);
            break;
        case 3:
            maxInColumns(matrix, m, n);
            break;
        case 4:
            borderElements(matrix, m, n);
            break;
        case 5:
            printLocalMax(matrix, m, n);
            break;
        case 6:
            printQueens(matrix, m, n);
            break;
        case 7:
            printEvenRows(matrix, m, n);
            break;
        case 8:
            sortRows(matrix, m, n);
            cout << "Ma trận sau khi sắp xếp:\n";
            printMatrix(matrix, m, n);
            break;
        case 9:
            cout << "Thoát chương trình.\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}
