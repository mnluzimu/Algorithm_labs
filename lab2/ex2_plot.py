import numpy as np
import matplotlib.pyplot as plt

x = ['10', '15', '20', '25', '30']
# x = ['2', '3', '5']
# plt.figure(figsize=(5, 3), dpi=300)
# plt.xticks(x)
# y1 = [0.000195, 0.000203, 0.000211, 0.000223, 0.000222]
# y2 = [0.765, 0.773, 0.741, 0.699, 0.711]
y = [0.312339,
0.668034,
1.180046,
1.788332,
2.636970]
# x = np.arange(len(y7))
plt.plot(x, y, color='r', linestyle='-.',
         marker='>', label=r'$time(us)$')
# plt.plot(x, x, color='k', linestyle='None',
#          marker = '+', label=r'$x$')
# plt.plot(x, x * np.log(x), color='b', linestyle='None',
#          marker = '<', label=r'$x\log(x)$')
# plt.plot(x, x ** 2, color='c', linestyle='None',
#          marker = 's', label=r'$x^{2}$')
plt.xlabel('scale'); plt.ylabel('$time(us)$')
plt.title("$time(us)$-scale")
plt.legend(); plt.grid(linestyle=':')
plt.savefig("ex2.png")
plt.show()