#ifndef MODELS_H
#define MODELS_H

#include <vector>

using namespace std;

class LNMM
{
private:
    double eps;
    bool verbose;
    int sample_size;
    int max_iter;

public:
    double beta;
    double sigma;

    vector<double> beta_trace;
    vector<double> sigma_trace;

    vector<double> z;
    vector<vector<double>> z_sample;

    LNMM(double beta_0 = 2.0, double sigma_0 = 1.0, int sample_size = 10000,
         int max_iter = 50, double eps = 1.0e-5, bool verbose = true);

    void fit(vector<vector<double>> x, vector<vector<double>> y);

    double get_beta(void);
    double get_sigma(void);

    vector<double> get_beta_trace(void);
    vector<double> get_sigma_trace(void);
    vector<vector<double>> get_z_sample(void);
};

#endif
