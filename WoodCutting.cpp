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
#define p2i pair<int,pii>
#define endl '\n'

using namespace std;

const int N = 1e6 + 5;
const int M = 2e3 + 5;
const int mod = 1e9 + 7;
const int inf = 1e18 + 7;
const bool ComGa999ms = false;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {
    return l+rng()%(r-l+1);
}

int maximize(int &a, int b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}

int minimize(int &a, int b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}

int n, s;
multiset <int> Set;

void solve(void) {
    cin >> n >> s;
    rep(i, 1, n) {
        int x; cin >> x;
        Set.insert(x);
    }

    int res = 0;
    while (sz(Set) > 1) {
        int Fi = *Set.begin(); Set.erase(Set.begin());
        int Se = *Set.begin(); Set.erase(Set.begin());

        res += Se + Fi;
        Set.insert(Se + Fi);
    }

    cout << res;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    if (ComGa999ms) {
        int t; cin >> t;
        while (t-- ) solve();
    } else solve();

    return 0;
}