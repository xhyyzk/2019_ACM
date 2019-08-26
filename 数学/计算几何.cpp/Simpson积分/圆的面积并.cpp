spoj The area of the union of circles
//给出n个圆的圆心坐标和半径，求他们的面积并

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 10;
#define exp 1e-6

int n;

struct Point //点
{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    bool operator<(const Point &b)const { return x==b.x?y<b.y:x<b.x; }
};

struct Circle //圆
{
    Point o;
    double r;
    Circle(){}
    Circle(Point _o,double _r):o(_o),r(_r){}
}circles[MAXN],tmp[MAXN];

bool cmp2(Circle a,Circle b)
{
    return a.r>b.r;
}

bool cmp(Circle a,Circle b)
{
    if(fabs(a.o.x-a.r-b.o.x+b.r) <= exp) return a.o.x+a.r<b.o.x+b.r;
    return a.o.x-a.r<b.o.x-b.r;
}

pair<double,double>intervals[MAXN];
int tot=0;
int st,ed;

bool check(Circle a,Circle b) //检查b是否被套在a里面
{
    return (a.o.x-b.o.x)*(a.o.x-b.o.x)+(a.o.y-b.o.y)*(a.o.y-b.o.y)<=(a.r-b.r)*(a.r-b.r);
}

void prework()
{
    sort(circles+1,circles+n+1,cmp2);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        bool flag=true;
        for(int j=1;j<=cnt;j++)
            if(check(tmp[j],circles[i]))
            {
                flag=false;
                break;
            }
        if(flag) tmp[++cnt]=circles[i];
    }
    n=cnt;
    for(int i=1;i<=n;i++)
        circles[i]=tmp[i];
}

void getCircleIntersec(Circle a,double x) //求x=x这条平行于y轴的直线穿过圆a的长度
{
    intervals[++tot]=make_pair(a.o.y-sqrt(a.r*a.r-(x-a.o.x)*(x-a.o.x)),a.o.y+sqrt(a.r*a.r-(x-a.o.x)*(x-a.o.x)));
}

double f(double x) //求扫描线x被圆覆盖部分的长度
{
    tot=0;
    for(int i=st;i<=ed;i++)
        if(x<circles[i].o.x+circles[i].r&&x>circles[i].o.x-circles[i].r)
            getCircleIntersec(circles[i],x);
    sort(intervals+1,intervals+tot+1);
    double ans=0,start=-1e12,end=-1e12; //!!!!!!!!!!!
    for(int i=1;i<=tot;i++)
    {
        if(intervals[i].first>=end)
        {
            ans+=end-start;
            start=intervals[i].first;
            end=intervals[i].second;
        }
        else end=max(end,intervals[i].second);
    }
    ans+=end-start;
    return ans;
}

double calc(double len,double fL,double fM,double fR) //求长度为len的[L,R]区间，中点为M的Simpson近似面积
{
    return (fL+4*fM+fR)*len/6;
}

double Simpson(double L,double M,double R,double fL,double fM,double fR,double sqr) //Simpson积分求区间[L,R]的面积并,f(L)=L,f(R)=R,f(M)=M,把[L,R]当成整体来拟合得到的面积是sqr
{
    double M1=(L+M)/2,M2=(M+R)/2;
    double fM1=f(M1),fM2=f(M2);
    double g1=calc(M-L,fL,fM1,fM),g2=calc(R-M,fM,fM2,fR);
    if(fabs(sqr-g1-g2) <= exp) //把当前区间分成2半再拟合得到的答案差别很小，就不再递归下去了
        return g1+g2;
    return Simpson(L,M1,M,fL,fM1,fM,g1)+Simpson(M,M2,R,fM,fM2,fR,g2);
}

int main()
{
    double ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf%lf",&circles[i].o.x,&circles[i].o.y,&circles[i].r);
    prework();
    sort(circles+1,circles+n+1,cmp);
    for(int i=1,j;i<=n;i++)
    {
        double L=circles[i].o.x-circles[i].r,R=circles[i].o.x+circles[i].r;
        for(j=i+1;j<=n;j++)
        {
            if(circles[j].o.x-circles[j].r>R) break;
            else R=max(R,circles[j].o.x+circles[j].r); //!!!!!!!!!!!!!!
        }
        double M=(L+R)/2;
        st=i,ed=j-1;
        i=j-1;
        double fL=f(L),fM=f(M),fR=f(R);
        ans+=Simpson(L,M,R,fL,fM,fR,calc(R-L,fL,fM,fR));
    }
    printf("%.3lf\n",ans);
    return 0;
}
