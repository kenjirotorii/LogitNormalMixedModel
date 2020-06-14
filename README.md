## Logit Normal Mixed Model

### Description of the model

Generalized Linear Mixed Model (GLMM) is a statistical model that incorporates a random effect like an indivisual difference into Generalized Linear Model (GLM). Among GLMM, a logit-normal mixed model is used when fitting a set of binary response variables. Let $Y_{ij}$ for $i=1,...,m$ and $j=1,...,n$ denote a set of binary response variables: the $j$th response for the $i$th subject. Let $x_{ij}$ be a covariate associated with the $i, j$ observation. Conditional on the random effects $Z = \boldsymbol{z} \in \mathbb{R}^m$, the observations $Y_{ij}$ are independently distributed as $Bernoulli(\pi_{ij})$ where

$$
\begin{align}
\ln\left(\frac{\pi_{ij}}{1 - \pi_{ij}}\right) &= \beta x_{ij} + z_i \ .
\end{align}
$$

Let the random effects $Z_1, ..., Z_m$ be i.i.d $N(0, \sigma^2)$.

### EM algorithm

With the parameters $\theta = (\beta, \sigma^2)$ where $\beta, \sigma \in \mathbb{R}$, the likelihood function is given by

$$
\begin{align}
L(\theta; \boldsymbol{y})
&= \prod_{i=1}^{m} \int \left\{\prod_{j=1}^{n} p(y_{ij}| z_i; \theta) \right\} p(z_i;\theta) dz_i \\
&= \prod_{i=1}^{m} \int \left\{\prod_{j=1}^{n} \pi_{ij}^{y_{ij}} (1 - \pi_{ij})^{1 - y_{ij}} \right\} \frac{\exp(-z_i^2 / 2 \sigma^2)}{\sqrt{2\pi\sigma^2}} dz_i \\
&= \prod_{i=1}^{m} \int \left\{\prod_{j=1}^{n} \exp[y_{ij} \ln \pi_{ij} + (1 - y_{ij}) \ln(1 - \pi_{ij})] \right\} \frac{\exp(-z_i^2 / 2 \sigma^2)}{\sqrt{2\pi\sigma^2}} dz_i \\
&= \prod_{i=1}^{m} \int \left\{\prod_{j=1}^{n} \exp[y_{ij}(\beta x_{ij} + z_i) - \ln(1 + e^{\beta x_{ij} + z_i})] \right\} \frac{\exp(-z_i^2 / 2 \sigma^2)}{\sqrt{2\pi\sigma^2}} dz_i \\
&= (\sigma^2)^{-m/2} \int_{\mathbb{R}^m} \exp \left\{ \sum_{i=1}^{m} \sum_{j=1}^{n} [y_{ij}(\beta x_{ij} + z_i) - \ln(1 + e^{\beta x_{ij} + z_i})] - \frac{1}{2 \sigma^2} \sum_{i=1}^{m} z_i^2 \right\} d\boldsymbol{z} \ .
\end{align}
$$

Since the integral in Eq.6 is usually intractable, we can use EM algorithm to find the value $\hat{\theta}_{true}$ which maximizes the likelihood function. Because the likelihood function above cannot be numerically calculated, we find instead the value $\hat{\theta}$ which maximizes the expected value of the "complete data" log-likelihood at $\theta$ under the posterior distribution of the random effect $\boldsymbol{z}$ evaluated under the current parameter value $\theta^{old}$, which is called "evidence lower bound (ELBO)" or "$Q$-function". The $Q$-function is defined by

$$
\begin{align}
Q(\theta | \theta^{old}; \boldsymbol{y})
&= \mathbb{E}_{\boldsymbol{z} \sim p(\boldsymbol{z} | \boldsymbol{y}; \theta^{old})}[\ln p(\boldsymbol{y}, \boldsymbol{z}; \theta)] \\
&= \int_{\mathbb{R}^m} p(\boldsymbol{z} | \boldsymbol{y}; \theta^{old}) \ln p(\boldsymbol{y}, \boldsymbol{z}; \theta) d\boldsymbol{z} \ .
\end{align}
$$

In the E step, we calculate the $Q$-function with the current parameter value $\theta^{old}$. In the M step, we then determine the revised parameter estimate $\theta^{new}$ by maximizing the $Q$-function

$$
\begin{align}
\theta^{new} = \rm{argmax}_{\theta}\ Q(\theta | \theta^{old}; \boldsymbol{y}) \ .
\end{align}
$$

