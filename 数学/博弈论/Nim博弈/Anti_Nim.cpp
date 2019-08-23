反Nim博弈：
    走完最后一步（也即拿完最后一个石子注入此类的）
获胜条件（先手）：
    1、所有堆石子数都为1且游戏的SG值为0（即有偶数个孤单堆且每堆只有1个石子数）；
    2、存在某堆石子数大于1且游戏的SG值不为0；

//bzoj 1022
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int t, n;
int a[5010];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        int sum = 0, cnt = 0, flag = 0;
        for(int i = 1; i <= n; ++i) {
            cin >> a[i];
            sum ^= a[i];
            if(a[i] > 1) flag = 1;
        }
        if(!flag) {
            if(n % 2 == 0) cout << "John" << endl;
            else cout << "Brother" << endl;
        }
        else {
            if(sum == 0) cout << "Brother" << endl;
            else cout << "John" << endl;
        }
    }
    return 0;
}
