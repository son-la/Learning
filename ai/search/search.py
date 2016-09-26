# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@1cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"

    "Fringe stack LIFO"
    mStack = util.Stack()
    
    #Push start state
    #State = coordiate,history,cost
    mStack.push((problem.getStartState(), [], 0))
                
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST

    #Implemented set
    old = set()

    action = None
    while (not(mStack.isEmpty())):
        #Executed succesor
        action = mStack.pop()
        
        #Add executed successor to implemented set
        old = old.union(set([action[0]]))

        
        #Check goal?
        if not(problem.isGoalState(action[0])):
            
            #Check successors
            for ss in problem.getSuccessors(action[0]):
                
                #Avoid turn back immediately
                if len(old.intersection(set([ss[0]]))) != 0:
                    continue
                    
                #Keep track to current node (Previous actions until this node)
                history = list(action[1])
                #Append new move
                history.append(ss[1])

                #Initialize successor
                m = [ss[0],history]
                #Push to stack
                mStack.push(m)
        else:
            break
        

    #Return track
    return action[1]

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"

    "Fringe queue FIFO"
    mQueue = util.Queue()
    
    #Push start state
    #State = coordiate,history,cost
    mQueue.push((problem.getStartState(), [], 0))
                
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST

    #Implemented set
    old = set()

    action = None
    while (not(mQueue.isEmpty())):
        #Executed succesor
        action = mQueue.pop()
        
        #Avoid checking twice       
        if action[0] in old:
            continue

        #Add executed successor to implemented set
        old = old.union(set([action[0]]))
        
        #Check goal?
        if not(problem.isGoalState(action[0])):
            
            #Check successors
            for ss in problem.getSuccessors(action[0]):
                
                #Get track to current node 
                history = list(action[1])
                #Append new move
                history.append(ss[1])
                    
                #Initialize successor
                m = [ss[0],history]
                #Push to stack
                mQueue.push(m)
        else:
            break
        

    #Return track
    return action[1]
    
def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    "Priority Queue"
    mStack = util.PriorityQueue()
    
    #Push start state
    #State = (coordiate,history,cost) priority
    # cost = priority
    mStack.push((problem.getStartState(), [], 0), 0)
                
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST

    #Implemented set
    old = set()

    action = None
    while (not(mStack.isEmpty())):
        #Executed succesor
        action = mStack.pop()
        
        #Avoid checking twice
        if action[0] in old:
            continue;

        #Add executed successor to implemented set
        old = old.union(set([action[0]]))

        
        #Check goal?
        if not(problem.isGoalState(action[0])):
            
            #Check successors
            for ss in problem.getSuccessors(action[0]):
                                
                #Get track to current node
                history = list(action[1])
                #Append new move
                history.append(ss[1])

                #Initialize successor
                m = [ss[0],history, action[2] + ss[2]]
                #Push to stack
                mStack.push(m, m[2]) # Cost = priority
        else:
            break
        

    #Return track
    return action[1]

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    "Priority Queue"
    mStack = util.PriorityQueue()
    
    #Push start state
    #State = coordiate,history,cost
    mStack.push((problem.getStartState(), [], 0), heuristic(problem.getStartState(), problem))
                
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST

    #Implemented set
    old = set()

    action = None
    while (not(mStack.isEmpty())):
        
        #Executed succesor
        action = mStack.pop()

        #Avoid checking twice
        if action[0] in old:
            continue

        #Add executed successor to implemented set
        old = old.union(set([action[0]]))

        
        #Check goal?
        if not(problem.isGoalState(action[0])):
            
            #Check successors
            for ss in problem.getSuccessors(action[0]):
                
                #Get track to current node
                history = list(action[1])
                #Append new move
                history.append(ss[1])

                #Initialize successor
                m = [ss[0],history, action[2] + ss[2]]

                #Push to stack
                mStack.push(m, m[2] + heuristic(ss[0], problem))
        else:
            break
        

    #Return track
    return action[1]
    


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
