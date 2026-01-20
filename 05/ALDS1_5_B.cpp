/*
マージソート
マージソート（Merge Sort）は分割統治法に基づく高速なアルゴリズムで、次のように実装することができます。

merge(A, left, mid, right)
  n1 = mid - left;
  n2 = right - mid;
  L[0...n1], R[0...n2] を生成
  for i = 0 to n1-1
    L[i] = A[left + i]
  for i = 0 to n2-1
    R[i] = A[mid + i]
  L[n1] = INFTY
  R[n2] = INFTY
  i = 0
  j = 0
  for k = left to right-1
    if L[i] <= R[j]
      A[k] = L[i]
      i = i + 1
    else 
      A[k] = R[j]
      j = j + 1

mergeSort(A, left, right)
  if left+1 < right
    mid = (left + right)/2;
    mergeSort(A, left, mid)
    mergeSort(A, mid, right)
    merge(A, left, mid, right)
 個の整数を含む数列 
 を上の疑似コードに従ったマージソートで昇順に整列するプログラムを作成してください。また、mergeにおける比較回数の総数を報告してください。

入力
１行目に 
、２行目に 
 を表す 
 個の整数が与えられます。

出力
１行目に整列済みの数列 
 を出力してください。数列の隣り合う要素は１つの空白で区切ってください。２行目に比較回数を出力してください。

制約
の要素
入力例 1
10
8 5 9 2 6 3 7 1 10 4
出力例 1
1 2 3 4 5 6 7 8 9 10
34
*/

#include<iostream>
#include<vector>

using namespace std;

const int INFTY = 2000000000;

int compare_count = 0;

void merge(vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;

    vector<int> L(n1 + 1), R(n2 + 1);
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + i];

    L[n1] = INFTY;
    R[n2] = INFTY;

    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        compare_count++;
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void mergeSort(vector<int>& A, int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid, right);
        merge(A, left, mid, right);
    }
}

int main(){
    int n;
    if (!(cin >> n)) return 0;

    vector<int> S(n);
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }

    mergeSort(S, 0, n);

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << S[i];
    }
    cout << endl;
    cout << compare_count << endl;

    return 0;

}