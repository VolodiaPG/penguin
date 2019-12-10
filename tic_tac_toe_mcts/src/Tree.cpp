#include "Tree.hpp"

namespace mcts
{

Tree::Tree(
    game::AbstractGame *game,
    game::AbstractPlayer *me,
    const MCTSConstraints &constraints)
    : playerMe(me),
      game(game),
      constraints(constraints)
{
    rootNode.player = playerMe;
    // rootNode = new Node(nullptr, me, nullptr, game);
}

Tree::~Tree()
{
    // if (rootNode)
    // {
    //     delete rootNode;
    // }
}

void Tree::begin()
{
    std::cout << "Beginning MCTS search" << std::endl;
    timer t;
    while (t.milliseconds_elapsed() < (unsigned long)constraints.time)
    {
        for (int ii = 0; ii < NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO; ++ii)
        {
            Node *promisingNode = selectBestChildAndDoAction(&rootNode);

            if (!game->isFinished())
            {
                expandNode(promisingNode);
            }

            Node *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            if (nodeToExplore != promisingNode)
            {
                doActionOnBoard(*nodeToExplore);
            }

            int winnerId = randomSimulation();

            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    DEBUG(rootNode.visits);
}

void Tree::expandNode(Node *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    game::AbstractPlayer *nextPlayer = game->getPlayerToPlay();

    std::cout << "id node created for player : " << nextPlayer->getId() << std::endl;

    for (game::AbstractBoardCell *move : game->board->getAvailableCells())
    {
        Node *node = new Node();
        node->parent = nodeToExpand;
        node->player = nextPlayer;
        node->targetedCell = move;

        nodeToExpand->childNodes.push_back(node);
    }
}

game::AbstractBoardCell *Tree::bestMove() const
{
    return nodeWithMaxVisits(&rootNode)->targetedCell;
}

Node *Tree::nodeWithMaxVisits(const Node *nodeFrom) const
{
    Node *chosen = nullptr;
    int max = -1;

    for (Node *node : nodeFrom->childNodes)
    {
        if (node->visits > max)
        {
            max = node->visits;
            chosen = node;
        }
    }

    return chosen;
}

double Tree::formula(
    const Node &node,
    const Node &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max()-1;
    if (nodeSuccessor.visits != 0)
    {
        // int multiplier = 1;
        // if (nodeSuccessor.player->getId() != playerMe->getId())
        // {
        //     multiplier = -1;
        // }
        ret = nodeSuccessor.score / (double)nodeSuccessor.visits +
              sqrt(2.0 * log((double)node.visits) / (double)nodeSuccessor.visits);
    }

    return ret;
}

void Tree::doActionOnBoard(const Node &nodeToGetTheActionFrom)
{
    std::cout << "played player#" << nodeToGetTheActionFrom.player->getId() << std::endl;
    game->play(nodeToGetTheActionFrom.player,
               nodeToGetTheActionFrom.targetedCell);
}

game::AbstractBoardCell *Tree::getRandomAvailableCellFromBoard() const
{
    std::vector<game::AbstractBoardCell *> cells = game->board->getAvailableCells();

    // random index ranging between 0 and cells.size() not included; (eg. 0 and 3, 3 not included)
    unsigned int index = rand() % cells.size();

    return cells[index];
}

void Tree::backPropagateAndRevertAction(int winnerId, Node *terminalNode)
{
    Node *node = terminalNode;

    while (node->parent != nullptr)
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

        game->revertPlay(node->targetedCell);

        node = node->parent;
    }
}

Node *Tree::randomChooseChildOrFallbackOnNode(Node *node) const
{
    Node *ret = node;
    if (node->childNodes.size())
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

int Tree::randomSimulation() const
{
    // 'convert' the two playes into random players (decisional)

    // save the actions done so we can revert them;
    std::queue<game::AbstractBoardCell *> playedCells;

    while (!game->isFinished())
    {
        game::AbstractBoardCell *cell = getRandomAvailableCellFromBoard();
        game->play(
            game->getPlayerToPlay(),
            cell);
        playedCells.push(cell);
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

Node *Tree::selectBestChildAndDoAction(Node *input)
{
    Node *ret = input;

    if (ret->parent != nullptr)
    {
        doActionOnBoard(*ret);
    }
    double interestingValue = std::numeric_limits<double>::lowest();
    bool (*strategy)(double, double) = isGreater;

    while (ret->childNodes.size() != 0)
    {
        Node *interestingToReturn = nullptr;

        // One child must be selected to further develop
        std::cout << "ret: " << ret << std::endl;
        for (Node *node : ret->childNodes)
        {
            double res = formula(
                *ret,
                *node);

            std::cout << res << std::endl;

            if (res == std::numeric_limits<double>::max())
            { // not explored yet
                interestingToReturn = node;
                break;
            }
            else if (strategy(res, interestingValue))
            {
                // update ret
                interestingValue = res;
                interestingToReturn = node;
            }
        }


        // if (ret->player->getId() == playerMe->getId())
        // {
        strategy = isGreater;
        interestingValue = std::numeric_limits<double>::lowest();
        // }
        // else
        // {
        //     strategy = isLower;
        //     interestingValue = std::numeric_limits<double>::max();
        // }

        // exclude the root node that doesn't have any action associated...


        // TODO NaN
        if (interestingToReturn->parent != nullptr)
        {
            doActionOnBoard(*interestingToReturn);
        }
        ret = interestingToReturn;
    }

    return ret;
}

} // namespace mcts