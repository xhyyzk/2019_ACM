bzoj 2618
给出n个多边形每个点的坐标，求它们的重合面积

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps = 1e-8;
const int inf = 1e18;

int n, m, cnt, tot;
double ans;
struct P{double x,y;}p[1005], a[1005];
struct L{P a,b;double slop;}l[1005], q[1005];
P operator - (P a,P b) {
    P t;
    t.x=a.x-b.x;
    t.y=a.y-b.y;
    return t;
}

//叉乘
double operator * (P a, P b) {
    return a.x*b.y - a.y*b.x;
}

//极角排序
bool operator < (L a, L b)
{
    if(a.slop != b.slop)return a.slop < b.slop;
    return (a.b-a.a)*(b.b-a.a) > 0;
}

//求两直线相交的交点
P inter(L a,L b) {
    double k1, k2, t;
    k1 = (b.b-a.a)*(a.b-a.a);
    k2 = (a.b-a.a)*(b.a-a.a);
    t = k1 / (k1+k2);
    P ans;
    ans.x = b.b.x + (b.a.x-b.b.x)*t;
    ans.y = b.b.y + (b.a.y-b.b.y)*t;
    return ans;
}

bool jud(L a, L b, L t) {
    P p = inter(a, b);
    return (t.b-t.a)*(p-t.a)<0;
}

//半平面交
void hpi() {
    sort(l+1, l+cnt+1);
//  for(int i=1;i<=cnt;i++)
//      cout<<l[i].a.x<<' '<<l[i].a.y<<' '<<l[i].b.x<<' '<<l[i].b.y<<endl;
    int L=1, R=0;  //模拟双端队列
    tot=0;
    for(int i = 1; i <= cnt; i++) { //去重
        if(l[i].slop != l[i-1].slop) tot++;
        l[tot] = l[i];
    }
    cnt = tot;
    tot = 0;
    q[++R] = l[1];
    q[++R] = l[2];
    for(int i = 3; i <= cnt; i++) {
        while(L<R && jud(q[R-1], q[R], l[i])) R--;
        while(L<R && jud(q[L+1], q[L], l[i])) L++;
        q[++R] = l[i];
    }
    while(L<R && jud(q[R-1], q[R], q[L])) R--;
    while(L<R && jud(q[L+1], q[L], q[R])) L++;
    q[R+1] = q[L];
    for(int i = L; i <= R; i++)
        a[++tot] = inter(q[i], q[i+1]);
}

//计算多边形的面积
void getans() {
    if(tot < 3) return;
    a[++tot] = a[1];
    for(int i = 1; i <= tot; i++)
        ans += a[i]*a[i+1];
    ans = fabs(ans)/2;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &m);
        for(int j = 1; j <= m; j++)
            scanf("%lf%lf", &p[j].x, &p[j].y);
        p[m+1] = p[1];
        for(int j = 1; j <= m; j++)
            l[++cnt].a = p[j],l[cnt].b = p[j+1];
    }
    for(int i = 1; i <= cnt; i++)
        l[i].slop = atan2(l[i].b.y-l[i].a.y, l[i].b.x-l[i].a.x);
    hpi();
    getans();
    printf("%.3lf",ans);
    return 0;
}


/*
2
6
-2 0
-1 -2
1 -2
2 0
1 2
-1 2
4
0 -3
1 -1
2 2
-1 0
*/
