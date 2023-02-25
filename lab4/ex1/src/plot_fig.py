from matplotlib import pyplot as plt

x1 = [667.894, 3953.59, 36801.1, 637771]
x2 = [149.635, 5631.76, 11527.1, 249333]

y = ["27", "81", "243", "729"]

plt.plot(y, x1, color="r", linestyle="--", label="$\log_5N$")
plt.plot(y, x2, color="b", linestyle="-.", label="$\log_7N$")
plt.title("time-scale")
plt.xlabel("n")
plt.ylabel("time")

plt.grid(linestyle=":")
plt.savefig("time_scale.png")
plt.show()

