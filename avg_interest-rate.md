Let's assume we have a changing daily rate `a` for many days.
The final amount `x` (not counting payments in or out) could than be 
```math
x = x_0 · (1+a_1)·(1+a_2)·(1+a_3)·…
```
for days `1`, `2`, `3`.
An effective rate over `n` days can be calculated
```math
x = x_0 · (1+a_{eff})^n
```

Now, on the nth day, define 
```math
k = \frac{x}{x_0}
```
as the total change.
The effective daily rate is than
```math
k = (1+a_{eff})^n \\
a_{eff} = k^{\frac{1}{n}} - 1
```

To annualise the rate, a_eff must be risen by the power of days `D`=365.25 of the year:
```math
\left( 1 + a_{eff} \right)^D = (1 + a_y)\\
a_y = \left(1 + a_{eff}\right)^D -1 \\
\\

a_y = k^{\frac{D}{n}} -1
```

