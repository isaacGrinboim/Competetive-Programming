#include <iostream>
#include <vector>

const int MAX_SIZE = 1e6;
int n;
int tree[2 * MAX_SIZE];

void update(int pos, int value) {
    for (tree[pos += n] = value; pos > 1; pos >>= 1) 
        tree[pos >> 1] = tree[pos] + tree[pos ^ 1];
}

void buildTree() {
    for (int i = n - 1; i > 0; --i) 
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

int querySum(int left, int right) {
    int result = 0;
    for (left += n, right += n; left < right; left >>= 1, right >>= 1) {
        if (left & 1) result += tree[left++];
        if (right & 1) result += tree[--right];
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int testCases;
    std::cin >> testCases;

    while (testCases--) {
        int n1, m;
        std::cin >> n1 >> m;
        n = n1 + m;
        
        std::fill(tree + n, tree + 2 * n, 0);
        buildTree();
        
        std::vector<int> positionMap(n1);
        for (int i = 0; i < n1; ++i) {
            positionMap[i] = n1 - i - 1;
            update(i, 1);
        }

        for (int j = 0; j < m - 1; ++j) {
            int x;
            std::cin >> x;
            --x;
            std::cout << querySum(positionMap[x] + 1, n) << " ";
            update(positionMap[x], 0);
            positionMap[x] = n1 + j;
            update(positionMap[x], 1);
        }

        int x;
        std::cin >> x;
        --x;
        std::cout << querySum(positionMap[x] + 1, n) << std::endl;
    }

    return 0;
}
