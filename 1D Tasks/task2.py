import numpy as np
import time
p=[1/3,1/3,1/3]    
p2=[1/3,1/3,1/3]
import matplotlib.pyplot as plt
# plt.style.use("ggplot")

plt.style.use("seaborn-dark")

def task2(distance,p1,p2,timeout=20,simtimes=10000):
    '''
    choices: Represents the directions in which the user can move
    p1: Probability of motion for Person 1
    p2: Probability of motion for Person 2
    simtimes: How many times to run the simulation
    timeout : after how many seconds to stop simulation
    limit: Max number of steps per user in which they are expected to meet
    Logic: 
        Use Random choice, to generate 'simtimes' simulations of 'steps' number of steps of Person 1 and 2 move
        Make an array to store the movement, whether close to each other or further.
        Where 0 index means start, odd indices means person 1 movement,other even indices mean person 2 movement,
        Then take the cumulative sum to see the change in distance at each step.
        and add the starting distance to each simulation
        Then see whether there is a step where distance is 0. 
        Take the mean of all those step where they first met to get the expectation.
        The distribution seems to fit that of an exponential decay function 
    Assumption:
        One person can move at a time. Limited number of steps. If it doesn't meet there, it won't meet.
        We ignore the times when time to meet is very high
    '''
    start=time.time()
    choices = np.array([-1,0,1])
    difference=np.zeros(simtimes) + distance
    left= difference!=0
    factor=1
    numberofsteps=np.zeros(simtimes)
    start=time.time()
    
    while np.sum(left)!=0 and time.time() -start <=timeout:
        if factor==1:
            difference[left]+=np.random.choice(choices,np.sum(left),p=p1)
        else:
            difference[left]-=np.random.choice(choices,np.sum(left),p=p2)
         # plt.yscale("log")
        factor*=-1
        numberofsteps[left]+=1
        left= difference !=0
    
    ans= numberofsteps[~left]
    
    plt.hist(ans,density=True,bins=100,color="#007ea7")
    plt.xlim(np.min(ans)-0.2,np.max(ans)+0.2)
    plt.ylabel('Probability')
    plt.xlabel('Steps taken to meet')
    plt.title(f"Distribution of time to meet when distance = {distance}") 
    plt.show()
    return (np.nanmean(ans))

        
print(task2(100,p,p2))
