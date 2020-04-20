#ifndef UTILS_I_EQUALS_HPP_
#define UTILS_I_EQUALS_HPP_

template <class BaseT>
class IEquals_Base
{
protected:
    virtual bool equals_to(const BaseT &base) const = 0;

public:
    bool operator==(const BaseT &base) const;
    bool operator!=(const BaseT &base) const;
};

template <class DerivedT, class BaseT>
class IEquals_Derived
{
protected:
    virtual bool equals_to(const DerivedT &derived) const = 0;

    bool equals_to(const BaseT& base) const;
};

#endif