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

void solve(){
    int n,m;
    cin>>n>>m;
    vector<ll> coins(n);
    f(n)cin>>coins[i];
    vector<vector<int>> adj(n), adj_rev(n);
    vector<pair<int,int>> edges(m);


    f(m){
        int u,v;
        cin>>u>>v;
        u--,v--;
        edges[i] = {u,v};
        adj[u].pb(v);
        adj_rev[v].pb(u);
    }

    vector<bool> vis(n,false);
    vector<int> order;

    function<void(int)> dfs1 = [&](int u){
        vis[u]=true;
        for(int v:adj[u]){
            if(!vis[v]){
                dfs1(v);
            }
        }
        order.pb(u);
    };

    f(n){
        if(!vis[i]){
            dfs1(i);
        }
    }

    reverse(all(order));

    vector<int> comp(n,-1);
    int c=0;

    vll sums;


    function<void(int,int)> dfs2 = [&](int u,int c){
        comp[u]=c;
        sums[c]+=coins[u];
        for(int v:adj_rev[u]){
            if(comp[v]==-1){
                dfs2(v,c);
            }
        }
    };

    for(int u:order){
        if(comp[u]==-1){
            sums.push_back(0);
            dfs2(u,c++);
        }
    }

    vector<vector<int>> dag(c);


    for(auto e:edges){
        if(comp[e.F]!=comp[e.S]){
            dag[comp[e.F]].push_back(comp[e.S]);
        }
    }

    vector<ll> dp(c,-1);
    function<ll(int)> rec = [&](int node){
        if(dp[node]!=-1)return dp[node];
        ll ans =sums[node];
        for(auto ch:dag[node]){
            ans = max(ans,rec(ch)+sums[node]);
        }
        return dp[node]=ans;
    };

    ll ans = 0;
    for(int node=0;node<c;node++){
        ans = max(ans,rec(node));
    }
    cout<<ans;
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
