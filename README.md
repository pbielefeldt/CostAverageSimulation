# TotalReturnSimulation
How does the total return of financial investment depend not only on the yield, but on the spread of yields?

--- 

I wondered about how the spread of yields influences the overall performance.
If you talk to bank/insurance people, they will always point to the average yield.
And that's probably fine, as it is the quantity everyone can understand.
However, if I have an investment for 30 years, and it has an average rate of return of 6% p.a., the total amount of money I got in the end should depend on the spread of returns, shouldn't it?
If the investment performs very well for the first years, but worse later, the compound interest effect should help me a bit and vice versa …

To investigate this, I started this cute little tool.
Feel free to use it and send me improvements.

### Some Results:
Here are some results of my simulation. 
All pictures show the result of 250k individual runs.
Each time, the final value of the virtual securities account is show, for
__30 years__ (or months or any quantity of time) during which every year, 
__100 EUR__ (or USD or whatever)were banked. 
Think of a funds saving plan, if you like. 
The total amount paid is 30×100 € = __3000 €__.

It is assumed that the _average_ yield is about 8%.
(Which is arguably high, feel free to take another value).
The actual yield every year (or other unit time) varies, following a gaus normal distribution.
When I say "the yield is  (8±4)%", it means, the average is 8%, and the gaus σ is 4%.
I.e., in 68,3% of all years, the simulated yield is between 4% and 12%, in 99,7% of the years it is within -4% and 20% and so forth.

The *y*-axis of the histogram shows how often a certain final amount was received in the 250 000 runs.

An exponentially modified gaussian distribution is fitted to the value.
It describes the input variation as well as the exponential component of the compound interest.
Its parameter mu describes the most probable value—the value an investor is most likely to receive.

For a very small variation of the annual yield of 1% (at 8% average), the result is:
![08_01](https://user-images.githubusercontent.com/13000622/55683302-78244c80-593e-11e9-906c-c40da8b30334.gif "(8±1)%")
As expected, the histogram shows a sharp peak around the average value.

For (8±4)%, the curve gets a bit broader:
![08_04](https://user-images.githubusercontent.com/13000622/55683303-78244c80-593e-11e9-9bb6-ce9262ce7e7b.gif "(8±4)%")

At (8±8)% and above, the asymmetry of the curve can be seen by eye:
![08_08](https://user-images.githubusercontent.com/13000622/55684432-a9a31500-594a-11e9-8764-3af43eee9c6f.gif "(8±8)%")
Due to the compound interest effect, very high gains early in the run lead to very high final amounts.

Since the same is true in the opposite direction, the mean value however decreases.
For an investment with relatively high variance, yield (8±12)%, the most probable result is only 6219 €, 39% less than the 10260 € from the (8±4)%-simulation:
![08_12](https://user-images.githubusercontent.com/13000622/55683305-78bce300-593e-11e9-993b-dcd5f14501a1.gif "(8±12)%")

In the case of a yield of (8±16)%, the effect is even more pronounced:
![08_16](https://user-images.githubusercontent.com/13000622/55683306-78bce300-593e-11e9-9fd8-c56873c7be41.gif "(8±16)%")


### "Installation"
This is only a script that was intended to be executed with [ROOT](https://root.cern.ch/ "ROOT web page").
If you have ROOT installed, execute it by running `root TotalReturnSim.C+`.
