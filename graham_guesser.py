#!/usr/bin/env python
# -*- coding: utf-8 -*-
import math

book_factor = 1.5 # usual price-to-book ratio, typical: 1.5
earnings_factor = 12 # usual price-to-earings ratio, typical: 12

sigma = 15 # percent offset (up/down)

book_value = float(input("total equity: "))
earnings_value = float(input("annual earnings: "))
fundamental_value = math.sqrt(book_factor*book_value*earnings_factor*earnings_value)

price = float(input("current price: "))

if price < (1-(sigma/100))*fundamental_value :
	print("According to the Graham formula, the asset is traded below its fundamental value of {0:.3f}.".format(fundamental_value)) 
elif price > (1+(sigma/100))*fundamental_value :
	x = 100*(price-fundamental_value)/fundamental_value
	print("According to the Graham formula, the asset is overpriced by about {0:.1f} %".format(x))
else :
	print("The asset is traded close to its Graham fundamental value of {0:.3f}.".format(fundamental_value)) 
