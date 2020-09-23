#!/usr/bin/env python
# -*- coding: utf-8 -*-

n   = 365.
x_0 = 100.
x   = 110.

D   = 365.25

k   = x/x_0

a_y = pow(k,D/n) - 1.

print(a_y)
