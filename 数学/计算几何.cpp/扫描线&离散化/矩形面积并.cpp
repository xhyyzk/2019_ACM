//poj 1151
#include <bits/stdc++.h>'
using namespace std;
const int MAXN = 300;
int mark[MAXN << 2];
double sum[MAXN << 2];
double hash_[MAXN];

struct seg {
    double l, r, h;
    int d;
    seg(){}
    seg(double x1, double x2, double h, int c):l(x1), r(x2), h(h), d(c){}
    bool operator < (const seg &a) const {
        return h < a.h;
    }
}s[MAXN];

void pushup(int n, int l, int r) {
    if(mark[n]) sum[n] = hash_[r + 1] - hash_[l];
    else if(l == r) sum[n] = 0;
    else sum[n] = sum[n << 1] + sum[n << 1 | 1];
}

void update(int L, int R, int d, int n, int l, int r) {
    if(L <= l && r <= R) {
        mark[n] += d;
        pushup(n, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= mid) update(L, R, d, n << 1, l, mid);
    if(R > mid) update(L, R, d, n << 1 | 1, mid + 1, r);
    pushup(n, l, r);
}

int search_(double key, double* x, int n) {
    int l = 0, r = n - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(x[mid] == key) return mid;
        if(x[mid] > key) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int n, num = 0;
double x1, x2, y, y2;

int main() {
    while(cin >> n && n) {
        int k = 0;
        for(int i = 0; i < n; ++i) {
            cin >> x1 >> y >> x2 >> y2;
            hash_[k] = x1;
            s[k++] = seg(x1, x2, y, 1);
            hash_[k] = x2;
            s[k++] = seg(x1, x2, y2, -1);
        }
        sort(hash_, hash_ + k);
        sort(s, s + k);
        int m = 1;
        for(int i = 1; i < k; ++i) {
            if(hash_[i] != hash_[i - 1]) hash_[m++] = hash_[i];
        }
        double ans = 0;
        for(int i = 0; i < k; ++i) {
            int L = search_(s[i].l, hash_, m);
            int R = search_(s[i].r, hash_, m) - 1;
            update(L, R, s[i].d, 1, 0, m-1);
            ans += sum[1] * (s[i+1].h - s[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++num,ans);
    }
    return 0;
}



//精简版
#include<bits/stdc++.h>
using namespace std;
#define lson i<<1,l,m
#define rson i<<1|1,m+1,r
const int maxn=222;

double x[maxn];
struct node {
    double l,r,h;//左右坐标，高度
    int d;//标记上位边还是下位边
    node() {}
    node(double l,double r,double h,int d):l(l),r(r),h(h),d(d) {}
    bool operator < (const node &a)const {
        return h<a.h;
    }
} line[maxn];

int cnt[maxn<<2];
double sum[maxn<<2];

void pushup(int i,int l,int r)
{
   if(cnt[i])
       sum[i]=x[r+1]-x[l];
   else
       sum[i]=sum[i<<1]+sum[i<<1|1];
}

void update(int ql,int qr,int v,int i,int l,int r)
{
    if(ql<=l && qr>=r) {
       cnt[i]+=v;
       pushup(i,l,r);
       return ;
    }
    int m=(l+r)>>1;
    if(ql<=m)update(ql,qr,v,lson);
    if(qr>m)update(ql,qr,v,rson);
    pushup(i,l,r);
}

int main() {
    int q;
    int kase=0;
    while(cin>>q&&q) {
        memset(cnt,0,sizeof(cnt));//相当于build
        memset(sum,0,sizeof(sum));//相当于build
        int n=0,m=0;
        for(int i=1; i<=q; i++){
            double x1,y1,x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            x[++n]=x1;
            x[++n]=x2;
            line[++m]=node(x1,x2,y1,1);
            line[++m]=node(x1,x2,y2,-1);
        }
        sort(x+1,x+1+n);
        sort(line+1,line+1+m);
        int k=1;
        k=unique(x+1,x+n+1)-x-1;//直接用STL中的unique函数。
        double ans=0.0;
        for(int i=1; i<m; i++){

            int l=lower_bound(x+1,x+k+1,line[i].l)-x;
            int r=lower_bound(x+1,x+k+1,line[i].r)-x;
            r--;
            if(l<=r)update(l,r,line[i].d,1,1,k-1);
            ans+=sum[1]*(line[i+1].h-line[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n",++kase,ans);
    }
}
