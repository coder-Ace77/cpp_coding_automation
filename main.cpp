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
#define debug(...) do {cerr << "[DEBUG] " << __LINE__ << ": " << #__VA_ARGS__ << " = "; _debug(__VA_ARGS__);} while(0)
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

template<typename T1, typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>&p){return os << "(" << p.first << "," << p.second << ")";}
template<typename T>
ostream& operator<<(ostream& os,const vector<T>&v){os << "[";for(int i = 0; i < v.size(); i++){if(i) os << " ";os << v[i];}return os << "]";}
template<typename T>
ostream& operator<<(ostream& os,const set<T>& s){os << "{";bool first = true;for(auto& x:s){if(!first) os << " ";first = false;os << x;}return os << "}";}
template<typename T>
ostream& operator<<(ostream& os,const multiset<T>&s){os << "{";bool first = true;for(auto& x:s){if(!first) os << " ";first = false;os << x;}return os << "}";}
template<typename T1, typename T2>
ostream& operator<<(ostream& os,const map<T1,T2>& mp){os << "{";bool first = true;for(auto& x:mp){if(!first) os << " ";first = false;os << x.first << ":" << x.second;}return os << "}";}
void _debug(){cerr << endl;}
template<typename T, typename... V>
void _debug(T t, V... v){cerr << t;if(sizeof...(v))cerr << "@ ";_debug(v...);}

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

class NumberTheory{
    public:
    static long long binpow(long long a, long long b, long long m){
        a%=m;
        long long ans = 1;
        while(b>0){
            if (b & 1)ans=ans*a%m;
            a=a*a%m;
            b>>=1;
        }
        return ans;
    }

    static long long inv(long long a,long long m){
        return binpow(a,m-2,m);
    }

    static int gcd (int a, int b) {
        return (b ? gcd (b, a % b) : a);
    }

    static int lcm(int a,int b){
        return a/gcd(a, b)*b;
    }

    static int extended_eucledian(int a, int b, int& x, int& y){
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int x1, y1;
        int d = extended_eucledian(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }



    static vector<int> sieve(int n){
        vector<int> sv(n+1,true);
        sv[0]=sv[1]=false;
        for (int i=2;i*i<=n;i++){
            if(sv[i]){
                for (int j=i*i;j<=n;j+=i)
                    sv[j] = false;
            }
        }
        return sv;
    }

    static vector<int> spf(int n){
        vector<int> sv(n+1);
        f(n+1)sv[i]=i;
        for(int i=2;i<=n;i++){
            for(int j=2*i;j<=n;j+=i){
                if(sv[j]==j){
                    sv[j]=i;
                }
            }
        }
        return sv;
    }

    static int phi(int n){
        int ans = n;
        for(int i=2; i*i<=n;i++){
            if (n%i==0){
                while(n%i==0)n/=i;
                ans-=ans/i;
            }
        }
        if(n>1)ans-=ans/n;
        return ans;
    }

    static vector<int> phi_1_to_n(int n){
        vector<int> phi(n+1);
        for (int i=0;i<=n;i++)phi[i]=i;
        for (int i=2;i<=n;i++){
            if(phi[i]==i){
                for (int j=i;j<=n;j+=i)
                    phi[j]-=phi[j]/i;
            }
        }
        return phi;
    }
};


void solve(){
    int n,k;
    cin>>n>>k;
    vi v(n);
    f(n)cin>>v[i];
    const int MAX = 1e6+5;
    auto sv = NumberTheory::spf(MAX);
    map<map<int,int>,int> mp;
    long long ans=0;
    for(int i=0;i<n;i++){
        map<int,int> fac;
        int temp = v[i];
        while(temp>1){
            int ff = sv[temp];
            fac[ff]++;
            temp/=ff;
        }
        map<int,int> trace;
        map<int,int> cmp;

        for(auto x:fac){
            if(x.second%k!=0){
                trace.insert({x.first,x.second%k});
                cmp.insert({x.first,k-x.second%k});
            }
        }
        ans+=mp[cmp];
        mp[trace]+=1;
    }
    cout<<ans;
}

int main(int argc, char* argv[]) {
    fast;cout << fixed << setprecision(PRECISION);
    int t = 1;
    for(int i = 1; i <= t; i++){
        solve();
        if (argc > 1 && string(argv[1]) == "print_dollar") cout << "|" << endl;
        else cout << endl;
    }
    return 0;
}