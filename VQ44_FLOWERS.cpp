/*###Begin banned keyword - each of the following line if appear in code will raise error. regex supported
sort
stable_sort
partial_sort
partial_sort_copy
sort_heap
set
multi_set
merge
###End banned keyword*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;


vector<int> get_ans(const vector<int>& A,int K){
	map<int,int> Hash;

    for (auto T : A) Hash[T]++;
    
    vector <int> res;
    
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
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	cin >> n >> k;
	
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	vector<int> ans = get_ans(a,k);
	
	for (const int& x: ans) cout << x << ' ';
	return 0;
}