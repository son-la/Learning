# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from _sqlite3 import Row
from pacman import GameState


class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        
        
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"
        
        if legalMoves[chosenIndex] == "Stop":
            if len(scores) > 1:
                scores.sort()
                bestScore = scores[len(scores) - 1]
                bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
                chosenIndex = random.choice(bestIndices) # Pick randomly among the best
            
        
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        
        
        position = newPos
        foodGrid = newFood
        col = len(foodGrid[:])
        row = len(foodGrid[0])
        
        if (manhattanDistance(newPos, newGhostStates[0].getPosition()) < 4):
            return 0
        if newFood.count() == 0:
            return 999
        #if (newScaredTimes[0] > 0):
        #    #Go toward ghosts
        #    return 999 - manhattanDistance(newPos, newGhostStates[0].getPosition())
        
        cnt = 1
        #Find closest food
        while (1):
            p0p = position[0] + cnt
            p0n = position[0] - cnt
            p1p = position[1] + cnt
            p1n = position[1] - cnt
    
            closestDistance = float("inf")
            found = False
            for c in range(p0n,p0p+1):
                if c>-1 and c < col:
                    for r in range(p1n,p1p+1):
                        if r>-1 and r < row:
                            if foodGrid[c][r] == True:
                                found = True
                                distance = manhattanDistance(newPos, [c,r])
                                if distance < closestDistance:
                                    closestDistance = distance
                        
            
            if found == True:
                break
            cnt += 1                        
                                    
        
        
        # Go toward foods, keep away from ghosts
        return 999 - closestDistance - newFood.count()*15
            
            
            
        
        #return successorGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.
        
          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        # Collect legal moves and successor states
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
        
        # Number of agents
        self.numOfAgents = gameState.getNumAgents()
        
        # First branches, get max
        scores = [self.value(gameState.generateSuccessor(self.index,action), 1) for action in legalMoves]
        
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best
                
        return legalMoves[chosenIndex]
        
    # evaluationFunction calls
    def value(self, state, depth):
        if depth == self.depth * self.numOfAgents:
            return self.evaluationFunction(state)
        if depth % self.numOfAgents == 0:
            return self.max_value(state, depth)
        else:
            return self.min_value(state, depth)
             
        
    # Player    
    def max_value(self, gameState, depth):
        
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
                
        if len(legalMoves) == 0:
            return self.evaluationFunction(gameState)
        v = -float("inf")
        for successor in [gameState.generateSuccessor(self.index, action) for action in legalMoves]:
            v = max(v, self.value(successor, depth + 1))
        return v
    
    # Opponents
    def min_value(self, gameState, depth):
        opponent_index = depth % self.numOfAgents
        
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(opponent_index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
                
        if len(legalMoves) == 0:
            return self.evaluationFunction(gameState)
        v = float("inf")
        for successor in [gameState.generateSuccessor(opponent_index, action) for action in legalMoves]:
            v = min(v, self.value(successor, depth + 1))        
        return v

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        # Collect legal moves and successor states
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
        
        # Number of agents
        self.numOfAgents = gameState.getNumAgents()
        
        alpha = -float("inf")
        
        # First branches, get max
        scores =[] 
        for action in legalMoves:
            beta = float("inf") # Reset beta, best value for minimizer
            score = self.value(gameState.generateSuccessor(self.index,action), 1, alpha, beta)
            alpha = max(alpha, score[0]) # Update alpha, best value for maximizer (Root)
            scores.append(score[0])
        
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best
                
        return legalMoves[chosenIndex]
    
    
    # evaluationFunction calls
    def value(self, state, depth, alpha, beta):
        if depth == self.depth * self.numOfAgents:
            return [self.evaluationFunction(state), alpha, beta]
        if depth % self.numOfAgents == 0:
            return self.max_value(state, depth, alpha, beta)
        else:
            return self.min_value(state, depth, alpha, beta)
            
            
    
    # Player    
    def max_value(self, gameState, depth, alpha, beta):
                
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
        # No more action, call evaluation function        
        if len(legalMoves) == 0:
            return [self.evaluationFunction(gameState), alpha, beta]
        
        
        v = -float("inf")
        for action in legalMoves:
            for successor in [gameState.generateSuccessor(self.index, action)]: 
                val = self.value(successor, depth + 1, alpha, beta)
                v = max(v, val[0])
                if v > beta: # Pruning
                    return [v, alpha, beta]
                alpha = max(alpha, v)
        return [v,alpha, beta]
    
    # Opponents
    def min_value(self, gameState, depth, alpha, beta):
        opponent_index = depth % self.numOfAgents      
        
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(opponent_index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
        # No more action, call evaluation function                
        if len(legalMoves) == 0:
            return [self.evaluationFunction(gameState), alpha, beta]
        
        
        v = float("inf")
        for action in legalMoves:
            for successor in [gameState.generateSuccessor(opponent_index, action)]: 
                val = self.value(successor, depth + 1, alpha, beta)
                v = min(v, val[0])
                if v < alpha: # Pruning
                    return [v, alpha, beta]
                beta = min(beta,v)        
        return [v, alpha, beta]
    
    
    

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        # Collect legal moves and successor states
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
        
        # Number of agents
        self.numOfAgents = gameState.getNumAgents()
        
        # First branches, get max
        scores = [self.value(gameState.generateSuccessor(self.index,action), 1) for action in legalMoves]
        
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best
                
        return legalMoves[chosenIndex]
        
    # evaluationFunction calls
    def value(self, state, depth):
        if depth == self.depth * self.numOfAgents:
            return self.evaluationFunction(state)
        if depth % self.numOfAgents == 0:
            return self.max_value(state, depth)
        else:
            return self.min_value(state, depth)
             
        
    # Player    
    def max_value(self, gameState, depth):
        
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(self.index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
                
        if len(legalMoves) == 0:
            return self.evaluationFunction(gameState)
        v = -float("inf")
        for successor in [gameState.generateSuccessor(self.index, action) for action in legalMoves]:
            v = max(v, self.value(successor, depth + 1))
        return v
    
    # Opponents
    def min_value(self, gameState, depth):
        opponent_index = depth % self.numOfAgents
        
        # Legal moves = all moves - "STOP"
        allMoves = gameState.getLegalActions(opponent_index)
        legalMoves = []
        for move in allMoves:
            if move != Directions.STOP:
                legalMoves.append(move)
                
                
        if len(legalMoves) == 0:
            return self.evaluationFunction(gameState)
        
        sum = 0.0
        for successor in [gameState.generateSuccessor(opponent_index, action) for action in legalMoves]:
            sum += self.value(successor, depth + 1)
        return sum/float(len(legalMoves))
        
        

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <Eat all food, keepaway from ghost, avoid get stuck>
    """
    "*** YOUR CODE HERE ***"
               
    # Useful information you can extract from a GameState (pacman.py)
    position = currentGameState.getPacmanPosition()
    foodGrid = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()
    #newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
    walls = currentGameState.getWalls()
    
    numOfRow = len(walls[0])
    numOfCol = walls.count()
    col = len(foodGrid[:])
    row = len(foodGrid[0])
    
    # Priority level:
    # 1. Win immediately
    # 2. Get stuck
    # 4. closest food
    
    # Eat all food
    if foodGrid.count() == 0:
        return 999
    
    # Avoid get stuck
    if foodGrid[position[0]][position[1]] == False:
        stuck = 0
        
        if position[0] > 0 :
            stuck += walls[position[0]-1][position[1]]
        
        if position[0] < numOfCol-1:    
            stuck += walls[position[0]+1][position[1]]
        
        if position[1] > 0:
            stuck += walls[position[0]][position[1]-1]
        
        if position[1] < numOfRow-1:
            stuck += walls[position[0]][position[1]+1]
        
        if stuck > 2:
            return 0; 
    
    
    # Chasing ghosts     
    
    bestGhostDistance = float("inf")
    bestGhostDistanceindex = -1
    for i in range(0, len(newGhostStates)):
        #if (newScaredTimes[i] > 0):
            #Go toward ghosts
        #        bestGhostDistance = min(bestGhostDistance, manhattanDistance(position, newGhostStates[i].getPosition()))
        #        bestGhostDistanceindex = i
        #else:
        #    print manhattanDistance(position, newGhostStates[i].getPosition())
        if (manhattanDistance(position, newGhostStates[i].getPosition()) < 3):
            return 0
                
    if bestGhostDistanceindex != -1:
        return 999 - bestGhostDistance
    
    
    cnt = 1
    #Find closest food
    while (1):
        p0p = position[0] + cnt
        p0n = position[0] - cnt
        p1p = position[1] + cnt
        p1n = position[1] - cnt

        closestDistance = float("inf")
        found = False
        for c in range(p0n,p0p+1):
            if c>-1 and c < col:
                for r in range(p1n,p1p+1):
                    if r>-1 and r < row:
                        if foodGrid[c][r] == True:
                            found = True
                            distance = manhattanDistance(position, [c,r])
                            if distance < closestDistance:
                                closestDistance = distance
                    
        
        if found == True:
            break
        cnt += 1                        
                                
    
    
    # Go toward foods, keep away from ghosts
    return 999 - closestDistance - foodGrid.count()*15

# Abbreviation
better = betterEvaluationFunction

