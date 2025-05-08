#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define repd(i, r, l) for (int i = r; i >= l; --i)
#define _unique(x) (x).resize(unique((x).begin(), (x).end()) - (x).begin());
#define sz(v) (int)(v).size()
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'

using namespace std;

const int N = 1e6 + 5;
const int M = 2e3 + 5;
const int mod = 1e9 + 7;
const int inf = 1e18 + 7;

int n;
int a[N];

int comb2(int x) {
    return x * (x - 1) / 2;
}

int comb3(int x) {
    return x * (x - 1) * (x - 2) / 6;
}

namespace sub1 {
    bool isTriangle(int a, int b, int c) {
        return (a + b > c && a + c > b && b + c > a);
    }

    bool isSpecTriangle(int a, int b, int c) {
        return (a == b || b == c || a == c);
    }

    void solve(void) {
        int res = 0;
        rep(i, 1, n - 2) rep(j, i + 1, n - 1) rep(k, j + 1, n)
            if (isTriangle(a[i], a[j], a[k]) && isSpecTriangle(a[i], a[j], a[k])) ++res;
        cout << res;
    }
}

namespace sub2 {
    int cnt[N], pre[N];
    void solve(void) {
        rep(i, 1, n) cnt[a[i]]++;
        rep(i, 1, (int)1e5) pre[i] = pre[i - 1] + cnt[i];

        int res = 0;
        rep(i, 1, (int)1e5) {
            if (cnt[i] >= 3) res += comb3(cnt[i]);

            if (cnt[i] >= 2) {
                // 2a > c
                int limit = min(2 * i - 1, (int)1e5);
                int c = pre[limit] - cnt[i];
                res += comb2(cnt[i]) * c;
            }
        }

        cout << res;
    }
}

namespace sub3 {
    map <int, int> cnt;
    int pre[N];
    
    void solve(void) {
        vector <int> v;
        rep(i, 1, n) cnt[a[i]]++, v.push_back(a[i]);

        sort(all(v));
        _unique(v);

        
        rep(i, 0, sz(v) - 1) pre[i] = pre[i - 1] + cnt[v[i]];

        int res = 0;
        for (int i : v) {
            if (cnt[i] >= 3) res += comb3(cnt[i]);
            if (cnt[i] >= 2) {
                int limit = min(2 * i - 1, (int)1e9);
                // c <= 2a - 1
                int j = upper_bound(all(v), limit) - v.begin() - 1;
                
                int c = pre[j] - cnt[i];
                res += comb2(cnt[i]) * c;
            }
        }
        cout << res;
    }
}

void solve(void) {
    bool op2 = 1;

    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        if (a[i] >= (int)1e5) op2 = 0;
    }

    if (n <= 100) {
        sub1::solve();
        return ;
    }

    if (n <= (int)1e5 && op2) {
        sub2::solve();
        return ;
    }

    sub3::solve();
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    solve();
    return 0;
}