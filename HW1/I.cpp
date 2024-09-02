#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double TOLERANCE = 1e-10;

struct Coordinate {
    double x, y;
    Coordinate(double a = 0, double b = 0) : x(a), y(b) {}
    bool operator<(const Coordinate &a) const {
        if (fabs(x - a.x) > TOLERANCE) return x < a.x;
        return y < a.y;
    }
    bool operator==(const Coordinate &a) const {
        return fabs(x - a.x) < TOLERANCE && fabs(y - a.y) < TOLERANCE;
    }
    Coordinate operator+(const Coordinate &a) const {
        return Coordinate(x + a.x, y + a.y);
    }
    Coordinate operator-(const Coordinate &a) const {
        return Coordinate(x - a.x, y - a.y);
    }
    Coordinate operator/(const double val) const {
        return Coordinate(x / val, y / val);
    }
    Coordinate operator*(const double val) const {
        return Coordinate(x * val, y * val);
    }
};

double crossProduct(Coordinate origin, Coordinate a, Coordinate b) {
    return (a.x - origin.x) * (b.y - origin.y) - (a.y - origin.y) * (b.x - origin.x);
}

int constructConvexHull(int numPoints, Coordinate points[], Coordinate convexHull[]) {
    sort(points, points + numPoints);
    int m = 0;
    for (int i = 0; i < numPoints; i++) {
        while (m >= 2 && crossProduct(convexHull[m - 2], convexHull[m - 1], points[i]) <= 0)
            m--;
        convexHull[m++] = points[i];
    }
    for (int i = numPoints - 1, t = m + 1; i >= 0; i--) {
        while (m >= t && crossProduct(convexHull[m - 2], convexHull[m - 1], points[i]) <= 0)
            m--;
        convexHull[m++] = points[i];
    }
    return m - 1;
}

bool isInsideConvexPolygon(const Coordinate &point, Coordinate convexHull[], int hullSize) {
    if (hullSize < 3) return false;
    if (crossProduct(convexHull[0], point, convexHull[1]) > TOLERANCE) return false;
    if (crossProduct(convexHull[0], point, convexHull[hullSize - 1]) < -TOLERANCE) return false;

    int left = 2, right = hullSize - 1;
    int lineIndex = -1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (crossProduct(convexHull[0], point, convexHull[mid]) > -TOLERANCE) {
            lineIndex = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return crossProduct(convexHull[lineIndex - 1], point, convexHull[lineIndex]) < TOLERANCE;
}

Coordinate largeLanterns[10010], convexHull[20020];

void processTestCases() {
    int numLargeLanterns, numSmallLanterns;
    while (cin >> numLargeLanterns) {
        for (int i = 0; i < numLargeLanterns; ++i) {
            cin >> largeLanterns[i].x >> largeLanterns[i].y;
        }

        int hullSize = constructConvexHull(numLargeLanterns, largeLanterns, convexHull);

        cin >> numSmallLanterns;
        int insideCount = 0;
        for (int i = 0; i < numSmallLanterns; ++i) {
            Coordinate smallLantern;
            cin >> smallLantern.x >> smallLantern.y;
            if (isInsideConvexPolygon(smallLantern, convexHull, hullSize)) {
                ++insideCount;
            }
        }

        cout << insideCount << endl;
    }
}

int main() {
    processTestCases();
    return 0;
}
