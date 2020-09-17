/*
https://codeforces.com/contest/380/problem/C
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define F first
#define S second
#define ALL(a) (a).begin(),(a).end()
#define MAXX 1000005
#define int long long int
#define INT_BITS 32


struct seg{
    int correct=0,open=0,close=0;
};
seg st[4*MAXX];


void combine(int x)
{
    int temp = min(st[x*2+1].open, st[x*2+2].close);
    st[x].correct = st[x*2+1].correct + st[x*2+2].correct + temp*2;
    st[x].open = st[x*2+1].open + st[x*2+2].open - temp;
    st[x].close = st[x*2+1].close + st[x*2+2].close - temp;
}
string a;
void build(int x,int lx,int rx)
{
    if(rx-lx == 1)
    {
        if(lx < a.size())
        {
            if(a[lx] == ')')
                st[x].close = 1;
            else st[x].open = 1;
        }
        return;
    }
    int m = (lx+rx)/2;
    build(x*2+1,lx,m);
    build(x*2+2,m,rx);
    combine(x);
}
seg range(int l,int r,int x,int lx,int rx)
{
    seg ans;
    ans.close = 0;
    ans.open = 0;
    ans.correct = 0;
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
    int temp = min(left.open, right.close);
    ans.correct = left.correct + right.correct + temp*2;
    ans.open = left.open + right.open - temp;
    ans.close = left.close + right.close - temp;
    return ans;
}

void solve(void)
{
    int n,m;
    
    cin >> a;
    n = a.size();
    build(0,0,n);
    cin >> m;
    while(m--)
    {
        int l,r;
        cin >> l >> r;
        l--;
        seg temp = range(l,r,0,0,n);
        cout << temp.correct << "\n";
        //cout << endl;
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
