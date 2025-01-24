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

#define ll long long
#define ull unsigned long long
#define lll __int128
#define pc __builtin_popcount
#define pr pair<int,int>
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define lb(x) x&-x
using namespace std;
const int maxn=3e5+10;
template<class T> void read(T &X)
{
    X=0;
    bool fu=0;
    char cr=getchar();
    while((cr<'0'||cr>'9')&&cr!='-') cr=getchar();
    if(cr=='-') cr=getchar(),fu=1;
    while(cr>='0'&&cr<='9') X=(X<<3)+(X<<1)+(cr^48),cr=getchar();
    X=(fu?-X:X);
}
int T,n,d[maxn];
vector<int> e[maxn];
pr a[maxn];
set<pr> s;
int main()
{
    read(T);
    while(T--)
    {
        read(n),s.clear();
        for(int i=1;i<=n;i++) d[i]=0,e[i].clear();
        for(int i=1,x,y;i<n;i++) read(x),read(y),s.insert(mp(x,y)),s.insert(mp(y,x)),d[x]++,d[y]++;
        for(int i=1;i<=n;i++) a[i]=mp(d[i],i);
        sort(a+1,a+n+1),reverse(a+1,a+n+1);
        int loc=1;
        while(loc+1<=n&&a[loc+1].x==a[1].x) loc++;
        int ans=a[1].x+a[2].x-2;
        if(loc==1)
        {
            for(int i=2;i<=n&&a[2].x==a[i].x;i++)
            {
                if(!s.count(mp(a[1].y,a[i].y)))
                {
                    ans=a[1].x+a[2].x-1;
                    break;
                }
            }
        }
        else if(loc>=2)
        {
            if(!s.count(mp(a[1].y,a[2].y))) ans=a[1].x+a[2].x-1;
            if(loc>=3&&0==s.count(mp(a[1].y,a[3].y))) ans=a[1].x+a[2].x-1;
            if(loc>=3&&0==s.count(mp(a[2].y,a[3].y))) ans=a[1].x+a[2].x-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}