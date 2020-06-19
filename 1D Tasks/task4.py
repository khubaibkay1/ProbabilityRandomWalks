import numpy as np

import scipy.stats as st
import math
import matplotlib.pyplot as plt
plt.style.use("seaborn-dark")


def task4(start,steps,simtimes=10000):
    '''
    simtimes: How many times to run the simulation
    steps: How many steps to do in each simulation
    Logic: 
        Since the movement is modelled by uniform random variable between 0 and 1
        np.random.uniform to generation 'simtimes' simulations of 'steps' number of steps
        Then find the net movement in each simulation and add the starting point to each simulation
        that will give you the ending point of each simulation. Take the mean of that to get the expectation.
        The distribution of the distribution is Gaussian so a Gaussian curve is fitted to the histogram 
    '''
    moves=np.random.uniform(size=(simtimes,steps))
    turns=moves.sum(axis=1) + start
    plt.hist(turns,density=True,bins=50,color="#007ea7")
    # Draws Gaussian curve over the distribution
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


task4(0,50)