#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;cin>>n;
	vector<int> a(n);
	for (int i=0;i<n;i++)
		cin>>a[i];
	vector<int> x;
	priority_queue<int,vector<int>,greater<>> y;
	for (auto i:a)
		if (x.empty()||i>=x.back())
			x.emplace_back(i);
		else{
			while (!x.empty()&&i<x.back())
				y.emplace(x.back()+1),
				x.pop_back();
			x.emplace_back(i);
		}
	while (!y.empty()){
		int t=y.top();
		y.pop();
		while (!x.empty()&&t<x.back())
			y.emplace(x.back()+1),
			x.pop_back();
		x.emplace_back(t);
	}
	for (int i=0;i<n;i++)
		cout<<x[i]<<' ';
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while (t--) solve();
	return 0;
}
