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
#define MAXN 100005
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

ll tr[4*MAXN],cnt[4*MAXN][41];

void upd(int idx,int v,int l,int r,int i){
    if(l==r){
        tr[i]=0;
        for(int j=0;j<=40;j++){
            if(j==v)cnt[i][j]=1;
            else cnt[i][j]=0;
        }
        return;
    }
    int mid = ((l+r)>>1);
    if(idx<=mid)upd(idx,v,l,mid,2*i+1);
    else upd(idx,v,mid+1,r,2*i+2);
    ll ans=(tr[2*i+1]+tr[2*i+2]);
    ll cur = 0;
    for(int j=40;j>=0;j--){
        ans+=(cur*cnt[2*i+2][j]);
        cur+=cnt[2*i+1][j];
        cnt[i][j] = (cnt[2*i+1][j]+cnt[2*i+2][j]);
    }
    tr[i]=ans;
}

pair<ll,vector<ll>> qry(int ql,int qr,int l,int r,int i){
    if(ql>r || l>qr)return make_pair(0ll,vector<ll> (41));
    if(ql<=l && r<=qr){

        vector<ll> a(41);
        for(int j=0;j<=40;j++)a[j]=cnt[i][j];
        ll val = tr[i];
        return make_pair(val,a);
    }   

    int mid = (l+r)/2;

    auto x = qry(ql,qr,l,mid,2*i+1);
    auto y = qry(ql,qr,mid+1,r,2*i+2);

    ll ans = (x.F+y.F);
    ll crr = 0;
    for(int j=40;j>=0;j--){
        ans+=(crr*y.S[j]);
        crr+=x.S[j];
        x.S[j]+=y.S[j];
    }
    return {ans,x.S};
}

void solve(){
    int n,q;
    cin>>n>>q;

    f(n){
        int x;
        cin>>x;
        upd(i,x,0,n-1,0);
    }

    f(q){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            l--,r--;
            cout<<qry(l,r,0,n-1,0).F<<endl;
        }else{
            int idx,v;
            cin>>idx>>v;
            idx--;
            upd(idx,v,0,n-1,0);
        }
    }
}

int main(int argc, char* argv[]){
    fast;
    cout<<setprecision(PRECISION);
    int t=1;
    // cin>>t;
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