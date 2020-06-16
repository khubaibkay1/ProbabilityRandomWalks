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


task1(50,50)



# print(task1(10,10))

# import numpy as np

# p=[1/3,1/3,1/3]    
# p2=[1/3,1/3,1/3]


# def task2(distance,p1,p2,limit=10000,simtimes=10000,divisions=100):
#     choices = np.array([-1,0,1])
#     ans=np.empty(simtimes)
#     chunksize = simtimes//divisions
#     simtimes = chunksize * divisions
#     ans[:]=np.nan
#     for divnum in range(divisions):


#         temp=np.empty((chunksize,limit*2+1),dtype="int32")
#         moves1=np.random.choice(choices,(chunksize,limit),p=p1)
#         moves2=np.random.choice(choices,(chunksize,limit),p=p2)
#         temp[:,1::2]=moves1
#         temp[:,2::2]=-moves2
#         moves1=None
#         moves2=None
#         temp=np.cumsum(temp,axis=1) + distance
#         # print(temp[0])
#         lst=np.where(temp==0)
#         for element in range(len(lst[0])):
#             i,j=lst[0][element],lst[1][element]
#             if np.isnan(ans[divnum*chunksize+i]):
#                 ans[divnum*chunksize+i] = j

#         # print(np.where(temp==0))
#         # break
#     print(np.nanmean(ans))
    

# task2(1,p,p2)