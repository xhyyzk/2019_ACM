struct Point {
    int x, y;
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
