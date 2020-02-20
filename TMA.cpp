/**
 * TMA - The Mating Algorithm as per Gale-Shapley algorithm
 * The problem based on N suitors (boys) and N girls.
 *
 * Time complexity: O(N^2)
 * Space complexity: O(N^2)
 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>

// N is the number of man or woman
// thus 2*N is total number of both men and women
template <int N>
class Solution {
public:
    // check if woman (w) prefers man (m) than another man (anotherM)
    bool wPreferm(int prefList[2*N][N], int w, int m, int anotherM) {
        for (int i=0; i<N; ++i) {
            if (prefList[w][i] == m)
                return true;
            else if (prefList[w][i] == anotherM)
                return false;
        }

        // should not happen
        return false;
    }

    // main function for The Mating Algorithm
    std::vector<int> tma(int prefList[2*N][N]) {
        // result of mates of women
        int wResults[N];
        std::memset(&wResults[0], -1, sizeof(wResults));

        // number of man's free count
        int mFreeCount = N;

        // whether or not man is free (thus not engage yet)
        bool mFree[N];
        std::memset(mFree, true, sizeof(mFree));

        while (mFreeCount > 0) {
            // get the current free man to initiate the proposal
            int m;
            for (int i=0; i<N; ++i) {
                if (mFree[i]) {
                    m = i;
                    break;
                }
            }

            for (int i=0; i<N && mFree[m]; ++i) {
                // get the target woman from preference
                int w = prefList[m][i];

                // if woman is still free
                if (wResults[w - N] == -1) {
                    wResults[w - N] = m;
                    mFree[m] = false;
                    --mFreeCount;
                } else {    // woman is already engaged
                    // get the man the woman was engaged to
                    int anotherM = wResults[w - N];

                    // if a woman prefer this man (m) more than who she already enaged with
                    // then this man (m) win her heart
                    if (wPreferm(prefList, w, m, anotherM)) {
                        wResults[w - N] = m;
                        mFree[m] = false;
                        mFree[anotherM] = true;
                    }
                }
            }
        }

        std::vector<int> wResultsCvt (&wResults[0], &wResults[0] + N);

        return wResultsCvt;
    }
};

int main() {
    const int N = 4;
    // boys range from [0, 3]
    // girls range from [4, 7]
    // in general: boys => [0, N-1] and girls => [N, 2*N-1]
    int prefList[2*N][N] {
        {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3}
    };

    auto pairs = Solution<N>().tma(prefList);
    for (int i=0; i<pairs.size(); ++i) {
        std::cout << "Girl [" << i << "] <---> Boy [" << pairs[i] << "]\n";
    }
    return 0;
}
