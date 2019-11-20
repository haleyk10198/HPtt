#include <bits/stdc++.h>
using namespace std;
const int maxn = 250001;
long long a[maxn], b[maxn], d[maxn], d1[maxn], d2[maxn], d3[maxn];
int n, pivot;

long long eval(long long *arr) {
    long long ans = abs(arr[0]);
    for(int i = 1; i < n; i++)
    {
        arr[i] += arr[i-1];
        ans += abs(arr[i]);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    pivot = (n >> 1) + (n & 1);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    long long ans = 1e15;
    if(n % 2 == 0) {
        for (int i = 0; i < n; i++) {
            d[i] = ((a[i] <= pivot) && (b[i] <= pivot)) - ((a[i] > pivot) && (b[i] > pivot));
        }
        ans = eval(d);
    } else {
        for (int i = 0; i < n; i++) {
            d[i] = ((a[i] <= pivot) && (b[i] < pivot)) - ((a[i] > pivot) && (b[i] >= pivot));
        }
        ans = eval(d);
        for (int i = 0; i < n; i++) {
            d[i] = ((a[i] < pivot) && (b[i] <= pivot)) - ((a[i] >= pivot) && (b[i] > pivot));
        }
        ans = min(ans, eval(d));
        for (int i = 0; i < n; i++) {
            d1[i] = (a[i] == pivot && b[i] > pivot) - (a[i] < pivot && b[i] == pivot);
            d2[i] = (a[i] > pivot && b[i] > pivot) - (a[i] < pivot && b[i] < pivot);
            d3[i] = (a[i] > pivot && b[i] == pivot) - (a[i] == pivot && b[i] < pivot);
        }
        ans = min(ans, eval(d1) + eval(d2) + eval(d3));
    }
    cout << ans << endl;
    return 0;
}