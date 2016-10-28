// sigma{i in [0,n)} [(a+b*i)/m], O(nlogn)
long long pt_line(const long long &n, const long long &a,
                const long long &b, const long long &m) {
    if (b == 0) {
        return n * (a / m);
    }
    if (a >= m) {
        return n * (a / m) + solve(n, a % m, b, m);
    }
    if (b >= m) {
        return (n - 1) * n / 2 * (b / m) + solve(n, a, b % m, m);
    }
    return pt_line((a + b * n) / m, (a + b * n) % m, m, b);
}