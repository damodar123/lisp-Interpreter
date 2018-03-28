#include "S_Exprsn.h"
class EvalClass {
    S_Exprsn * car(S_Exprsn * expression);
    S_Exprsn * cdr(S_Exprsn * expression);
    S_Exprsn * cons(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * eq(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * null(S_Exprsn * expression);
    S_Exprsn * isInt(S_Exprsn * expression);
    S_Exprsn * atom(S_Exprsn * expression);
    S_Exprsn * plus(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * minus(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * times(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * quotient(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * remainder(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * less(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn * greater(S_Exprsn * exp1,S_Exprsn * exp2 );
    S_Exprsn*  getValFromAlist(S_Exprsn * symbolicAtom,S_Exprsn * aList);
    S_Exprsn* addPairsToAList(S_Exprsn * parameters, S_Exprsn * arguments, S_Exprsn * initialAList);
    S_Exprsn * addFunctionToDlist(S_Exprsn * function, S_Exprsn * initialDlist);
    S_Exprsn * getValFromDlist(S_Exprsn* functionName, S_Exprsn * dlist);
    S_Exprsn * apply(S_Exprsn * function,S_Exprsn * arguments, S_Exprsn * Alist, S_Exprsn * Dlist);
    S_Exprsn * evLis(S_Exprsn * be, S_Exprsn * Alist, S_Exprsn * Dlist);
    S_Exprsn * evCon(S_Exprsn * be, S_Exprsn * Alist, S_Exprsn * Dlist);
    void assertNumberOfArguments(S_Exprsn* funcName,S_Exprsn* arguments, int numExpectedArguments);
    bool isInAlist(S_Exprsn * symbolicAtom,S_Exprsn * aList);
    bool isList(S_Exprsn * exp);
    int lengthOfList(S_Exprsn * list);
    bool isTrue(S_Exprsn * exp);
public:
    S_Exprsn * eval(S_Exprsn * exp, S_Exprsn * Alist, S_Exprsn ** Dlist);
};
