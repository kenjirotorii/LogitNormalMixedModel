#include <stdio.h>
#include <vector>

#include "models.h"

using namespace std;

int main(void)
{
    vector<vector<double>> y = {
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int M = y.size();
    int N = y[0].size();

    vector<vector<double>> x(M, vector<double>(N, 0.0e0));

    for (int m = 0; m < M; m++)
    {
        for (int n = 0; n < N; n++)
        {
            x[m][n] = (double)(n + 1) / 15.0;
        }
    }

    LNMM lnmm(2.0, 1.0, 10000, 50, 1.0e-5, true);
    lnmm.fit(x, y);

    return 0;
}
