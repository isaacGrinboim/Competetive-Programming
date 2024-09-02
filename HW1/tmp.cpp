#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
typedef long long ll;
#define pb push_back
using namespace std;
#define EPS 1e-9
#define INF 1e9
#define PI acos(-1.0)

struct point {
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS);
    }
};

double cross(const point &O, const point &A, const point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<point> convex_hull(vector<point> P) {
    int n = P.size(), k = 0;
    vector<point> H(2*n);
    sort(P.begin(), P.end());

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n-2, t = k+1; i >= 0; --i) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k-1);
    return H;
}

bool onSegment(point p, point q, point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(point p, point q, point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (fabs(val) < EPS) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(point p1, point q1, point p2, point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    if (o1 != o2 && o3 != o4)
        return true;
    
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool isInsideHull(const vector<point>& hull, const point& p) {
    if (hull.size() < 3) return false;
    point extreme = {INF, p.y};
    int count = 0, i = 0;
    do {
        int next = (i + 1) % hull.size();
        if (doIntersect(hull[i], hull[next], p, extreme)) {
            if (orientation(hull[i], p, hull[next]) == 0)
                return onSegment(hull[i], p, hull[next]);
            count++;
        }
        i = next;
    } while (i != 0);
    return count & 1;
}

bool checkSeparation(const vector<point>& hull1, const vector<point>& hull2) {
    for (size_t i = 0; i < hull1.size(); ++i) {
        point p1 = hull1[i];
        point q1 = hull1[(i + 1) % hull1.size()];
        for (size_t j = 0; j < hull2.size(); ++j) {
            point p2 = hull2[j];
            point q2 = hull2[(j + 1) % hull2.size()];
            if (doIntersect(p1, q1, p2, q2)) {
                return false;
            }
        }
    }
    for (const point& p : hull1) {
        if (isInsideHull(hull2, p)) {
            return false;
        }
    }
    for (const point& p : hull2) {
        if (isInsideHull(hull1, p)) {
            return false;
        }
    }
    return true;
}

int main() {
    ll M, C;
    cin >> M >> C;
    while (M && C) {
        vector<point> mPoints(M), cPoints(C);
        for (int i = 0; i < M; ++i) {
            double x, y;
            cin >> x >> y;
            mPoints[i] = {x, y};
        }
        for (int i = 0; i < C; ++i) {
            double x, y;
            cin >> x >> y;
            cPoints[i] = {x, y};
        }

        vector<point> mHull = convex_hull(mPoints);
        vector<point> cHull = convex_hull(cPoints);

        bool canSeparate = checkSeparation(mHull, cHull);

        if (canSeparate) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }

        cin >> M >> C;
    }

    return 0;
}
