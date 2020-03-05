#include "uctfunction.hpp"

double uctValue(int nodeVisitCount, int childWinCount, int childVisitCount)
{
    if(childVisitCount == 0)
    {
        return 1000000;
    }
    double result = (double)childWinCount/(double)childVisitCount + sqrt(2.0)*sqrt(log((double)nodeVisitCount)/(double)childVisitCount);
    return result;
}
