#include "Node.hpp"

#include "BoardCell.hpp"

namespace mcts
{
Node::Node(Node *parent, game::AbstractPlayer *player, game::AbstractBoardCell *targetedCell)
    : parent(parent), player(player), targetedCell(targetedCell)
{
}

Node::~Node()
{
    for (Node *node : childNodes)
    {
        delete node;
    }
}

double Node::formula(int winsSuccessor, int numberVisitsSuccessor, int numberVisitsFather)
{
    if (numberVisitsSuccessor == 0)
    {
        return std::numeric_limits<double>::max();
    }

    return (double)winsSuccessor / (double)numberVisitsSuccessor + sqrt(2.0 * log((double)numberVisitsFather) / (double)numberVisitsSuccessor);
}

Node *Node::selectBestChildAndDoAction(game::AbstractBoard *board)
{
    Node *ret = this;

    if (ret->targetedCell)
    {
        ret->doAction(board);
    }

    while (ret->childNodes.size() != 0)
    {
        int parentVisits = ret->visits;

        double max = std::numeric_limits<double>::min();
        Node *temp = ret;
        // One child must be selected to further develop
        for (Node *node : ret->childNodes)
        {
            double res = formula(
                node->victories,
                node->visits,
                parentVisits);

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
            ret->doAction(board);
        }
    }

    return ret;
}

bool Node::doAction(game::AbstractBoard *board)
{
    // do our move
    return board->performMove(player->getId(), targetedCell);
}

void Node::revertAction(game::AbstractBoard *board)
{
    return board->revertMove(targetedCell);
}

int Node::randomSimulation(game::AbstractGame *game) const
{
    // 'convert' the two playes into random players (decisional)
    game::RandomPlayer player1(game->player1->getId()), player2(game->player2->getId());

    // save the actions done so we can revert them;
    std::stack<game::AbstractBoardCell *> playedCells;

    while (!game->isFinished())
    {
        playedCells.push(game->play(&player1, &player2));
    }

    // check the victory
    int winner = game->board->checkStatus();

    // revert the random game
    while (!playedCells.empty())
    {
        game->revertPlay(playedCells.top());
        // remove the element
        playedCells.pop();
    }

    return winner;
}

void Node::backPropagateAndRevertAction(const int winnerId, game::AbstractBoard *board)
{
    ++visits;
    if (winnerId == (const int)player->getId())
    {
        victories++;
    }
    else if (winnerId == -1)
    { // a draw is a victory for both player1 & 2
        victories++;
    }

    if (parent != nullptr)
    {
        revertAction(board);

        // backpropagate again
        parent->backPropagateAndRevertAction(winnerId, board);
    }
}

Node *Node::nodeWithMaxVisits() const
{
    Node *chosen = nullptr;
    int max = -1;
    // int totalVisits = 0;
    // DEBUG(childNodes.size());

    for (Node *node : childNodes)
    {
        // totalVisits += node->visits;
        // DEBUG(node->visits);
        // DEBUG(node->victories);
        if (node->visits > max)
        {
            max = node->visits;
            chosen = node;
            // const game::Position &pos = ((game::BoardCell *)chosen->targetedCell)->getPosition();
            // DEBUG(max);
            // DEBUG(pos.x);
            // DEBUG(pos.y);
        }
    }
    // DEBUG(totalVisits);

    return chosen;
}

Node *Node::randomChooseChildOrDefaultMe()
{
    Node *ret = this;
    if (childNodes.size())
    {
        unsigned int index = rand() % childNodes.size();
        ret = childNodes[index];
    }

    return ret;
}

void Node::expandNode(std::vector<game::AbstractBoardCell *> possibleMove, game::AbstractPlayer *nextPlayer)
{
    for (game::AbstractBoardCell *move : possibleMove)
    {
        Node *node = new Node(this, nextPlayer, move);
        childNodes.push_back(node);
    }
}

} // namespace mcts