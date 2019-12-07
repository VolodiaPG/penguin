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
            Node_bis *promisingNode = selectBestChildAndDoAction(&rootNode);

            if (!game->isFinished())
            {
                expandNode(promisingNode);
            }

            Node_bis *nodeToExplore = randomChooseChildOrFallbackOnNode(promisingNode);

            if (nodeToExplore != promisingNode)
            {
                game->play(
                    nodeToExplore->player,
                    nodeToExplore->targetedCell);
            }
            int winnerId = randomSimulation(nodeToExplore);

            backPropagateAndRevertAction(winnerId, nodeToExplore);
        }
    }

    DEBUG(rootNode.visits);
}

void Tree::expandNode(Node_bis *nodeToExpand)
{
    // the turn has already been played, now it's the next player's turn
    game::AbstractPlayer *nextPlayer = game->getPlayerToPlay();
    for (game::AbstractBoardCell *move : game->board->getAvailableCells())
    {
        Node_bis *node = new Node_bis();
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

Tree::Node_bis *Tree::nodeWithMaxVisits(const Node_bis *nodeFrom) const
{
    Node_bis *chosen = nullptr;
    int max = -1;

    for (Node_bis *node : nodeFrom->childNodes)
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
    const Node_bis &node,
    const Node_bis &nodeSuccessor) const
{
    double ret = std::numeric_limits<double>::max();
    if (nodeSuccessor.visits != 0)
    {
        ret = (double)nodeSuccessor.score / (double)nodeSuccessor.visits +
              sqrt(2.0 * log((double)node.visits) / (double)nodeSuccessor.visits);
    }

    return ret;
}

void Tree::doActionOnBoard(const Node_bis &nodeToGetTheActionFrom)
{
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

void Tree::backPropagateAndRevertAction(Node_bis &terminalNode)
{
    int stateOfGame = game->checkStatus();

    Node_bis *node = &terminalNode;
    do
    {
        ++node->visits;
        if ((int)node->player->getId() == stateOfGame)
        {
            node->score += INCREMENT_VICTORY;
        }
        else if (stateOfGame == -1)
        {
            node->score += INCREMENT_DRAW;
        }
        else
        {
            node->score += INCREMENT_DEFEAT;
        }

        game->revertPlay(node->targetedCell);

    } while ((node = node->parent) != nullptr);
}

Tree::Node_bis *Tree::randomChooseChildOrFallbackOnNode(Node_bis *node) const
{
    Node_bis *ret = node;
    if (node->childNodes.size())
    {
        unsigned int index = rand() % node->childNodes.size();
        ret = node->childNodes[index];
    }

    return ret;
}

int Tree::randomSimulation(Node_bis* nodeFrom) const
{
    // 'convert' the two playes into random players (decisional)

    // save the actions done so we can revert them;
    std::stack<game::AbstractBoardCell *> playedCells;

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
        game->revertPlay(playedCells.top());
        // remove the element
        playedCells.pop();
    }

    return winner;
}

Tree::Node_bis *Tree::selectBestChildAndDoAction(Node_bis *input)
{
    Node_bis *ret = input;

    if (ret->targetedCell)
    {
        game->play(
            ret->player,
            ret->targetedCell);
    }

    while (ret->childNodes.size() != 0)
    {
        double max = std::numeric_limits<double>::min();
        Node_bis *temp = ret;
        // One child must be selected to further develop
        for (Node_bis *node : ret->childNodes)
        {
            double res = formula(
                *ret,
                *node);

            if (res > max)
            {
                // update ret
                max = res;
                temp = node;
            }
        }

        ret = temp;

        // exclude the root node that doesn't have any action associated...
        if (ret->targetedCell)
        {
            game->play(
                ret->player,
                ret->targetedCell);
        }
    }

    return ret;
}

} // namespace mcts