#include <stdio.h>
#include <cmath>
#include <vector>
#include <numeric>

#include "utils.h"
#include "models.h"

using namespace ::std;

LNMM::LNMM(double beta_0, double sigma_0, int sample_size, int max_iter, double eps, bool verbose)
{
    this->beta = beta_0;
    this->sigma = sigma_0;
    this->sample_size = sample_size;
    this->max_iter = max_iter;
    this->eps = eps;
    this->verbose = verbose;

    beta_trace.assign(max_iter, 0.0e0);
    sigma_trace.assign(max_iter, 0.0e0);
}

void LNMM::fit(vector<vector<double>> x, vector<vector<double>> y)
{
    int i, j, m, n;
    int M, N;
    double candidate;
    double accept_prob;
    double y_sum;
    double f0, f1;
    double z_sum;
    double prev_beta;

    // Data sizes
    M = y.size();
    N = y[0].size();

    // Initialization
    z.assign(M, 0.0e0);
    for (m = 0; m < M; m++)
    {
        z[m] = normal_dist(0.0e0, sigma);
    }

    z_sample.assign(sample_size, vector<double>(M, 0.0e0));

    for (i = 0; i < max_iter; i++)
    {
        for (j = 0; j < sample_size; j++)
        {
            for (m = 0; m < M; m++)
            {
                // proposal distribution (random walk)
                candidate = normal_dist(z[m], sigma / 1.0);

                // calculate acceptance probability
                y_sum = accumulate(y[m].begin(), y[m].end(), 0.0e0);
                accept_prob = exp(y_sum * (candidate - z[m]) - (candidate * candidate - z[m] * z[m]) / 2.0 / sigma);
                for (n = 0; n < N; n++)
                {
                    accept_prob *= (1.0 + exp(beta * x[m][n] + z[m])) / (1.0 + exp(beta * x[m][n] + candidate));
                }

                // update z value if accepted
                if (minimum(1.0, accept_prob) >= uniform_dist(0.0, 1.0))
                {
                    z[m] = candidate;
                }
            }

            z_sample[j] = z;
        }

        for (int newton_step = 0; newton_step < 1000; newton_step++)
        {
            f0 = f1 = 0.0e0;

            for (j = 0; j < sample_size; j++)
            {
                for (m = 0; m < M; m++)
                {
                    for (n = 0; n < N; n++)
                    {
                        f0 += x[m][n] * (y[m][n] - logit(beta * x[m][n] + z_sample[j][m]));
                        f1 += -x[m][n] * x[m][n] * logit_grad(beta * x[m][n] + z_sample[j][m]);
                    }
                }
            }

            prev_beta = beta;
            beta -= f0 / f1;

            printf("Newton-iteration: %d, beta: %e\n", newton_step, beta);

            if (abs(beta - prev_beta) < eps)
            {
                break;
            }
        }

        z_sum = 0.0e0;
        for (j = 0; j < sample_size; j++)
        {
            for (m = 0; m < M; m++)
            {
                z_sum += z_sample[j][m] * z_sample[j][m];
            }
        }

        sigma = 1.0 / M * z_sum / sample_size;

        if (verbose)
            printf("[iter: %2d, beta: %.3f, sigma: %.3f]\n", i, beta, sigma);
    }

    printf("Final result -> beta = %.3f, sigma = %.3f\n", beta, sigma);
}

double LNMM::get_beta(void)
{
    return beta;
}

double LNMM::get_sigma(void)
{
    return sigma;
}

vector<double> LNMM::get_beta_trace(void)
{
    return beta_trace;
}

vector<double> LNMM::get_sigma_trace(void)
{
    return sigma_trace;
}