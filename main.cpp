#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <unordered_map>
#include <set>
#include <stack>
#include <cstring>
#include <numeric>
#include <bitset>
#include <iomanip>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define f(n) for(int i = 0; i < n; i++)
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define ceil(a, b) ((a + b - 1) / b)
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define all(x) (x).begin(), (x).end()
#define sz(x) static_cast<int>((x).size())
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define F first
#define S second
#define strend string::npos
#define mod 1000000007
#define MAXN 200005
#define inf 1e9
#define infll 1e18
#define PRECISION 6
#define endl '\n'
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#define debug(...) do {cerr << #__VA_ARGS__ << " = ";_debug(__VA_ARGS__);}while(0)

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

template<typename T> 
ostream& operator<<(ostream& os,const vector<T>&v){os<<"[";for(int i=0;i<v.size();i++){if(i)os<<" ";os<<v[i];}return os<<"]";}
template<typename T1, typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>&p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename T>
ostream& operator<<(ostream& os,const set<T>& s){os<<"{";bool first=true;for(auto& x:s){if(!first)os<<" ";first=false;os<<x;}return os<<"}";}
template<typename T>
ostream& operator<<(ostream& os,const multiset<T>&s){os<<"{";bool first=true;for(auto& x:s){if(!first)os<<" ";first=false;os<<x;}return os<<"}";}
template<typename T1, typename T2>
ostream& operator<<(ostream& os,const map<T1,T2>& mp){os<<"{";bool first=true;for(auto& x:mp){if(!first)os<<" ";first=false;os<<x.first<<":"<<x.second;}return os<<"}";}
void _debug(){cerr<<endl;}
template<typename T, typename... V>
void _debug(T t,V... v){cerr<<t;if(sizeof...(v))cerr<<", ";_debug(v...);}

void solve(){
    
}

int main(int argc, char* argv[]) {
    fast;cout<<fixed<<setprecision(PRECISION);  
    int t = 1;cin >> t;
    for(int i=1;i<=t;i++){
        solve();
        if (argc > 1 && string(argv[1]) == "print_dollar")cout << "|" << endl;  
        else cout << endl;
    }
    return 0;
}