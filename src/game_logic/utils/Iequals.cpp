#include "../AbstractPlayer.hpp"
#include "../AbstractPawn.hpp"
#include "../tic_tac_toe/Player.hpp"
#include "../tic_tac_toe/BoardCell.hpp"
#include "../penguin/HumanPlayer.hpp"
#include "../penguin/BoardCell.hpp"

#include "Iequals.hpp"

template <class BaseT>
bool IEquals_Base<BaseT>::operator==(const BaseT &base) const
{
    return equals_to(base);
}

template <class BaseT>
bool IEquals_Base<BaseT>::operator!=(const BaseT &base) const
{
    return !equals_to(base);
}

template <class DerivedT, class BaseT>
bool IEquals_Derived<DerivedT, BaseT>::equals_to(const BaseT &base) const
{
    DerivedT *casted;
    if ((casted = dynamic_cast<DerivedT *>(&base)) != nullptr)
    {
        return equals_to(*casted);
    }
    return false;
}

template class IEquals_Base<game::AbstractPlayer>;
template class IEquals_Base<game::AbstractBoardCell>;
template class IEquals_Base<game::AbstractPawn<game::tic_tac_toe::Player, game::tic_tac_toe::BoardCell>>;
template class IEquals_Base<game::AbstractPawn<game::penguin::HumanPlayer, game::penguin::BoardCell>>;