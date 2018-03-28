#include "S_Exprsn.h"
map<string,S_Exprsn*> S_Exprsn::identifiers;

void S_Exprsn::InitializeDefaultSymbolizAtoms(){
    S_Exprsn * nilExp = new S_Exprsn(SYMBOLICATOM);
    nilExp->setName("NIL");
    identifiers["NIL"] = nilExp;
    S_Exprsn * trueExp = new S_Exprsn(SYMBOLICATOM);
    trueExp->setName("T");
    identifiers["T"] = trueExp;
}
void S_Exprsn::DeleteSymbolicAtoms(){
    for(auto it = identifiers.begin();it != identifiers.end(); it++){
        S_Exprsn * symAtom = it->second;
        it->second = NULL;
        delete(symAtom);

    }

}
S_Exprsn* S_Exprsn::symbolicAtom(string str){
    if(identifiers.find(str) == identifiers.end() || identifiers[str] == NULL){
        S_Exprsn * ne = new S_Exprsn(SYMBOLICATOM);
        ne->setName(str);
        identifiers[str] = ne;
        return ne;
    }
    else
        return identifiers[str];

}
S_Exprsn::~S_Exprsn(){
    if(getType() == NONATOM){
        delete getLeft();
        delete getRight();
    }

}
S_Exprsn::S_Exprsn(SExpType aType):type(aType){

}
