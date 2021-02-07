#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::solve(const vector<int> &price, int length)
{
    vector<vector<int>> dp(price.size(), vector<int>(length + 1, 0));

    for (int i = 0; i < price.size(); ++i)
        for (int l = 1; l <= length; ++l)
        {
            int profitWith{0}, profitWithout{0};
            if (i > 0)
                profitWithout = dp[i - 1][l];
            
            if (l > i)
                profitWith = price[i] + dp[i][l - i - 1];

            dp[i][l] = max(profitWith, profitWithout);
        }

    return dp[price.size() - 1][length];
}