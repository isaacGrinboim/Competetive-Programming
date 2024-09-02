#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <limits>
using namespace std;
typedef long long ll;

const int INF = numeric_limits<int>::max();

struct Recipe {
    int cost;
    int prestige;
};

void topologicalSortAndShortestPaths(vector<vector<pair<int, Recipe>>> &graph, vector<int> &inDegrees, vector<pair<int, int>> &results) {
    stack<int> stk;
    for (int i = 0; i < inDegrees.size(); ++i) {
        if (inDegrees[i] == 0) {
            stk.push(i);
            results[i] = {0, 0};
        }
    }

    while (!stk.empty()) {
        int node = stk.top(); stk.pop();
        for (auto &neighbor : graph[node]) {
            int nextNode = neighbor.first;
            int addedCost = neighbor.second.cost;
            int addedPrestige = neighbor.second.prestige;

            if (results[nextNode].first > results[node].first + addedCost) {
                results[nextNode] = {results[node].first + addedCost, results[node].second + addedPrestige};
            } else if (results[nextNode].first == results[node].first + addedCost) {
                results[nextNode].second = max(results[nextNode].second, results[node].second + addedPrestige);
            }

            if (--inDegrees[nextNode] == 0) {
                stk.push(nextNode);
            }
        }
    }
}

void knapsackMaxPrestige(vector<pair<int, int>> &dishDetails, int budget, int &maxPrestige, int &minCost) {
    vector<vector<int>> dp(dishDetails.size() + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= dishDetails.size(); ++i) {
        for (int j = 1; j <= budget; ++j) {
            if (dishDetails[i - 1].first <= j) {
                dp[i][j] = max(dp[i - 1][j], dishDetails[i - 1].second + dp[i - 1][j - dishDetails[i - 1].first]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }

            if (dp[i][j] > maxPrestige) {
                maxPrestige = dp[i][j];
                minCost = j;
            }
        }
    }
}

int main() {
    int budget;
    int numRecipes;

    while (cin >> budget >> numRecipes) {
        unordered_map<string, int> dishIndexMap;
        vector<vector<pair<int, Recipe>>> graph;
        vector<int> inDegrees;
        int currentIndex = 0;

        for (int i = 0; i < numRecipes; ++i) {
            string derivedDish, baseDish, ingredient;
            int addedCost, addedPrestige;
            cin >> derivedDish >> baseDish >> ingredient >> addedCost >> addedPrestige;

            if (dishIndexMap.find(baseDish) == dishIndexMap.end()) {
                dishIndexMap[baseDish] = currentIndex++;
                graph.emplace_back();
                inDegrees.push_back(0);
            }

            if (dishIndexMap.find(derivedDish) == dishIndexMap.end()) {
                dishIndexMap[derivedDish] = currentIndex++;
                graph.emplace_back();
                inDegrees.push_back(0);
            }

            graph[dishIndexMap[baseDish]].push_back({dishIndexMap[derivedDish], {addedCost, addedPrestige}});
            inDegrees[dishIndexMap[derivedDish]]++;
        }

        vector<pair<int, int>> dishDetails(currentIndex, {INF, INF});
        topologicalSortAndShortestPaths(graph, inDegrees, dishDetails);

        int maxPrestige = 0;
        int minCost = 0;
        knapsackMaxPrestige(dishDetails, budget, maxPrestige, minCost);

        cout << maxPrestige << endl << minCost << endl;
    }

    return 0;
}
