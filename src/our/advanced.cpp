// c on pq
int PointOnLine(PT c, PT p, PT q) {
    return sgn(cross(p-c, q-c)) == 0;
}
int PointOnSegment(PT c, PT p, PT q) {
    return sgn(cross(p-c, q-c)) == 0 && sgn(dot(p-c, q-c)) <= 0;
}
// 1 -> cross,   0 -> parallel,  -1 -> overlap
int LineIntersection(PT p, PT q, PT r, PT s, PT &cp) {
    double u = cross(p, q, r), v = cross(q, p, s);
    if (sgn(u + v)) {
        cp.x = (r.x*v + s.x*u) / (u + v);
        cp.y = (r.y*v + s.y*u) / (u + v);
        return 1;
    }
    if (sgn(u)) return 0;
    if (sgn(cross(r, s, p))) return 0;
    return -1;
}
// 1 ->intersect, 0 -> not (include parallel), -1 -> parallel and overlap
int SegmentIntersection(PT p, PT q, PT r, PT s, PT &cp) {
    int ret = LineIntersection(p, q, r, s, cp);
    if (ret == 1) return sgn(dot(p - cp, q - cp)) <= 0 && sgn(dot(r - cp, s - cp)) <= 0;
    if (ret == -1 && (PointOnSegment(p, r, s) || PointOnSegment(q, r, s) 
                   || PointOnSegment(r, p, q) || PointOnSegment(s, p, q))) return -1;
    return 0;
}
// 0 -> not, 1 -> in, 2 -> boundary
int PointInPolygon(PT cp, PT p[], int n) {
    int wn = 0;
    p[n] = p[0];
    for (int i = 0; i < n; ++i) {
        if (PointOnSegment(cp, p[i], p[i+1])) return 2;
        int k = sgn(cross(p[i+1]-p[i], cp-p[i]));
        int d1 = sgn(p[i].y - cp.y);
        int d2 = sgn(p[i+1].y - cp.y);
        if (k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    return wn != 0;
}

// Triangle centers
void Circumcenter(PT a, PT b, PT c, PT &p) {
    b = b - a; c = c - a;
    PT r(dot(b,b)/2, dot(c,c)/2);
    double d = cross(b,c);
    p.x = a.x + cross(r,c) / d;
    p.y = a.y + cross(b,r) / d;
}
double Incenter(PT A, PT B, PT C, PT &cp) {
    double a = dis(B, C), b = dis(C, A), c = dis(A, B), p = (a + b + c) / 2;
    double s = sqrt(p * (p - a) * (p - b) * (p - c)), r = s / p;
    cp.x = (a * A.x + b * B.x + c * C.x) / (a + b + c);
    cp.y = (a * A.y + b * B.y + c * C.y) / (a + b + c);
    return r;
}
void Orthocenter(PT A, PT B, PT C, PT &cp) {
    Circumcenter(A, B, C, cp);
    cp.x = A.x + B.x + C.x - 2 * cp.x;
    cp.y = A.y + B.y + C.y - 2 * cp.y;
}
// 012 intersect points
int CircleCrossLine(PT p0, double r, PT p1, PT p2, PT &cp1, PT &cp2) {
    double d = fabs(PointToLine(p0, p1, p2, cp1));
    if (sgn(d - r) > 0) return 0;
    if (sgn(d - r) == 0) { cp2 = cp1; return 1;}
    d = sqrt(r * r - d * d) / dis(p1, p2);
    double dx = (p2.x - p1.x) * d;
    double dy = (p2.y - p1.y) * d;
    cp2.x = cp1.x + dx; cp2.y = cp1.y + dy;
    cp1.x = cp1.x - dx; cp1.y = cp1.y - dy;
    return 2;
}
// 012 intersect points
int CircleCrossCircle(PT p1, double r1, PT p2, double r2, PT &cp1, PT &cp2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + EPS < 0) return 0;
    if (d < EPS) d = 0; else d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d; sq *= 2;
    cp1.x = (x - dy) / sq; cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq; cp2.y = (y - dx) / sq;
    if (d > EPS) return 2;
    return 1;
}
