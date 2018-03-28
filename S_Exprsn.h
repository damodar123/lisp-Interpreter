#include <string>
#include <map>
using namespace std;

enum SExpType{
    INTEGERATOM = 0,
    SYMBOLICATOM,
    NONATOM
};

class S_Exprsn {
public:
	static S_Exprsn* symbolicAtom(string s);
	static void InitializeDefaultSymbolizAtoms();
	static void DeleteSymbolicAtoms();
	S_Exprsn(SExpType);
	~S_Exprsn();

private:
    static map<string,S_Exprsn*> identifiers;
    SExpType type;
    int val;
    std::string name;
    S_Exprsn * left;
    S_Exprsn * right;

public:
    SExpType getType() const
	{
    	return type;
	}

    void setType(SExpType t)
	{
    	type = t;
	}


    int getVal() const
	{
    	return val;
	}

    void setVal(int v)
	{
    	val = v;
	}

    const string &getName() const
	{
    	return name;
	}

    void setName(const string &n)
	{
		name = n;
	}

    S_Exprsn *getLeft() const
	{
    	return left;
	}

    void setLeft(S_Exprsn *l)
	{
    	left = l;
	}

    S_Exprsn *getRight() const
	{
    	return right;
	}

	void setRight(S_Exprsn *r)
	{
    	right = r;
	}
};
