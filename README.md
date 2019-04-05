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

### Some image:
yield: 6%
spread 1.5%
![06.0-pm-01.5](https://user-images.githubusercontent.com/13000622/55651724-dab80400-57e9-11e9-9a4d-a8b55725efaf.gif)

yield 6%
spread 3%
![06.0-pm-03](https://user-images.githubusercontent.com/13000622/55651851-2cf92500-57ea-11e9-98cd-1f04b1d1a404.gif)

### "Installation"
This is only a script that was intended to be executed with [ROOT](https://root.cern.ch/ "ROOT web page").
If you have ROOT installed, execute it by running `root TotalReturnSim.C`.
