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
ostream& operator<<(ostream& os,const vector<T>&v){os << "[";for(int i = 0; i < v.size(); i++){if(i) os << " ";os << v[i];}return os << "]";}
template<typename T1, typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>&p){return os << "(" << p.first << "," << p.second << ")";}
template<typename T>
ostream& operator<<(ostream& os,const set<T>& s){os << "{";bool first = true;for(auto& x:s){if(!first) os << " ";first = false;os << x;}return os << "}";}
template<typename T>
ostream& operator<<(ostream& os,const multiset<T>&s){os << "{";bool first = true;for(auto& x:s){if(!first) os << " ";first = false;os << x;}return os << "}";}
template<typename T1, typename T2>
ostream& operator<<(ostream& os,const map<T1,T2>& mp){os << "{";bool first = true;for(auto& x:mp){if(!first) os << " ";first = false;os << x.first << ":" << x.second;}return os << "}";}
void _debug(){cerr << endl;}
template<typename T, typename... V>
void _debug(T t, V... v){cerr << t;if(sizeof...(v))cerr << ", ";_debug(v...);}

template <unsigned int MOD>
struct ModInt {
    using uint = unsigned int;
    using ull = unsigned long long;
    using M = ModInt;

    uint v;

    ModInt(ll _v = 0) { set_norm(_v % MOD + MOD); }
    M& set_norm(uint _v) { v = (_v < MOD) ? _v : _v - MOD; return *this; }

    explicit operator bool() const { return v != 0; }
    M operator+(const M& a) const { return M().set_norm(v + a.v); }
    M operator-(const M& a) const { return M().set_norm(v + MOD - a.v); }
    M operator*(const M& a) const { return M().set_norm(ull(v) * a.v % MOD); }
    M operator/(const M& a) const { return *this * a.inv(); }
    M& operator+=(const M& a) { return *this = *this + a; }
    M& operator-=(const M& a) { return *this = *this - a; }
    M& operator*=(const M& a) { return *this = *this * a; }
    M& operator/=(const M& a) { return *this = *this / a; }
    M operator-() const { return M() - *this; }
    M& operator++(int) { return *this = *this + 1; }
    M& operator--(int) { return *this = *this - 1; }

    M pow(ll n) const {
        if (n < 0) return inv().pow(-n);
        M x = *this, res = 1;
        while (n) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    M inv() const {
        ll a = v, b = MOD, p = 1, q = 0, t;
        while (b != 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(p -= t * q, q);
        }
        return M(p);
    }

    bool operator==(const M& a) const { return v == a.v; }
    bool operator!=(const M& a) const { return v != a.v; }
    friend ostream& operator<<(ostream& os, const M& a) { return os << a.v; }
    static uint get_mod() { return MOD; }
};
using Mint = ModInt<1000000007>;

template <typename T>
class SegTree{
    void build(vector<T> &arr,int l,int r,int i){
        if(l==r){
            tree[i]=arr[l];
            return;
        }
        int mid = (l+r)/2;
        build(arr,l,mid,2*i+1);
        build(arr,mid+1,r,2*i+2);
        tree[i]=fn(tree[2*i+1],tree[2*i+2]);
    }

    void upd(int ind,int val,int l,int r,int i){
        if(l==r){
            tree[i]=val;
            return;
        }
        int mid = (l+r)/2;
        if(ind<=mid)upd(ind,val,l,mid,2*i+1);
        else upd(ind,val,mid+1,r,2*i+2);
        tree[i]=fn(tree[2*i+1],tree[2*i+2]);
    }

    T qry(int ql,int qr,int l,int r,int i){
        if(ql>r || l>qr)return def;
        if(ql<=l && r<=qr)return tree[i];
        int mid = (l+r)/2;
        return fn(qry(ql,qr,l,mid,2*i+1),qry(ql,qr,mid+1,r,2*i+2));
    }

    public:
    int n;
    function<T(T,T)> fn;
    vector<T> tree;
    T def;
    SegTree(int arr_size,function<T(T,T)> op,T d=0){
        tree.resize(4*arr_size);
        n=arr_size;
        fn = op;
        def=d;
    }
    void build(vector<T> &arr){
        build(arr,0,arr.size()-1,0);
    }

    void upd(int ind,T val){
        upd(ind,val,0,n-1,0);
    }

    T qry(int ql,int qr){
        return qry(ql,qr,0,n-1,0);
    } 
};


void solve(){
    int n;
    cin>>n;
    
    vi v(n);
    f(n)cin>>v[i];

    bool ok = true;

    function<vector<int>(int,int)> rec = [&](int l,int r){
        if(l==r){
            vector<int> a{0,v[l],v[l]};
            return a;
        }
        int mid = (l+r)/2;
        auto op1 = rec(l,mid);
        auto op2 = rec(mid+1,r);

        if(op1[0]==-1 || op2[0]==-1){
            vector<int> a{-1,-1,-1};
            return a;
        }
        // ans , min , max
        if(op1[2]<op2[1]){
            vector<int> a{op1[0]+op2[0],min(op1[1],op2[1]),max(op1[2],op2[2])};
            return a;
        }else if(op2[2]<op1[1]){
            vector<int> a{op1[0]+op2[0]+1,min(op1[1],op2[1]),max(op1[2],op2[2])};
            return a;
        }else{
            vector<int> a{-1,-1,-1};
            return a;
        }
    };
    cout<<rec(0,n-1)[0];
}

int main(int argc, char* argv[]) {
    fast;cout << fixed << setprecision(PRECISION);
    int t = 1;cin >> t;
    for(int i = 1; i <= t; i++){
        solve();
        if (argc > 1 && string(argv[1]) == "print_dollar") cout << "|" << endl;
        else cout << endl;
    }
    return 0;
}