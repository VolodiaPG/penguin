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
        childNodes.clear();
    }

    std::vector<Node *> childNodes;
    Node *parent = nullptr;
    game::AbstractPlayer *player;
    game::AbstractBoardCell *targetedCell = nullptr;

    double score = 0.0;
    int visits = 0;
    bool isRoot = false;
};

class Tree
{
protected:
    friend class TreeVisualizer;
    Node rootNode;
    

    Node *nodeWithMaxVisits(const Node *nodeFrom) const;

public:
    game::AbstractPlayer *playerMe;
    game::AbstractGame *game;
    MCTSConstraints constraints;

    explicit Tree(game::AbstractPlayer *me);
    explicit Tree(
        game::AbstractGame *game,
        game::AbstractPlayer *me,
        const MCTSConstraints &constraints);

    ~Tree();

    void begin();

    game::AbstractBoardCell *bestMove() const;

    /**
     * @brief Moves the root to a given cell
     * 
     * @param cell 
     */
    void moveRootToCell(game::AbstractBoardCell* cell);

    /**
     * @brief Get the Root Node object
     * 
     * @return Node* 
     */
    Node* getRootNode();

    /**
     * @brief Merges tree into the current tree
     * @brief Does it only for 2 layers
     * 
     * @param tree 
     */
    void merge(Tree* tree);
};

} // namespace mcts
#endif /*TREE_HPP_*/