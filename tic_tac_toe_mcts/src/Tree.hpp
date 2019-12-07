#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include "Node.hpp"
#include "AbstractPlayer.hpp"
#include "AbstractGame.hpp"
#include "log.hpp"

#define NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO 100
#define INCREMENT_VICTORY 1
#define INCREMENT_DRAW 1
#define INCREMENT_DEFEAT -1

namespace game
{
class MCTSPlayer;
}

namespace mcts
{

class Node;

struct timer
{
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::milliseconds milliseconds;

    void reset() { start = clock::now(); }

    unsigned long long milliseconds_elapsed() const
    {
        return std::chrono::duration_cast<milliseconds>(clock::now() - start).count();
    }

private:
    clock::time_point start = clock::now();
};

typedef struct
{
    /**
     * @brief Time constraint in ms
     * 
     */
    int time;
} MCTSConstraints;

class Tree
{
protected:
    struct Node_bis
    {
        ~Node_bis()
        {
            for (Node_bis *child : childNodes)
                delete child;
        }

        std::vector<Node_bis *> childNodes;
        Node_bis *parent = nullptr;
        game::AbstractPlayer *player;
        game::AbstractBoardCell *targetedCell = nullptr;

        int score = 0;
        int visits = 0;
    } rootNode;
    // Node *rootNode;
    void expandNode();

    Node_bis *selectBestChildAndDoAction(Node_bis *node);

    Node_bis *randomChooseChildOrFallbackOnNode(Node_bis *node) const;

    int randomSimulation(Node_bis *nodeFrom) const;

    void expandNode(Node_bis *nodeToExpand);

    Node_bis* nodeWithMaxVisits(const Node_bis* nodeFrom) const;

    void backPropagateAndRevertAction(Node_bis &terminalNode);

    game::AbstractBoardCell *getRandomAvailableCellFromBoard() const;

    double formula(
        const Node_bis &node,
        const Node_bis &nodeSuccessor) const;

    void doActionOnBoard(const Node_bis &nodeToGetTheActionFrom);

public:
    game::AbstractPlayer *playerMe;
    game::AbstractGame *game;
    MCTSConstraints constraints;

    explicit Tree(
        game::AbstractGame *game,
        game::AbstractPlayer *me,
        const MCTSConstraints &constraints);
    ~Tree();

    void begin();

    game::AbstractBoardCell *bestMove() const;
    // NodegetRootNode() const { return rootNode; };
};

} // namespace mcts
#endif /*TREE_HPP_*/