import matplotlib.pyplot as plt
import numpy as np

# Intel Core™ i5-6600 CPU, Ubuntu 16.10

x    = [   100,    1000,    10000,    100000]
##############################################################################################
bfse = [   646,   10446,  103250,   1249891] # boost' flat_set with emplace_hint
svsb = [  1028,   14274,  141462,   1413630] # std::vector with insert_unique (back check)
bfsi = [  2098,   30042,  381098,   4568955] # boost' flat_set with insert
svsn = [  1985,   31368,  412077,   4845256] # std::vector with insert_unique
stds = [ 10440,  183646, 2095243,  35038916] # std::set with emplace_hint
stdu = [ 14119,  159966, 2103225,  41113434] # std::unordered_set
stsi = [ 12179,  175546, 2669882,  58153824] # std::set with insert

plt.style.use('ggplot')
plt.plot(x, bfse, '-xk', label='boost::flat_set::emplace_hint')
plt.plot(x, bfsi, '-hg', label='boost::flat_set::insert')
plt.plot(x, svsb, '-o', label='std::vector::insert_unique (with back() check)')
plt.plot(x, svsn, '-v', label='std::vector::insert_unique')
plt.plot(x, stds, '-8', label='std::set::emplace_hint')
plt.plot(x, stsi, '-*', label='std::set::insert')
plt.plot(x, stdu, '-s', label='std::unordered_set::insert')
plt.xscale('log')
plt.yscale('log')
plt.legend(loc=2)
plt.show()





