#include<bits/stdc++.h>
#define int long long

using namespace std;

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (n == 1) {
            cout << a[0] << endl;
            continue;
        }
        int max_sum = 0;
        for (int num : a) {
            max_sum += num;
        }
        for (int k = 1; k <= n-1; k++) {
            vector<int> current = a;
            for (int step = 0; step < k; step++) {
                if (current.size() == 1) break;
                if (current[0] > current.back()) {
                    reverse(current.begin(), current.end());
                }
                vector<int> diff;
                for (int i = 0; i < current.size() - 1; i++) {
                    diff.push_back(current[i+1] - current[i]);
                }
                current = diff;
            }
            int sum = 0;
            for (int num : current) {
                sum += num;
            }
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
        cout << max_sum << endl;
    }
    return 0;
}