### Monte Carlo EM algorithm

If the integral in Eq.8 admits a closed form solution, the implementation of EM algorithm is straightforward. However, it does not. If one has the means to simulate random draws from this posterior distribution, the $Q$-function can be approximated by Monte Carlo integration. Let $\boldsymbol{z}^{(1)}, ..., \boldsymbol{z}^{(S)}$ denote a random sample from $p(\boldsymbol{z} | \boldsymbol{y}; \theta^{old})$. Then a Monte Carlo approximation to Eq.8 is given by

$$
\begin{align}
Q(\theta | \theta^{old}; \boldsymbol{y}) \approx \tilde{Q}(\theta | \theta^{old}; \boldsymbol{y}) := \frac{1}{S} \sum_{s=1}^S \ln p(\boldsymbol{y}, \boldsymbol{z}^{(s)}; \theta) \ .
\end{align}
$$

This learning algorithm is called as the Monte Carlo EM algorithm (MCEM).

The "complete data" log-likelihood with a random sample is given by

$$
\begin{align}
L_c (\theta; \boldsymbol{y})
& = \ln p(\boldsymbol{y}, \boldsymbol{z}^{(s)}; \theta) \\
&= \sum_{i=1}^m \sum_{j=1}^n [y_{ij} (\beta x_{ij} + z_i^{(s)}) - \ln(1 + e^{\beta x_{ij} + z_i^{(s)}})] - \frac{m}{2} \ln(\sigma^2) - \frac{1}{2 \sigma^2} \sum_{i=1}^m (z_i^{(s)})^2 \ .
\end{align}
$$

The posterior distribution of the random effect $\boldsymbol{z}$, $p(\boldsymbol{z} | \boldsymbol{y}; \theta^{old})$, is

$$
\begin{align}
p(\boldsymbol{z} | \boldsymbol{y}; \theta^{old}) \propto \exp \left\{ \sum_{i=1}^m \left[z_i y_{i\cdot} - \sum_{j=1}^n \ln(1 + e^{\beta x_{ij} + z_i}) - \frac{z_i^2}{2 \sigma^2}\right]\right\} \ ,
\end{align}
$$

where $y_{i\cdot} = \sum_{j=1}^n y_{ij}$ for $i=1,...,m$.

### Metropolis-Hastings

The Metropolis-Hastings (M-H) algorithm is employed to simulate random draws from the posterior distribution given by Eq.13. The short description of the M-H algorithm is given as follows.

>The M-H algorithm is a method used to construct Markov chains, which are used to generate sequences of statistical samples from probability distributions that are difficult to sample directly. If you can compute a function proportional to the probability distribution, you can get a sample from any probability distribution. Since it is very difficult to calculate the normalization coefficients in Bayesian applications, the M-H algorithm has the great advantage because it does not need to match the probability distribution we want to obtain, but only needs to be proportional to its density function.

The details of the M-H algorithm refer to [Bayesian Inference: Metropolis-Hastings Sampling](http://www.mit.edu/~ilkery/papers/MetropolisHastingsSampling.pdf).

In the logit-normal mixed model, we consider a Metropolis random walk sampler with normally distributed jump proposals, that is, the proposal density is

$$
\begin{align}
q(\boldsymbol{z}^{new} | \boldsymbol{z}^{old}) \propto \exp \left\{ - \frac{1}{2 \sigma^2} \| \boldsymbol{z}^{new} - \boldsymbol{z}^{old} \|^2_2 \right\} \ ,
\end{align}
$$

where $\boldsymbol{z}^{old}$ denotes the previous draw from the posterior distribution, and $\boldsymbol{z}^{new}$ is a candidate draw whose $k$ component is $z_k^{new}$, a generated new value, and the other components are the same as those of $\boldsymbol{z}^{old}$. Then the acceptance probability for the M-H algorithm is given by

$$
\begin{align}
A_k(\boldsymbol{z}^{old}, \boldsymbol{z}^{new}) = \min \left[1, \exp \left\{ \left(y_{k \cdot} - \frac{z_k^{new} + z_k^{old}}{2 \sigma^2} \right)(z_k^{new} - z_k^{old}) \right\} \prod_{j=1}^n \frac{1 + \exp (\beta x_{kj} + z^{old})}{1 + \exp (\beta x_{kj} + z^{new})} \right]
\end{align}
$$
