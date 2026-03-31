#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Efficient function to find where the n-th ball lands
int findPosition(int D, long long n) {
    int node = 1;
    long long k = n;

    for (int depth = 0; depth < D - 1; depth++) {
        if (k % 2 == 1) {
            // Odd ball at this node goes left
            node = node * 2;
            k = (k + 1) / 2;
        } else {
            // Even ball at this node goes right
            node = node * 2 + 1;
            k = k / 2;
        }
    }

    return node;
}

// Function to count how many balls reach a specific leaf
long long countBallsAtLeaf(int leaf_node, int D, long long n) {
    // Work backwards to find the path to this leaf
    // Then count how many balls follow this path

    vector<int> path; // 0 = left, 1 = right
    int node = leaf_node;

    // Trace back to root
    for (int depth = D - 1; depth > 0; depth--) {
        if (node % 2 == 0) {
            path.push_back(0); // came from left
        } else {
            path.push_back(1); // came from right
        }
        node = node / 2;
    }

    // Reverse to get path from root to leaf
    reverse(path.begin(), path.end());

    // Count balls following this path
    long long count = n;
    for (int i = 0; i < D - 1; i++) {
        if (path[i] == 0) {
            // Path goes left
            count = (count + 1) / 2;
        } else {
            // Path goes right
            count = count / 2;
        }
    }

    return count;
}

int main() {
    int D;
    long long n;
    cin >> D >> n;

    // Find position of last ball
    int last_pos = findPosition(D, n);
    cout << last_pos << endl;

    // Calculate state of each leaf
    int leaf_start = (1 << (D - 1));
    int leaf_end = (1 << D) - 1;

    for (int i = leaf_start; i <= leaf_end; i++) {
        if (i > leaf_start) cout << " ";
        long long balls = countBallsAtLeaf(i, D, n);
        cout << (balls % 2);
    }
    cout << endl;

    return 0;
}
