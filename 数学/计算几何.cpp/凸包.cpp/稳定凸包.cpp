稳定凸包
    当凸包上存在一条边上的点只有端点两个点的时候，这个凸包不是稳定的，因为可以在这条边外
加上一点，构成一个新的凸包。所以稳定凸包就是凸包的一条边上至少有三个点。

poj 1228
给出一些点，判断是不是稳定凸包，即求出凸包后，判断每条边上是否至少有三个点存在。

代码：
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
const double pi = 3.1415926535;
const int eps = 1e-7;
const int inf = 0x3f3f3f3f;
#define zero(a) (fabs((double)(a)) < eps)
int t, n;

struct Point {
    int x, y, v, l;
    Point(){}
    Point(int _x, int _y){
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const {
        return Point(x - b.x,y - b.y);
    }
}p[1010], ch[1010];

bool cmp(Point a, Point b) {
    if(a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

int Cross(Point p1, Point p2) {
    return p1.x*p2.y - p1.y*p2.x;
}

double dis(Point p1, Point p2) {
    return sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

int ConvexHull(Point* p, int n, Point* ch) {
    sort(p, p + n, cmp);
    int m = 0;
    for(int i = 0; i < n; ++i) {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; --i) {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}

bool judge(Point a, Point b) {
    int num = 0;
    for(int i = 0; i < n; ++i) {
        if(!Cross(a-p[i], p[i]-b)) num++;
    }
    if(num >= 3) return true;
    else return false;
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
        if(n < 6) {
            cout << "NO" << endl;
            continue;
        }
        int res = ConvexHull(p, n, ch), flag = 0;
        ch[res] = ch[0];
        for(int i = 0; i < res; ++i) {
            if(!judge(ch[i], ch[i + 1])) {
                flag = 1;
                break;
            }
        }
        if(!flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
