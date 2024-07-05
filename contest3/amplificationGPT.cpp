#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

// Function to generate all subsets' products for a given subset of amplifiers
void generateSubsetsProducts(const vector<int>& amplifiers, vector<long long>& products) {
    int n = amplifiers.size();
    int totalSubsets = 1 << n; // 2^n subsets

    for (int i = 0; i < totalSubsets; ++i) {
        long long product = 1;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                product *= amplifiers[j];
            }
        }
        products.push_back(product);
    }
}

// Function to solve the problem using Meet in the Middle
long long solve(const vector<int>& amplifiers, long long target) {
    int n = amplifiers.size();
    int half = n / 2;

    // Split the amplifiers into two halves
    vector<int> firstHalf(amplifiers.begin(), amplifiers.begin() + half);
    vector<int> secondHalf(amplifiers.begin() + half, amplifiers.end());

    // Generate all subsets' products for both halves
    vector<long long> productsFirstHalf, productsSecondHalf;
    generateSubsetsProducts(firstHalf, productsFirstHalf);
    generateSubsetsProducts(secondHalf, productsSecondHalf);

    // Sort the products of the second half for binary search
    sort(productsSecondHalf.begin(), productsSecondHalf.end());

    // Find the closest product to the target without exceeding it
    long long closestProduct = 0;
    for (long long product : productsFirstHalf) {
        if (product <= target) {
            // Binary search to find the best complement in the second half
            auto it = upper_bound(productsSecondHalf.begin(), productsSecondHalf.end(), target / product);
            if (it != productsSecondHalf.begin()) {
                --it;
                closestProduct = max(closestProduct, product * (*it));
            }
        }
    }

    return closestProduct;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int a;
        long long y;
        cin >> a >> y;

        vector<int> amplifiers(a);
        for (int i = 0; i < a; ++i) {
            cin >> amplifiers[i];
        }

        cout << solve(amplifiers, y) << endl;
    }

    return 0;
}
