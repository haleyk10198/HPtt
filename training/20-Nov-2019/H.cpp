#include <iostream>
#include <cstdlib>
using namespace std;
const int maxn = 250001;
int a[maxn], b[maxn], d[maxn], n, pivot;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    pivot = n / 2;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    for(int i = 0; i < n; i++)
        d[i] = (a[i] < pivot) - (b[i] < pivot);
    long long ans = abs(d[0]);
    for(int i = 1; i < n; i++)
    {
        d[i] += d[i-1];
        ans += abs(d[i]);
    }
    cout << ans << endl;
    return 0;
}