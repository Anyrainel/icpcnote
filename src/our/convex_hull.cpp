PT bp;  // Used for GrahamScan, lowest point
bool PolarCmp(const PT &p1, const PT &p2) {
    int u = sgn(cross(bp, p1, p2));
    return u > 0 || (u == 0 && sgn(dist2(bp, p1) - dist2(bp, p2)) < 0);
}
int GrahamScan(PT ch[], int n, int &m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int u = sgn(ch[i].x - ch[k].x);
        int v = sgn(ch[i].y - ch[k].y);
        if (v < 0 || (v == 0 && u < 0)) k = i;
    }
    bp = ch[k];
    sort(ch, ch + n, PolarCmp);
    n = unique(ch, ch + n, PointEqual) - ch;
    if (n <= 1) {
        m = n;
        return 0;
    }
    if (sgn(cross(ch[1]-ch[0], ch[n-1]-ch[0])) == 0) {
        m = 2;
        ch[1] = ch[n-1];
        return 0;
    }
    ch[n++] = ch[0];
    int i = 1;
    for (int j = 2; j < n; ++j) {
        while (i > 0 && sgn(cross(ch[i]-ch[i-1], ch[j]-ch[i-1])) < 0) --i;
        ch[++i] = ch[j];
    }
    m = i;
    return 0; 
}
PT ch[MAXN];
int main() {
    int N = 0, M;
    while (cin >> ch[N].x >> ch[N].y) ++N;
    GrahamScan(ch, N, M);
    for (int i = 0; i < M; ++i) cout << ch[i].x << " " << ch[i].y << endl;
    return 0;
}