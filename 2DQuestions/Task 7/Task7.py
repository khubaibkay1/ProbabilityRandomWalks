import numpy as np
import subprocess
import matplotlib.pyplot as plt

# Assign r in tuples (value, probability)
r=[(0,1/3),(0.5,1/3),(1,1/3)]
steps=10000


with open("rprobabilities.txt","w") as f:
    with open("rvalues.txt","w") as f2:
        for i,values in enumerate(r):
            if i ==len(r)-1:
                f2.write(str(values[0]))
                f.write(str(values[1]))
            else:
                f2.write(str(values[0])+"\n")
                f.write(str(values[1])+"\n")
with open("steps.txt","w") as f:
    f.write(str(steps))
    
subprocess.call("task7.exe",shell=True)
data=open("task7data.txt","r").readlines()
a=np.array([[float(i) for i in coord.strip().split(",")] for coord in data])
# print(a)
plt.style.use("ggplot")
x = a[:,0]

y = a[:,1]
print(np.sum(np.square(x)+np.square(y)>10000))
# Set up the axes with gridspec
fig = plt.figure(figsize=(6, 6))
grid = plt.GridSpec(4, 4, hspace=1, wspace=1)
main_ax = fig.add_subplot(grid[:-1, 1:])
y_hist = fig.add_subplot(grid[:-1, 0], xticklabels=[], sharey=main_ax)
x_hist = fig.add_subplot(grid[-1, 1:], yticklabels=[], sharex=main_ax)

# scatter points on the main axes





angles=np.linspace(0,2*np.pi,1000)
main_ax.set_xlabel("x")
main_ax.set_ylabel("y")
main_ax.scatter(x, y, alpha=0.2)
np.linspace(0,2*np.pi,1000)
main_ax.plot(100*np.sin(angles),100*np.cos(angles))
# histogram on the attached axes
x_hist.hist(x, 40,
            orientation='vertical')
x_hist.invert_yaxis()

y_hist.hist(y, 40,
            orientation='horizontal')
y_hist.invert_xaxis()

fig.savefig("Task7.png")