/*
https://www.spoj.com/problems/GSS1/
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define F first
#define S second
#define ALL(a) (a).begin(),(a).end()
#define MAXX 100005
#define int long long int
#define INT_BITS 32

struct seg{
    int pre,suf,mxsum,sum;
};
seg st[4*MAXX];
vector<int> a;
seg ans;

void combine(int x)
{
    st[x].pre = max(st[2*x+1].pre , st[2*x+1].sum + st[2*x+2].pre);
    st[x].suf = max(st[2*x+2].suf , st[2*x+2].sum + st[2*x+1].suf);
    st[x].mxsum = max({st[2*x+1].mxsum,st[2*x+2].mxsum,st[2*x+1].suf+st[2*x+2].pre});
    st[x].sum = st[2*x+1].sum + st[2*x+2].sum;
}

void build(int x,int lx,int rx)
{
    if(rx-lx == 1)
    {
        if(lx < a.size())
        {
            st[x].sum = a[lx];
            st[x].mxsum = a[lx];
            st[x].pre = a[lx];
            st[x].suf = a[lx];
        }
        return;
    }
    int m = (lx+rx)/2;
    build(x*2+1,lx,m);
    build(x*2+2,m,rx);
    combine(x);
}
int MIN_VAL = -1e9;
seg range(int l,int r,int x,int lx,int rx)
{
    seg ans;
    ans.mxsum = MIN_VAL;
    ans.sum = ans.mxsum;
    ans.pre = ans.sum;
    ans.suf = ans.sum;
    if(l >= rx or lx >= r)
        return ans;
    if(lx >= l and rx <= r)
        return st[x];
    int m = (lx+rx)/2;
    if(l >= m)
    {
        return range(l,r,x*2+2,m,rx);
    }
    else if(r < m) return range(l,r,x*2+1,lx,m);
    seg left = range(l,r,x*2+1,lx,m);
    seg right = range(l,r,x*2+2,m,rx);
    ans.pre = max(left.pre , left.sum + right.pre);
    ans.suf = max(right.suf , right.sum + left.suf);
    ans.mxsum = max({left.mxsum,right.mxsum,left.suf+right.pre});
    ans.sum = left.sum + right.sum;
    return ans;
}

void solve(void)
{
    int n,m;
    cin >> n;
    for(int i = 0 ; i < n ; i++)
    {
        int x;
        cin >> x;
        a.pb(x);
    }
    build(0,0,n);
    cin >> m;
    while(m--)
    {
        int l,r;
        cin >> l >> r;
        l--;
        seg temp = range(l,r,0,0,n);
        if(temp.mxsum != MIN_VAL)
            cout << temp.mxsum << "\n";
        else cout << a[l] << "\n";
        
    }
    
    
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    //cin >> T;
    while(T--)
        solve();

    return 0;
}
