#include<iostream>
#include<cmath>
#include<vector>
#include<unordered_set>
#include<algorithm>
#include<string>
#include<map>
#include<list>
#include<queue>
#include<unordered_map>
#include<set>
#include<stack>
#include<cstring>
#include<numeric>
#include<bitset>
#include<iomanip>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define f(n) for(int i=0;i<n;i++)
#define fr(i,a,b) for(int i=a;i<=b;i+=1)
#define ceil(a,b) (a+b-1)/b
#define ll long long int
#define vi vector<int>
#define vll vector<long long int>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define sum(x) accumulate(x.begin(),x.end(),0ll)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb(x) push_back(x)
#define F first
#define S second
#define strend string::npos
#define mod 1000000007
#define MAXN 100005
#define inf (int)1e9
#define infll (ll)1e18
#define PRECISION 6
#define endl '\n'
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define debug(x) cout<<#x<<'='<<x<<endl;
#define debug2(x,y) cout<<#x<<'='<<x<<','<<#y<<'='<<y<<endl;
#define debug3(x,y,z) cout<<#x<<'='<<x<<','<<#y<<'='<<y<<','<<#z<<'='<<z<<endl;

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
// use greater_equal, less_equal for multiset

template <unsigned int MOD>
struct ModInt {
    using uint = unsigned int;
    using ull = unsigned long long;
    using M = ModInt;

    uint v;

    ModInt(ll _v = 0) { set_norm(_v % MOD + MOD); }
    M& set_norm(uint _v) {  //[0, MOD * 2)->[0, MOD)
        v = (_v < MOD) ? _v : _v - MOD;
        return *this;
    }

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
using Mint = ModInt<1000000007>; // change here

void debugv(vector<int> v){for(auto x:v)cout<<x<<' ';cout<<endl;}
void debugv(vector<ll> v){for(auto x:v)cout<<x<<' ';cout<<endl;}
void debugv(vector<pii> v){for(auto x:v)cout<<x.F<<','<<x.S<<' ';cout<<endl;}
void debugv(vector<pll> v){for(auto x:v)cout<<x.F<<','<<x.S<<' ';cout<<endl;}
void debugv(vector<string> v){for(auto x:v)cout<<x<<' ';cout<<endl;}
void debugv(vector<vector<int>> v){for(auto x:v)debugv(x);}

vector<pii> adj[MAXN];

void solve(){
    int n,m;
    cin>>n>>m;
    f(m){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        adj[u].push_back({v,w});
    }
    priority_queue<pair<ll,int>> pq;

    vll dist(n,1e18),ways(n);
    vi mnf(n),mxf(n),vis(n);

    dist[0]=0;
    ways[0]=1;
    pq.push({0ll,0});

    while(!pq.empty()){
        int node = pq.top().S;
        pq.pop();

        if(vis[node])continue;
        vis[node]=true;

        for(auto [ch,wt]:adj[node]){
            ll new_cst = dist[node]+wt;
            if(new_cst==dist[ch]){
                ways[ch]+=ways[node];
                ways[ch]%=mod;
                mnf[ch] = min(mnf[ch],mnf[node]+1);
                mxf[ch] = max(mxf[ch],mxf[node]+1);
            }else if(new_cst<dist[ch]){
                dist[ch]=new_cst;
                ways[ch]=ways[node];
                mnf[ch] = mnf[node]+1;
                mxf[ch] = mxf[node]+1;
                pq.push({-dist[ch],ch});
            }
        }
    }
    cout<<dist[n-1]<<" "<<ways[n-1]<<" "<<mnf[n-1]<<" "<<mxf[n-1];
}

int main(){
    fast;
    cout<<setprecision(PRECISION);
    int t=1;
    // cin>>t;
    while(t--){
        solve();
        // cout<<"$"<<endl;
    }
return 0;
}