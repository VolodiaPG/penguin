#include "mcts.hpp"

namespace mcts
{

MCTS::MCTS(game::AbstractGame* game,
    mcts::Tree* tree,
    const MCTSConstraints &constraints)
    : constraints(constraints),
      game(game),
      tree(tree)
{
    
}
 
MCTS::~MCTS()
{

}

void MCTS::begin()
{
    std::cout << "Beginning MCTS search" << std::endl;
    timer t;
    root = tree->getRootNode();
    
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            //std::cout << "Selection" << std::endl;
            Node *promisingNode = selectBestChildAndDoAction(root);

            //std::cout << "Expand" << std::endl;
            if (!game->isFinished())
            {

                expandNode(promisingNode);
            }

            //std::cout << "Random" << std::endl;
            Node *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            //std::cout << "Do Action" << std::endl;
            if (nodeToExplore != promisingNode)
            {
                doActionOnBoard(*nodeToExplore);
            }

            //std::cout << "Simulation" << std::endl;
            int winnerId = randomSimulation();

            //std::cout << "Backprop" << std::endl;
            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    DEBUG(root->visits);
}

void MCTS::expandNode(Node *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    game::AbstractPlayer *nextPlayer = game->getPlayerToPlay();

    for (game::AbstractBoardCell *move : game->board->getAvailableCells())
    {
        Node *node = new Node();
        node->parent = nodeToExpand;
        node->player = nextPlayer;
        node->targetedCell = move;

        nodeToExpand->childNodes.push_back(node);
    }
}

double MCTS::formula(
    const Node &node,
    const Node &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = nodeSuccessor.score / (double)nodeSuccessor.visits +
              sqrt(2.0 * log((double)node.visits) / (double)nodeSuccessor.visits);
    }

    return ret;
}

void MCTS::doActionOnBoard(const Node &nodeToGetTheActionFrom)
{
    game->play(nodeToGetTheActionFrom.player,
               nodeToGetTheActionFrom.targetedCell);
}

game::AbstractBoardCell *MCTS::getRandomAvailableCellFromBoard() const
{
    std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();
    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    if(cells.size() == 0) throw -1;
    unsigned int index = rand() % cells.size();

    return cells[index];
}

void MCTS::backPropagateAndRevertAction(int winnerId, Node *terminalNode)
{
    Node *node = terminalNode;

    // iterate until the root node, not excluded tho!
    do
    {
        double increment = INCREMENT_DEFEAT;
        if ((int)node->player->getId() == winnerId)
        { // victory
            increment = INCREMENT_VICTORY;
        }
        else if (winnerId == -1)
        { // draw
            increment = INCREMENT_DRAW;
        }
        node->visits++;

        node->score += increment;
        if (node->parent)
        { // make sure we don't play the rootnode, otherwise things will get messy very quickly!
            game->revertPlay(node->targetedCell);
        }
        
    } while ((node = node->parent) != nullptr);
}

Node *MCTS::randomChooseChildOrFallbackOnNode(Node *node) const
{
    Node *ret = node;
    if (node->childNodes.size() != 0)
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

int MCTS::randomSimulation() const
{
    // save the actions done so we can revert them;
    std::queue<game::AbstractBoardCell *> playedCells;

    while (!game->isFinished())
    {
        try{
        game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
        game->play(
            game->getPlayerToPlay(),
            cell);
        playedCells.push(cell);
        }catch(int code){}
    }

    // check the victory
    int winner = game->checkStatus();

    // revert the random game
    while (!playedCells.empty())
    {
        game->revertPlay(playedCells.front());
        // remove the element
        playedCells.pop();
    }

    return winner;
}

Node *MCTS::selectBestChildAndDoAction(Node *input)
{
    Node *ret = input;
    
    if(!ret->isRoot)
    {
        doActionOnBoard(*ret);
    }
    
    while (ret->childNodes.size() != 0)
    {
        Node *interestingToReturn = nullptr;
        double interestingValue = std::numeric_limits<double>::lowest();

        // One child must be selected to further develop
        for (Node *node : ret->childNodes)
        {
            double res = formula(
                *ret,
                *node);
            
            if (res > interestingValue)
            {
                // update ret
                interestingValue = res;
                interestingToReturn = node;
            }
        }
        
        // exclude the root node that doesn't have any action associated...
        if(!interestingToReturn->isRoot)
        {
            doActionOnBoard(*interestingToReturn);
        }
        ret = interestingToReturn;
    }
    
    return ret;
}

}