#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 323232323;
const int N = 100;
typedef vector<int>  Poly;
Poly t[65];
int a[N], b[N], n;
int qpow(int a, int b)
{
    int res = 1;
    for(; b >0; b /= 2, a = a * a % mod)
        if(b % 2) res = res * a % mod;
    return res;
}
void Pmul(Poly &A, int a, int b)
{
    int n = A.size();
    for(int i = n - 2; i >= 0; i--) A[i + 1] = (A[i] * a % mod + A[i + 1] * b % mod) % mod;
    A[0] = A[0] * b % mod;
    return;
}
Poly getp(Poly &A, Poly &B, int p)
{
    int n = A.size();
    // printf("Case:%lld\n", n);
    Poly res(n);
    res[0] = 1;
    int fra = 1;
    for(int i = 0; i < n; i++)
    {
        if(i == p) continue;
        Pmul(res, 1, (mod - A[i]) % mod);
        fra = fra * ((A[p] - A[i]) % mod  + mod) % mod;
    }
    for(int i = 0; i < n; i++) res[i] = res[i] * qpow(fra, mod - 2) % mod * B[p] % mod;
    return res;
}
Poly lagrange(Poly &x, Poly &y)
{
    int n = x.size();
    Poly res(n);
    for(int i = 0; i < n; i++)
    {
        Poly temp = getp(x, y, i);
        for(int j = 0; j < n; j++) res[j] = (res[j] + temp[j]) % mod;
    }
    return res;
}
void Init()
{
    for(int i = 0; i <= 60; i++)
    {
        Poly x(i + 2), y(i + 2);
        for(int j = 0; j <= i + 1; j++) x[j] = (j + 1), y[j] =qpow(j + 1, i);
        for(int j = 1; j <= i + 1; j++) y[j] = (y[j] + y[j - 1]) % mod;
        t[i] = lagrange(x, y);
    }
    return;
}
int f(int k, int x)
{
    if(k == 1) return 1;
    int ans = 0;
    for(int y = 0; y <= b[k] + a[k + 1] * x ; y++) ans = (ans + f(k - 1, y)) % mod;
    return ans;
}
Poly power(int a, int b, int k)
{
    Poly res(k + 1, 0);
    res[0] = 1;
    for(int i = 1; i <= k; i++) Pmul(res, a, b);
    return res;
}
Poly getL(Poly k, int a, int b)
{
    int n = k.size();
    Poly res(n, 0);
    for(int i = 0; i < n; i++)
    {
        Poly temp = power(a, b, i);
        for(int j = 0; j <= i; j++) res[j] = (res[j] + temp[j] * k[i] % mod) % mod;
    }
    return res;
}
 
signed main()
{
    Init();
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    // printf("%lld\n", f(n, 0));
    Poly now(1,0);
    now[0] = 1;
    for(int i = 2; i <= n; i++)
    {
        int siz = now.size();
        Poly nxt(siz + 1);
        for(int j = 1; j < siz; j++)
        {
            if(now[j] == 0) continue;
            Poly temp = getL(t[j], a[i + 1], b[i]);
            for(int k = 0; k < j + 2; k++) nxt[k] = (nxt[k] + temp[k] * now[j] % mod) % mod;
        }
        nxt[0] = (nxt[0] + (b[i] + 1) * now[0] % mod) % mod;
        nxt[1] = (nxt[1] + a[i + 1] * now[0] % mod) % mod;
        // for(int j = 0; j < siz + 1; j++) printf("%lld ", nxt[j]);
        // printf("\n");
        // for(int j = 0; j < siz + 1; j++) printf("%lld ", f(i, j));
        // printf("\n");
        now = nxt;
    }
    printf("%lld\n", now[0]);
    return 0;
}