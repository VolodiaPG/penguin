#include "Node.hpp"

namespace mcts
{
Node::Node(Tree *tree, Node *parent, const State &state)
    : parentNode(parent), tree(tree), state(state)
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
    return (double)winsSuccessor / (double)numberVisitsFather + sqrt(2) * sqrt(log2((double)numberVisitsFather) / (double)numberVisitsSuccessor);
}

void Node::selection()
{
    Node *chosenNode = nullptr;

    // case of children
    if (childNodes.size())
    {
        double max = 0.0;

        // select the node that has the most value using the selection formula
        for (Node *node : childNodes)
        {
            double res = formula(node->totalVictories, node->totalScenarii, this->totalScenarii);
            if (res > max)
            {
                max = res;
                chosenNode = node;
            }
        }

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

void Node::expansion()
{
    // list all possible moves, ie remaining empty cells to move to, and add them to our children
    for (game::AbstractBoardCell *cell : tree->game->board->getEmptyCells())
    {
        State childState = {.myAction = cell};
        Node *node = new Node(tree, this, childState);
        childNodes.push_back(node);
        // add a new leaf to the tree
        node->simulation();
    }
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
    executeMyAction();

    // 'convert' the two playes into random players (decisional)
    game::RandomPlayer player1(tree->game->player1->getId()), player2(tree->game->player2->getId());

    // save the actions done so we can revert them;
    std::stack<game::AbstractBoardCell *> playedCells;

    while (!tree->game->isFinished())
    {
        playedCells.push(tree->game->play(&player1, &player2));
    }
    // check the victory
    bool won = (unsigned int)tree->game->board->checkStatus() == tree->playerMe->getId();

    // revert the random game
    while (!playedCells.empty())
    {
        tree->game->revertPlay(playedCells.top());
        // remove the element
        playedCells.pop();
    }
    backpropagation(won);
}

void Node::backpropagation(bool victoryOnRandomPlay)
{
    // undo the actions
    tree->game->revertPlay(state.myAction);

    ++totalScenarii;
    if (victoryOnRandomPlay)
    {
        ++totalVictories;
    }

    // backpropagate
    if (parentNode)
    {
        parentNode->backpropagation(victoryOnRandomPlay);
    }
}

void Node::execute()
{
    selection();
}

const Node *Node::nodeWithMaxVictories() const
{
    Node *chosen;
    int max = 0;

    for (Node *node : childNodes)
    {
        if (node->totalVictories >= max)
        {
            max = node->totalVictories;
            chosen = node;
        }
    }

    return chosen;
}

} // namespace mcts