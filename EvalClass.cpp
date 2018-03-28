#include <iostream>
#include "EvalClass.h"
#define CTRUE S_Exprsn::symbolicAtom("T")
#define  CFALSE S_Exprsn::symbolicAtom("NIL")

S_Exprsn * EvalClass::evCon(S_Exprsn * be, S_Exprsn * Alist, S_Exprsn * Dlist)
{
    if(null(be) == CTRUE){
        throw std::runtime_error(">Error in evcon:: Condition cannot be nil");
        return NULL;//error
    }
    else if(eval(car(car(be)),Alist,&Dlist) != S_Exprsn::symbolicAtom("NIL")){
            int conditionLength = lengthOfList(car(be));
            if(conditionLength != 2)
                throw std::runtime_error(">Error in evcon::Invalid number of arguments in Evcon");
            S_Exprsn * cadarBE = car(cdr(car(be)));
            return eval(cadarBE,Alist,&Dlist);
    } else{
        return evCon(cdr(be),Alist,Dlist);
    }
}

S_Exprsn * EvalClass::evLis(S_Exprsn * list, S_Exprsn * Alist, S_Exprsn * Dlist)
{
    if(null(list) == CTRUE){
        return S_Exprsn::symbolicAtom("NIL");
    }
    else{
        return cons(eval(car(list),Alist,&Dlist),evLis(cdr(list),Alist,Dlist));
    }
}

S_Exprsn * EvalClass::car(S_Exprsn * expression)
{
    if(expression->getType()== NONATOM)
        return expression->getLeft();
    else
        throw std::runtime_error(">Error:: primitive CAR function called on atomic s-expression");
    return NULL;
}

S_Exprsn * EvalClass::eq(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    S_Exprsn * returnExp = NULL;
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        returnExp = (expression1->getVal() == expression2->getVal())?  S_Exprsn::symbolicAtom("T") :  S_Exprsn::symbolicAtom("NIL");
    }
    else if(expression1->getType() == SYMBOLICATOM && expression2->getType() == SYMBOLICATOM){
        bool a = expression1->getName() == expression2->getName();
        S_Exprsn * b = S_Exprsn::symbolicAtom("T");
        S_Exprsn * c = S_Exprsn::symbolicAtom("NIL");
        returnExp = a?  b :c;
        string ee = returnExp->getName();
    }
    else
        throw std::runtime_error(">Error:: primitive EQ function called on non-atomic s-expressions / invalid s-expressions");
    return returnExp;
}

S_Exprsn * EvalClass::cdr(S_Exprsn * expression)
{
    if(expression->getType()== NONATOM)
        return expression->getRight();
    else
        throw std::runtime_error(">Error:: primitive CDR function called on atomic s-expression");
    return NULL;
}

S_Exprsn * EvalClass::cons(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    S_Exprsn * newExpression = new S_Exprsn(NONATOM);
    newExpression->setLeft(expression1);
    newExpression->setRight(expression2);
    return newExpression;
}

S_Exprsn * EvalClass::null(S_Exprsn * expression)
{
    return (expression == S_Exprsn::symbolicAtom("NIL"))? S_Exprsn::symbolicAtom("T"):S_Exprsn::symbolicAtom("NIL");
}

S_Exprsn * EvalClass::isInt(S_Exprsn * expression)
{
    return expression->getType() == INTEGERATOM? S_Exprsn::symbolicAtom("T"):S_Exprsn::symbolicAtom("NIL");
}

