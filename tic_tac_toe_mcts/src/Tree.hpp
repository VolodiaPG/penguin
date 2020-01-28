#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include <math.h>
#include <queue>
#include "AbstractPlayer.hpp"
#include "AbstractGame.hpp"
#include "log.hpp"

#define NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO 100
#define INCREMENT_VICTORY 1.0
#define INCREMENT_DRAW 0.5
#define INCREMENT_DEFEAT -1.0

namespace game
{
class MCTSPlayer;
}

namespace mcts
{

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

struct Node
{
    ~Node()
    {
        for (Node *child : childNodes)
            delete child;
    }

    std::vector<Node *> childNodes;
    Node *parent = nullptr;
    game::AbstractPlayer *player;
    game::AbstractBoardCell *targetedCell = nullptr;

    double score = 0.0;
    int visits = 0;
};

class Tree
{
protected:
    friend class TreeVisualizer;
    Node rootNode;
    // Node *rootNode;
    void expandNode();

    Node *selectBestChildAndDoAction(Node *node);

    Node *randomChooseChildOrFallbackOnNode(Node *node) const;

    int randomSimulation() const;

    void expandNode(Node *nodeToExpand);

    Node *nodeWithMaxVisits(const Node *nodeFrom) const;

    void backPropagateAndRevertAction(int winnerId, Node *terminalNode);

    game::AbstractBoardCell *getRandomAvailableCellFromBoard() const;

    double formula(
        const Node &node,
        const Node &nodeSuccessor) const;

    void doActionOnBoard(const Node &nodeToGetTheActionFrom);

    

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
    Node * bestNode();
    /**
     * @brief Makes this node the rootnode of the tree (keeps all of his children and deletes every thing else)
     * 
     * @param node 
     */
    void moveRootToNode(Node * node);
    // NodegetRootNode() const { return rootNode; };
};

} // namespace mcts
#endif /*TREE_HPP_*/