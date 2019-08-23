阶梯Nim
N个阶梯，限制每次从上一个阶梯移到下一个阶梯
阶梯Nim只考虑奇数位置进行Nim游戏，因为偶数位置是对称的，我们有平衡的操作

poj 1704
把两颗棋子之间的空隙当成是棋子，然后处理奇数堆就好了。

#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
int t, n;
int sg[MAXN][MAXN], step[MAXN][MAXN];
int a[1010];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        int sum = 0;
        for(int i = 1; i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1);
        for(int i = n; i >= 1; i -= 2)
            sum ^= a[i] - a[i - 1] - 1;
        if(sum) cout << "Georgia will win" << endl;
        else cout << "Bob will win" << endl;
    }
    return 0;
}
