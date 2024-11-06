#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int R, C;
        ll K;
        cin >> R >> C >> K;
        vector<vector<int>> G(R, vector<int>(C));
        int max_id = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> G[i][j];
                if (G[i][j] > max_id) max_id = G[i][j];
            }
        }
        vector<vector<pair<int, int>>> bunny_cells(max_id + 1);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                bunny_cells[G[i][j]].emplace_back(i, j);
            }
        }
        int left = 0, right = max(R, C);
        int answer = max(R, C);
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int s_row = min(mid, R - 1);
            int s_col = min(mid, C - 1);
            ll sum_row = (ll)R * (2LL * s_row + 1) - 1LL * s_row * (s_row + 1);
            ll sum_col = (ll)C * (2LL * s_col + 1) - 1LL * s_col * (s_col + 1);
            ll total_pairs_S = sum_row * sum_col - (ll)R * C;
            ll same_owner_pairs_S = 0;
            for (int b = 1; b <= max_id; b++) {
                int cb = bunny_cells[b].size();
                if (cb <= 1) continue;
                vector<pair<int, int>> &cells = bunny_cells[b];
                sort(cells.begin(), cells.end());
                for (int r = 0; r < cb; r++) {
                    int i_r = cells[r].first;
                    int j_r = cells[r].second;
                    int l = lower_bound(cells.begin(), cells.end(), make_pair(i_r - mid, -1)) - cells.begin();
                    int u = upper_bound(cells.begin(), cells.end(), make_pair(i_r + mid, C)) - cells.begin();
                    int low = j_r - mid;
                    int high = j_r + mid;
                    int lower_idx = lower_bound(cells.begin() + l, cells.begin() + u, make_pair(0, low),
                        [&](const pair<int, int> &a, const pair<int, int> &b) -> bool {
                            return a.second < b.second;
                        }) - cells.begin();
                    int upper_idx = upper_bound(cells.begin() + l, cells.begin() + u, make_pair(0, high),
                        [&](const pair<int, int> &a, const pair<int, int> &b) -> bool {
                            return a.second < b.second;
                        }) - cells.begin();
                    same_owner_pairs_S += (ll)(upper_idx - lower_idx);
                }
                same_owner_pairs_S -= (ll)cb;
            }
            ll valid_pairs_S = total_pairs_S - same_owner_pairs_S;
            if (valid_pairs_S >= K) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        cout << "Case #" << tc << ": " << answer << "\n";
    }
}
