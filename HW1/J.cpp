#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef vector<ll> Point3D;
typedef vector<ll> Point2D;

struct unionfind {
    vector<pair<ll, ll>> parent;

    unionfind(ll size) {
        parent = vector<pair<ll, ll>>(size);
        for (ll i = 0; i < size; i++)
            parent[i] = {i, 1};
    }

    ll find(ll x) {
        ll tmp = x;
        while (x != parent[x].first) x = parent[x].first;
        while (tmp != x) {
            ll remember = parent[tmp].first;
            parent[tmp].first = x;
            tmp = remember;
        }
        return x;
    }

    void Union(ll p, ll q) {
        p = find(p);
        q = find(q);
        if (q == p) return;
        if (parent[p].second < parent[q].second) {
            parent[p] = {q, parent[p].second + parent[q].second};
            parent[q].second = parent[p].second;
        } else {
            parent[q] = {p, parent[p].second + parent[q].second};
            parent[p].second = parent[q].second;
        }
    }

    ll get_size(ll x) {
        return parent[find(x)].second;
    }
};

int main() {
    ll K;
    while (cin >> K) {
        bool cycle_2D = false;
        bool cycle_3D = false;
        ll index_3D = 1;
        ll index_2D = 0;
        map<Point3D, ll> indices3D;
        map<Point2D, ll> indices2D;
        unionfind uf2D(2 * K + 1);
        unionfind uf3D(2 * K + 1);
        map<pair<ll, ll>, int> edges_3D;
        map<pair<ll, ll>, int> edges_2D;

        for (ll i = 0; i < K; ++i) {
            ll x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            Point3D p1_3D = {x1, y1, z1};
            Point3D p2_3D = {x2, y2, z2};
            Point2D p1_2D = {x1, y1};
            Point2D p2_2D = {x2, y2};

            if (!cycle_3D) {
                if (indices3D.find(p1_3D) == indices3D.end()) {
                    indices3D[p1_3D] = index_3D++;
                }
                if (indices3D.find(p2_3D) == indices3D.end()) {
                    indices3D[p2_3D] = index_3D++;
                }
                ll p1Idx_3D = indices3D[p1_3D];
                ll p2Idx_3D = indices3D[p2_3D];

                bool sameComponent3D = uf3D.find(p1Idx_3D) == uf3D.find(p2Idx_3D);
                bool edgeExists3D = edges_3D.find({p1Idx_3D, p2Idx_3D}) != edges_3D.end();

                if (sameComponent3D && uf3D.get_size(p2Idx_3D) >= 3 && !edgeExists3D) {
                    cycle_3D = true;
                } else {
                    uf3D.Union(p1Idx_3D, p2Idx_3D);
                    edges_3D[{p1Idx_3D, p2Idx_3D}] = 1;
                    edges_3D[{p2Idx_3D, p1Idx_3D}] = 1;
                }
            }

            if (!cycle_2D) {
                if (indices2D.find(p1_2D) == indices2D.end()) {
                    indices2D[p1_2D] = index_2D++;
                }
                if (indices2D.find(p2_2D) == indices2D.end()) {
                    indices2D[p2_2D] = index_2D++;
                }
                ll p1Idx_2D = indices2D[p1_2D];
                ll p2Idx_2D = indices2D[p2_2D];

                bool differentComponents2D = indices2D[p1_2D] != indices2D[p2_2D];
                bool sameComponent2D = uf2D.find(p1Idx_2D) == uf2D.find(p2Idx_2D);
                bool edgeExists2D = edges_2D.find({p1Idx_2D, p2Idx_2D}) != edges_2D.end();

                if (differentComponents2D && sameComponent2D && uf2D.get_size(p2Idx_2D) >= 3 && !edgeExists2D) {
                    cycle_2D = true;
                } else if (!sameComponent2D) {
                    uf2D.Union(p1Idx_2D, p2Idx_2D);
                    edges_2D[{p1Idx_2D, p2Idx_2D}] = 1;
                    edges_2D[{p2Idx_2D, p1Idx_2D}] = 1;
                }
            }
        }

        if (cycle_3D) {
            cout << "True closed chains" << endl;
        } else {
            cout << "No true closed chains" << endl;
        }

        if (cycle_2D) {
            cout << "Floor closed chains" << endl;
        } else {
            cout << "No floor closed chains" << endl;
        }
    }
    return 0;
}
