# DSA Assignment5

Họ và tên: Nguyễn Đăng Khoa

Lớp: ATTN2024

MSSV: 24520825

## [H007] - Alpha Problem
Đẻ chuyển số $n$ dưới cơ số $base$ thì chỉ cần chia base đến khi $n = 0$ và in ra số dư trong mỗi lần mod $base$.

```C++
cin >> n >> base;

while (n) {
    int o = n % base;
    res.push_back(o);

    n /= base;
}

repd(i, sz(res) - 1, 0) cout << res[i];
```

## [H006] - Word Merging 
Bài này chỉ cần lấy một stack chỉ cần so sánh nếu top của stack và kí tự $c$ hiện tại thì pop ra.

```C++
string s;
cin >> s;

stack <char> st;
for (char c : s) {
    if (st.size() && st.top() == c) st.pop();
    else st.push(c);
}

cout << sz(st);
```
## [H004] - Wood Cutting
Bài này tham lam insert cả dãy vào Set rồi cứ lấy 2 phần tử bẻ nhất cộng lại rồi insert ngược lại.

```C++
int res = 0;
while (sz(Set) > 1) {
    int Fi = *Set.begin(); Set.erase(Set.begin());
    int Se = *Set.begin(); Set.erase(Set.begin());

    res += Se + Fi;
    Set.insert(Se + Fi);
}

cout << res;
```

## [H003] - Isosceles Triangle

### Subtask 1 ($1 \leq n \leq 100$)
Vì giới hạn bài toán nhỏ nên chỉ cần for 3 vòng lồng nhau rồi đếm số tam giác cân.
```C++
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
```
### Subtask 2 ($1 \leq n \leq 10^5$), ($1 \leq a_i \leq 10^5$)
Gọi ```cnt[x]``` là mảng đếm số số cạnh có độ dài là ```x```, có 2 trường hợp:
- ```cnt[i] >= 3``` là trường hợp tam gíác đều nên số cách là $C(n, 3)$ 
- ```cnt[i] >= 2``` trường hợp tam giác cân bình thường trong đó có 2 cạnh có độ dài là ```i``` lúc này cạnh còn lại bị ràng buộc với điều kiện ```2 * i > c```. Thì lúc này chỉ cần đếm số số cạnh thỏa điều kiện trên.

Trong subtask này $a_i \leq 10^5$ nên chúng ta chỉ cần dùng mảng để đếm là được.
```C++
namespace sub2 {
    int cnt[N], pre[N];
    void solve(void) {
        rep(i, 1, n) cnt[a[i]]++;
        rep(i, 1, (int)1e5) pre[i] = pre[i - 1] + cnt[i];

        int res = 0;
        rep(i, 1, (int)1e5) {
            if (cnt[i] >= 3) res += comb3(cnt[i]); // comb3 là C(n, 3)

            if (cnt[i] >= 2) {
                // 2a > c
                int limit = min(2 * i - 1, (int)1e5);

                // -cnt[i] để không bị trùng TH tam giác đều 
                int c = pre[limit] - cnt[i]; 
                res += comb2(cnt[i]) * c; // comb2 là C(n, 2)
            }
        }

        cout << res;
    }
}
``` 
### Subtask 3 ($3 \leq n \leq 5.10^5$), ($1 \leq a_i \leq 10^9$)

Ý tưởng tương tự subtask 2 chúng ta sẽ optimize bằng map
```C++
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
```
## [H002] - Difference in Height
Bài này tính $\sum |a_i - a_j|$ thì giả sử $a_i > a_j$ thì ta chỉ cần lấy $a_i * i$ - $\sum a_j$ nên chúng ta chỉ cần sort lại là xong.
```C++
sort(a + 1, a + 1 + n);

rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
int res = 0;

// sum(1, i) là tổng từ a[i] từ vị trí 1 -> i
repd(i, n - 1, 1) res += a[i + 1] * i - sum(1, i); 
cout << res;
```
## [H001] - Tom's Currency
Bài này cứ push_back vào một cái vector xong rồi xóa các phần tử trùng
```C++
#define _unique(x) (x).resize(unique((x).begin(), (x).end()) - (x).begin());

sort(all(v));
_unique(v);
```
## Hashing: VQ44_FLOWERS
```C++
for (auto T : A) Hash[T]++;
    
vector <int> res;

// mỗi lần in ra thì cứ trừ k và trừ đi số lần xuất hiện    
if ((int)res.size() > k) {
    for (auto &T : Hash) if (T.second > 0 && k > 0) {
        res.push_back(T.first);
        T.second--;
        k--;
    }
}
    
while (k > 0) {
    for (auto &T : Hash) if (T.second > 0 && k > 0) {
        res.push_back(T.first);
        T.second--;
        k--;
    }
}
        
return res;
```
## Hashing: KiemKe
```C++
int count_distinct(const vector<string>& ids){
    map<string,int> Hash; 
    for (auto T : ids) Hash[T]++; // đếm số lần xuất hiện
    return Hash.size(); // trả về size là số phần tử khác nhau
}
```