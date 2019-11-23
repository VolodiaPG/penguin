#include "Node.hpp"

#include "BoardCell.hpp"

namespace mcts
{
Node::Node(Tree *tree, Node *parent, const State &state)
    : parentNode(parent), tree(tree), state(state)
{
    //TODO handle myAction nullity

    if (this->state.associatedPlayer != nullptr && this->parentNode != nullptr)
    {
        this->state.associatedPlayer = this->tree->game->getNextPlayer(
            this->parentNode->getState()
                .associatedPlayer);
    }
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
    if (!numberVisitsSuccessor)
    {
        return std::numeric_limits<double>::max();
    }
    return (double)winsSuccessor / (double)numberVisitsSuccessor + sqrt(2) * sqrt(log((double)numberVisitsFather) / (double)numberVisitsSuccessor);
}

void Node::selection()
{
    Node *chosenNode = nullptr;

    // execute my action
    executeMyAction();

    // check if it is a terminal node, ie win or draw / lost
    if (tree->game->isFinished())
    {
        // time to propagate before banning access to this node!

        // check the victory
        int won = tree->game->board->checkStatus() == (int)tree->playerMe->getId();

        // draw or lose (-1 for draw)
        if (!won)
        {
            won = tree->game->board->checkStatus() == -1 ? 0 : -1;
        }

        backpropagation(won);
        // isFullyDone = true;
    }
    else
    {
        // case of children
        if (childNodes.size())
        {
            double max = 0.0;
            // bool hasIterated = false;

            // select the node that has the most value using the selection formula
            for (Node *node : childNodes)
            {
                // if (!node->isFullyDone)
                // {
                double res = formula(node->totalVictories, node->totalScenarii, parentNode ? parentNode->totalScenarii : 0);

                if (res >= max)
                {
                    max = res;
                    chosenNode = node;
                }

                // hasIterated = true;
                // }
            }

            // if didn' iterate, then we are a terminalNode
            // if (!hasIterated)
            // {
            //     isFullyDone = true;
            // }

            // make sure not null
            if (chosenNode)
            {
                chosenNode->selection();
            }
        }
        else
        {
            // we need to expanse, there is not children to select anymore
            expansion();
        }
    }

    tree->game->revertPlay(state.myAction);
}

void Node::expansion()
{
    // list all possible moves, ie remaining empty cells to move to, and add them to our children
    for (game::AbstractBoardCell *cell : tree->game->board->getEmptyCells())
    {
        State childState = {cell};
        Node *node = new Node(tree, this, childState);
        childNodes.push_back(node);
        node->simulation();
        // add a new leaf to the tree
    }

    // choose a random one and simulate
    // unsigned int index = rand() % childNodes.size();
    // childNodes[index]->simulation();
}

void Node::executeMyAction()
{
    // TODO better rework ?

    // do our move
    game::DefinedPlayer player1(tree->game->player1->getId(), state.myAction), player2(tree->game->player2->getId(), state.myAction);

    // make sure our action is executed whoever's turn it is
    tree->game->play(&player1, &player2);
}

void Node::simulation()
{
    // 'convert' the two playes into random players (decisional)
    game::RandomPlayer player1(tree->game->player1->getId()), player2(tree->game->player2->getId());

    // save the actions done so we can revert them;
    std::stack<game::AbstractBoardCell *> playedCells;

    while (!tree->game->isFinished())
    {
        playedCells.push(tree->game->play(&player1, &player2));
    }

    // check the victory
    int won = tree->game->board->checkStatus() == (int)tree->playerMe->getId();

    // draw or lose (-1 for draw)
    if (!won)
    {
        won = tree->game->board->checkStatus() == -1 ? 0 : -1;
    }

    // revert the random game
    while (!playedCells.empty())
    {
        tree->game->revertPlay(playedCells.top());
        // remove the element
        playedCells.pop();
    }

    backpropagation(won);
}

void Node::backpropagation(int increment)
{
    ++totalScenarii;

    // checking the addresses only
    if (
        state.associatedPlayer != nullptr &&
        state.associatedPlayer == tree->playerMe)
    {
        totalVictories += increment;
    }

    // backpropagate
    if (parentNode)
    {
        parentNode->backpropagation(increment);
    }
}

void Node::execute()
{
    selection();
}

const Node *Node::nodeWithMaxVisits() const
{
    Node *chosen = nullptr;
    int max = 0;
    DEBUG(childNodes.size());

    for (Node *node : childNodes)
    {
        DEBUG(node->childNodes.size());
        if (node->totalScenarii >= max)
        {
            max = node->totalScenarii;
            chosen = node;
            const game::Position &pos = ((game::BoardCell *)chosen->getState().myAction)->getPosition();
            DEBUG(max);
            DEBUG(pos.x);
            DEBUG(pos.y);
        }
    }

    return chosen;
}

} // namespace mcts