import numpy as np
import subprocess
import scipy.stats as st
import math
import matplotlib.pyplot as plt
plt.style.use("ggplot")
# plt.style.use("seaborn-dark")

subprocess.call("task8.exe")
x=np.array([int (i) for i in open("task8.txt").readlines()])

# plt.hist(x,density=True)
plt.hist(x,density=True,bins=50,color="#007ea7")
print(np.mean(x))
# kde_xs = np.linspace(mn, mx, 301)
# kde = st.gaussian_kde(turns)

# plt.plot(kde_xs, kde.pdf(kde_xs),color="#d81159")
plt.ylabel('Probability')
plt.xlabel('Distance')
plt.title("How many steps are needed") 
    
plt.show()