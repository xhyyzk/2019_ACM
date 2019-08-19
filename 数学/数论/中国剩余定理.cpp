/*poj 2891 模数非互质
 将
    x = a1 (mod n1)
    x = a2 (mod n2)
 合并成
    x = a (mod n)
 其中n1, n2不互质
 令 d = gcd(n1, n2), c = a2 - a1
 所以
    a = n1 * K + a1, n = n1 * n2 / d
 其中
    K = c / d * inv(n1/d)
 最终，合并k个方程的最小x值为a % n;
*/


#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll Mod;

ll gcd(ll a, ll b)
{
    if(b == 0)
        return a;
    return gcd(b , a % b);
}

ll Extend_Euclid(ll a, ll b, ll & x, ll & y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = Extend_Euclid(b , a % b , x , y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

ll inv(ll a, ll n)
{
    ll x,y;
    ll t = Extend_Euclid(a , n , x , y);
    if(t != 1)
        return -1;
    return (x % n + n) % n;
}

bool Merge(ll a1, ll n1, ll a2, ll n2, ll & a3, ll & n3)
{
    ll d = gcd(n1 , n2);
    ll c = a2 - a1;
    if(c % d)
        return false;
    c = (c % n2 + n2) % n2;
    c /= d;
    n1 /= d;
    n2 /= d;
    c *= inv(n1 , n2);
    c %= n2;
    c *= n1*d;
    c += a1;
    n3 = n1 * n2 * d;
    a3 = (c % n3 + n3) % n3;
    return true;
}

ll CRT(int len, ll* a, ll* n)
{
    ll a1 = a[0] , n1 = n[0];
    ll a2,n2;
    for(int i = 1; i < len; i++)
    {
        ll aa,nn;
        a2 = a[i];
        n2 = n[i];
        if(!Merge(a1 , n1 , a2 , n2 , aa , nn))
            return -1;
        a1 = aa;
        n1 = nn;
    }
    Mod = n1;
    return (a1 % n1 + n1) % n1;
}
ll a[1000] , r[1000];
int k;
int main()
{
    while(scanf("%d",&k)!=EOF)
    {
        for(int i = 0; i < k; i++)
            scanf("%lld %lld", &a[i] , &r[i]);
        printf("%lld\n",CRT(k , r , a));
    }
    return 0;
}