S_Exprsn * EvalClass::minus(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        S_Exprsn * newExp = new S_Exprsn(INTEGERATOM);
        newExp->setVal(expression1->getVal()-expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}

S_Exprsn * EvalClass::plus(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        S_Exprsn * newExp = new S_Exprsn(INTEGERATOM);
        newExp->setVal(expression1->getVal()+expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}

S_Exprsn * EvalClass::times(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        S_Exprsn * newExp = new S_Exprsn(INTEGERATOM);
        newExp->setVal(expression1->getVal() * expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function TIMES. Called on non-atomic s-expressions / invalid s-expressions");
}

S_Exprsn * EvalClass::quotient(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        S_Exprsn * newExp = new S_Exprsn(INTEGERATOM);
        if(expression2->getVal()==0)
            std::runtime_error(">Error:: Division by 0 is not defined");
        newExp->setVal(expression1->getVal()/expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function QUOTIENT. Called on non-atomic s-expressions / invalid s-expressions");
}

S_Exprsn * EvalClass::less(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()<expression2->getVal()? S_Exprsn::symbolicAtom("T"):S_Exprsn::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function LESS. Called on non-atomic s-expressions / invalid s-expressions");
}

S_Exprsn * EvalClass::remainder(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        S_Exprsn * newExp = new S_Exprsn(INTEGERATOM);
        if(expression2->getVal()==0)
            std::runtime_error(">Error:: Division by 0 is not defined");
        newExp->setVal(expression1->getVal() % expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function REMAINDER. Called on non-atomic s-expressions / invalid s-expressions");
}

S_Exprsn * EvalClass::greater(S_Exprsn * expression1,S_Exprsn * expression2 )
{
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()>expression2->getVal()? S_Exprsn::symbolicAtom("T"):S_Exprsn::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function GREATER. Called on non-atomic s-expressions / invalid s-expressions");
}

S_Exprsn * EvalClass::atom(S_Exprsn * expression)
{
    return expression->getType()!=NONATOM? CTRUE: CFALSE;
}

bool EvalClass::isInAlist(S_Exprsn * symbolicAtomExp,S_Exprsn * aList)
{
     if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(aList == CFALSE) return false;
    if(symbolicAtomExp == car(car(aList))) return true;
    else return isInAlist(symbolicAtomExp,cdr(aList));
}

bool EvalClass::isTrue(S_Exprsn * exp)
{
    return exp==S_Exprsn::symbolicAtom("T");
}

S_Exprsn*  EvalClass::getValFromAlist(S_Exprsn * symbolicAtomExp,S_Exprsn * aList)
{
    //if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(symbolicAtomExp == car(car(aList))) return cdr(car(aList));
    else return getValFromAlist(symbolicAtomExp,cdr(aList));
}

S_Exprsn* EvalClass::addPairsToAList(S_Exprsn * parameters, S_Exprsn * arguments, S_Exprsn * initialAList)
{
    if(null(parameters) == CTRUE && null(arguments) == CTRUE) return initialAList;
    else if(null(parameters) != CTRUE && null(arguments) != CTRUE) {
        S_Exprsn * newpair = cons(car(parameters),car(arguments));
        return cons(newpair,addPairsToAList(cdr(parameters),cdr(arguments),initialAList));
    }
    else{
        throw std::runtime_error(">Error:: Mismatch in the number of arguments and parameters");
    }

}

S_Exprsn * EvalClass::addFunctionToDlist(S_Exprsn * function, S_Exprsn * initialDlist)
{
    S_Exprsn * paramsAndBody = cons(car(cdr(function)), car(cdr(cdr(function))));
    bool isParamsAList = isList(car(cdr(function)));
    if(isParamsAList == false)
        throw std::runtime_error(">Error:: Improper function definition:"+ car(function)->getName());
    if(cdr(cdr(cdr(function))) != CFALSE)
        throw std::runtime_error(">Error:: Improper function definition:"+ car(function)->getName());
    S_Exprsn * functionExp =  cons(car(function),paramsAndBody);
    S_Exprsn * newDlist = cons(functionExp,initialDlist);
    return newDlist;
}

S_Exprsn * EvalClass::getValFromDlist(S_Exprsn* functionName, S_Exprsn * dlist)
{
    if(isTrue(null(dlist)))
        throw std::runtime_error(">Error:: undeclared function:"+ functionName->getName());
    if(car(car(dlist)) == functionName){
        return cdr(car(dlist));
    } else{
        return getValFromDlist(functionName,cdr(dlist));
    }
}

void EvalClass::assertNumberOfArguments(S_Exprsn* funcName,S_Exprsn* arguments, int numExpectedArguments)
{
    int actualLengthOfArguments = lengthOfList(arguments);
    if( actualLengthOfArguments != numExpectedArguments)
        throw std::runtime_error(">Error:: Expected number of arguments:"+to_string(numExpectedArguments) + " and received:"+to_string(actualLengthOfArguments)+" for the primitive function:"+funcName->getName());
}

int EvalClass::lengthOfList(S_Exprsn * list){
    if(list == CFALSE)
        return 0;
    else return 1+lengthOfList(cdr(list));
}

bool EvalClass::isList(S_Exprsn * exp)
{
    if(exp == CFALSE)
        return true;
    else if(exp->getType() == NONATOM)
        return  isList(exp->getRight());
    else
        return false;
}

S_Exprsn * EvalClass::eval(S_Exprsn * exp, S_Exprsn * Alist, S_Exprsn ** Dlist)
{
    if(exp->getType() != NONATOM){
        if(isInt(exp) == CTRUE) return exp;
        else if(exp == CTRUE) return S_Exprsn::symbolicAtom("T");
        else if (null(exp) == CTRUE) return S_Exprsn::symbolicAtom("NIL");
        else if(isInAlist(exp,Alist)) return getValFromAlist(exp,Alist);
        else{
            throw std::runtime_error(">Error:: Unbound variable:"+exp->getName());
            return NULL;
        }
    }
    else if (car(exp)->getType() != NONATOM){
        if(eq(car(exp),S_Exprsn::symbolicAtom("QUOTE")) == CTRUE){
            assertNumberOfArguments(car(exp),cdr(exp),1);
            return car(cdr(exp));
        }
        else if(eq(car(exp),S_Exprsn::symbolicAtom("COND")) == CTRUE){
            return evCon(cdr(exp),Alist,*Dlist);
        }
        else if(eq(car(exp),S_Exprsn::symbolicAtom("DEFUN")) == CTRUE){
            S_Exprsn * newDlist = addFunctionToDlist(cdr(exp),*Dlist);
            *Dlist = newDlist;
            return S_Exprsn::symbolicAtom(car(cdr(exp))->getName());
        }
        else{
            return apply(car(exp),evLis(cdr(exp),Alist,*Dlist),Alist,*Dlist);
        }
    }
    else{
        throw std::runtime_error(">Error:: Unexpected expression in eval");
        return NULL;
    }
    throw std::runtime_error(">Error:: Unexpected expression in eval");
    return NULL;
}

S_Exprsn * EvalClass::apply(S_Exprsn * function,S_Exprsn * arguments, S_Exprsn * Alist, S_Exprsn * Dlist)
{
    S_Exprsn * returnVal = NULL;
    if(function->getType() != NONATOM) {
        if (eq(function, S_Exprsn::symbolicAtom("CAR")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = car(car(arguments));
        } else if (eq(function, S_Exprsn::symbolicAtom("CDR")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = cdr(car(arguments));
        } else if (eq(function, S_Exprsn::symbolicAtom("CONS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal =  cons(car(arguments),car(cdr(arguments))); 
        } else if (eq(function, S_Exprsn::symbolicAtom("NULL")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = null(car(arguments));
        } else if (eq(function, S_Exprsn::symbolicAtom("EQ")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = eq(car(arguments),car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("ATOM")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = atom(car(arguments));
        } else if (eq(function, S_Exprsn::symbolicAtom("INT")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = isInt(car(arguments));
        } else if (eq(function, S_Exprsn::symbolicAtom("GREATER")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = greater(car(arguments),car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("LESS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = less(car(arguments),car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("PLUS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = plus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("MINUS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = minus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("TIMES")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = times(car(arguments), car(cdr(arguments)));
        } else if (eq(function, S_Exprsn::symbolicAtom("QUOTIENT")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = quotient(car(arguments), car(cdr(arguments)));
        }else if (eq(function, S_Exprsn::symbolicAtom("REMAINDER")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = remainder(car(arguments), car(cdr(arguments)));
        }else{
            returnVal = eval(cdr(getValFromDlist(function,Dlist)),addPairsToAList(car(getValFromDlist(function,Dlist)),arguments,Alist),&Dlist);
        }
    }
    else{
        throw std::runtime_error(">Error:: Invalid: Non atom in car of apply");
        return NULL;
    }
    if(returnVal == NULL){
        throw std::runtime_error(">Error:: Enexpected error");
    }
    return returnVal;
}


