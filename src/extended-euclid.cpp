void euclid(const long long &a, const long long &b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        euclid(b, a % b, x, y);
        x -= a / b * y;
        swap(x, y);
    }
}