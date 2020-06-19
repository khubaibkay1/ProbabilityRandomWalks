import numpy as np

import scipy.stats as st
import math
import matplotlib.pyplot as plt
plt.style.use("ggplot")
# plt.style.use("seaborn-dark")


def task1(start,steps,left=1/3,stay=1/3,right=1/3,simtimes=10000):
    '''
    choices: Represents the directions in which the user can move
    left, stay, right : probability of doing that action
    simtimes: How many times to run the simulation
    steps: How many steps to do in each simulation
    Logic: 
        Use Random choice, to generate 'simtimes' simulations of 'steps' number of steps
        Then find the net movement in each simulation and add the starting point to each simulation
        that will give you the ending point of each simulation. Take the mean of that to get the expectation.
        The distribution of the distribution is Gaussian so a Gaussian curve is fitted to the histogram 
    '''
    choices=np.array([-1,0,1])

    moves=np.random.choice(choices,(simtimes,steps),p=[left,stay,right])
    turns=moves.sum(axis=1) + start
    plt.hist(turns,density=True,bins=50,color="#007ea7")
    
    # Draws a gaussian curve over the distribution
    mn, mx = plt.xlim()
    plt.xlim(mn, mx)
    kde_xs = np.linspace(mn, mx, 301)
    kde = st.gaussian_kde(turns)
    plt.plot(kde_xs, kde.pdf(kde_xs),color="#d81159")
    
    plt.ylabel('Probability')
    plt.xlabel('Distance')
    plt.title(f"Distribution of walks when steps = {steps}") 
    plt.show()
    return np.mean(turns)


print(task1(50,50))


