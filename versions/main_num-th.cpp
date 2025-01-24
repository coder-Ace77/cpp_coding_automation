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
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb push_back
#define F first
#define S second
#define strend string::npos
#define mod 1000000007
#define MAXN 200005
#define inf (int)1e9
#define infll (ll)1e18
#define PRECISION 6
#define endl '\n'
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define debug(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

template<typename... Args>
void debug_impl(const char* names, Args&&... args) {
    cout << names << " = ";
    ((cout << args << " "), ...); 
    cout << endl;
}

template <typename T>
class Array{
    public:
    vector<T> v,pre;

    Array() : v(), pre() {} // Default constructor    

    Array(int n){
        v.resize(n);
    }

    Array(int n,T vl){
        v.resize(n,vl);
    }

    Array(vector<T> a){
        v=a;
    }

    T& operator [](int ind){
        return v.at(ind);
    }

    int size(){
        return v.size();
    } 

    bool empty(){
        return v.empty();
    }

    void push_back(T val){
        v.push_back(val);
    }

    void sort(function<bool(T,T)> cmp = less<T>()){
        std::sort(v.begin(),v.end());
    }

    T max(){
        return (*max_element(v.begin(),v.end()));
    }

    T min(){
        return (*min_element(v.begin(),v.end()));
    }

    T sum(){
        return accumulate(v.begin(),v.end(),0ll);
    }

    void build(){
        pre.resize(v.size(),0);
        T s=0;
        for(int i=0;i<pre.size();i++){
            if(i==0)pre.at(i)=v.at(i);
            else pre.at(i)=pre.at(i-1)+v.at(i);
        }

    }

    T qry(int l,int r){
        if(l==0)return pre.at(r);
        else return pre.at(r)-pre.at(l-1);
    }

    void clear(){
        v.clear();
    }

};

template <typename T>
typename std::enable_if<!std::is_class<T>::value>::type debugv(const T& t) {
    std::cout << t << " ";
}

void debugv(const std::string& t) {
    std::cout << "\"" << t << "\" ";
}

template <typename T, size_t N>
void debugv(const T (&arr)[N]) {
    std::cout << "[ ";
    for (const auto& elem : arr) {
        debugv(elem);
    }
    std::cout << "] ";
}

template <typename T>
typename std::enable_if<std::is_class<T>::value>::type debugv(const T& container) {
    std::cout << "[ ";
    for (const auto& elem : container) {
        debugv(elem);
    }
    std::cout << "]";
}

template <typename K, typename V>
void debugv(const std::map<K, V>& m) {
    std::cout << "{ ";
    for (const auto& pair : m) {
        std::cout << "(";
        debugv(pair.first);
        std::cout << ": ";
        debugv(pair.second);
        std::cout << ") ";
    }
    std::cout << "} ";
}

template <typename T>
void debugv(const Array<T>& arr){
    debugv(arr.v);
}

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
    k--;
    if(n%2==0){
        cout<<1+k%n;
    }else{
        ll i = (2*k)/(n-1);
        cout<<1+(k+i)%n;
    }

}

int main(int argc, char* argv[]){
    fast;
    cout<<setprecision(PRECISION);
    int t=1;
    cin>>t;
    while(t--){
        solve();
        if (argc > 1 && string(argv[1]) == "print_dollar"){
            cout << "|"<<endl;
        } else {
            cout << endl;
        }
    }
    return 0;
}