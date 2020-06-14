#include <random>
#include <cmath>

#include "utils.h"

using namespace ::std;

double normal_dist(double mean, double var)
{
    random_device rnd; // 非決定的な乱数生成器でシード生成機を生成
    mt19937 mt(rnd()); //  メルセンヌツイスターの32ビット版、引数は初期シード
    normal_distribution<> norm(mean, var);

    return norm(mt);
}

double uniform_dist(double min_value, double max_value)
{
    random_device rnd; // 非決定的な乱数生成器でシード生成機を生成
    mt19937 mt(rnd()); //  メルセンヌツイスターの32ビット版、引数は初期シード
    uniform_real_distribution<> dist(min_value, max_value);

    return dist(mt);
}

double minimum(double a, double b)
{
    if (a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double logit(double x)
{
    return exp(x) / (1.0 + exp(x));
}

double logit_grad(double x)
{
    return exp(x) / (1.0 + exp(x)) / (1.0 + exp(x));
}