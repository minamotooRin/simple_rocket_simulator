from turtle import color
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":

    arr = np.loadtxt('output.txt', delimiter=' ')

    t = arr[:, 0]
    h = arr[:, 1]
    v = arr[:, 2]
    m = arr[:, 3]

    plt.subplots_adjust(wspace = 1, hspace = 1)

    plt.subplot(3, 1, 1)
    plt.plot(t, h, color = 'red')
    plt.title("time - height")

    plt.subplot(3, 1, 2)
    plt.plot(t, v, color = 'green')
    plt.title("time - velocity")

    plt.subplot(3, 1, 3)
    plt.plot(t, m, color = 'blue')
    plt.title("time - mass")

    plt.savefig("figure.png")
    plt.show()