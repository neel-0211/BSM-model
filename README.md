# BSM-model

## History of the Black-Scholes Model:
Developed in 1973 by Fischer Black, Robert Merton and Myron Scholes, the BlackScholes model was the first widely used mathematical method to calculate the  theoretical value of an option contract. Black-Scholes posits that instruments, such as stock shares or futures contracts will  have a lognormal distribution of prices following a random walk with constant drift and volatility. The Black-Scholes equation requires five variables. These inputs are volatility, the  price of the underlying asset, the strike price the option, the time until expiration of  the option, and the risk-free interest rate.

## The Black-Scholes model makes certain assumptions:
1. No dividends are paid out during the life of the option.
2. Markets are random (i.e., market movements cannot be predicted).
3. There are no transaction costs in buying the option.
4. The risk-free rate and volatility of the underlying asset are known and constant.
5. The returns on the underlying asset are log-normally distributed.
6. The option is European and can only be exercised at expiration.

## Libraries used:
1. iostream 
2. cmath
3. string

## Input variables:
* Underlying price (per share)
* Strike price of the option (per share)
* Time to maturity (years)
* Continuously compounding risk-free interest rate (%)
* Volatility (%) or option price

## Output:
Summary and Greeks (Delta, Gamma, Vega, Rho, Theta) of the option.
