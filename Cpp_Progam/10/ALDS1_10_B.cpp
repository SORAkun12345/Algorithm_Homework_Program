#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        int r, c;
        cin >> r >> c;
        p[i - 1] = r;
        if (i == n) p[i] = c;
    }

    vector<vector<long long>> m(n + 1, vector<long long>(n + 1, 0));

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = LLONG_MAX;

            for (int k = i; k <= j - 1; k++) {
                long long q = m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                m[i][j] = min(m[i][j], q);
            }
        }
    }

    cout << m[1][n] << endl;

    return 0;
}