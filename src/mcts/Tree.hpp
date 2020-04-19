#ifndef TREE_HPP_
#define TREE_HPP_

#include <chrono>
#include <math.h>
#include <queue>
#include "../game_logic/AbstractPlayer.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/utils/Move.hpp"

#define NUMBER_ITERATIONS_BEFORE_CHECKING_CHRONO 100
#define INCREMENT_VICTORY 1.0
#define INCREMENT_DRAW 0.5
#define INCREMENT_DEFEAT -1.0

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

template <class CellT, class PawnT>
struct Node
{
    ~Node()
    {
        for (Node *child : childNodes)
            delete child;
    }

    std::vector<Node *> childNodes;
    Node *parent = nullptr;
    game::Move<CellT, PawnT> move;

    double score = 0.0;
    int visits = 0;
    bool isRoot = false;
};

template <class CellT, class PlayerT, class PawnT>
class Tree
{
protected:
    Node<CellT, PawnT> rootNode;
    // Node *rootNode;
    void expandNode();

    // Node<CellT, PawnT> *selectBestChildAndDoAction(Node<CellT, PawnT> *node);

    // Node<CellT, PawnT> *randomChooseChildOrFallbackOnNode(Node<CellT, PawnT> *node) const;

    // int randomSimulation() const;

    // void expandNode(Node<CellT, PawnT> *nodeToExpand);

    Node<CellT, PawnT> *nodeWithMaxVisits(const Node<CellT, PawnT> *nodeFrom) const;

    // void backPropagateAndRevertAction(int winnerId, Node<CellT, PawnT> *terminalNode);

    // const game::Move<CellT, PawnT> getRandomAvailableMoveFromBoard(const unsigned int& player_id) const;

    // double formula(
    //     const Node<CellT, PawnT> &node,
    //     const Node<CellT, PawnT> &nodeSuccessor) const;

    // void doActionOnBoard(const Node<CellT, PawnT> &nodeToGetTheActionFrom);

public:
    game::AbstractGame<CellT, PlayerT, PawnT> *game;
    MCTSConstraints constraints;

    explicit Tree(
        game::AbstractGame<CellT, PlayerT, PawnT> *game,
        const MCTSConstraints &constraints);
    ~Tree();

    // size_t begin();

    game::Move<CellT, PawnT> bestMove() const;

    /**
     * @brief Moves the root to a given cell
     * 
     * @param cell 
     */
    void moveRootToMove(const game::Move<CellT, PawnT>& move);

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