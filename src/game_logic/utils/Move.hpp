#ifndef MOVE_HPP_
#define MOVE_HPP_

namespace game
{

template <class CellT, class PawnT>
struct Move
{
    CellT *from = nullptr;
    CellT *target = nullptr;
    PawnT *pawn = nullptr;

    bool operator==(const Move &move) const { return equals_to(move); };
    bool operator!=(const Move &move) const { return !equals_to(move); };

private:
    bool equals_to(const Move &move) const;

// For emscripten bindings
#ifdef __EMSCRIPTEN__
public:
    static Move generateMove(CellT *const &from, CellT *const target, PawnT *const &pawn) { return {from, target, pawn}; };
    CellT *getFrom() const { return from; };
    void setFrom(CellT *from) { this->from = from; };
    CellT *getTarget() const { return target; };
    void setTarget(CellT *target) { this->target = target; };
    PawnT *getPawn() const { return pawn; };
    void setPawn(PawnT *pawn) { this->pawn = pawn; };
#endif
};

} // namespace game

#endif