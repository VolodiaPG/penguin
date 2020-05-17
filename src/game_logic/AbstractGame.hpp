#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include <vector>

#include "utils/Move.hpp"

namespace game
{
template <class, class, class>
class AbstractBoard;

template <class CellT, class PlayerT, class PawnT>
class AbstractGame
{
public:
  AbstractBoard<CellT, PlayerT, PawnT> *board;

  explicit AbstractGame(AbstractBoard<CellT, PlayerT, PawnT> *board);

  explicit AbstractGame(const AbstractGame<CellT, PlayerT, PawnT> &) = default;

  virtual ~AbstractGame(){};

  /** 
     * @brief Tells if the game is finished yet
     * 
     * @return true 
     * @return false 
     */
  virtual bool isFinished() const = 0;

  // /**
  //  * @brief play one round of the game
  //  *
  //  * @return the played cell
  //  */
  // virtual AbstractBoardCell *play(AbstractPlayer *p1, AbstractPlayer *p2) = 0;

  virtual bool play(PawnT *pawn, CellT *cell) = 0;

  virtual const Move<CellT, PawnT> revertPlay() = 0;

  /**
     * @brief Get the player who hadn't play yet
     * 
     * @return const int the player id 
     */
  virtual unsigned int getPlayerToPlay() = 0;

  /**
     * @brief Checks the status of the game, if won, draw
     * 
     * @return int when won : the id of the winner, -1 if draw, 0 otherwise
     */
  virtual int checkStatus() const = 0;

  /**
   * @brief Get the available moves to a player
   * 
   * @param player the player (the human one)
   * @return Move containing all the necessary informations
   */
  virtual std::vector<Move<CellT, PawnT>> getAvailableMoves(PlayerT *player) = 0;

  /**
     * @brief Clone function for clonning games
     * 
     * @return AbstractGame* 
     */
  virtual AbstractGame<CellT, PlayerT, PawnT> *clone() const = 0;
};
} // namespace game

#endif