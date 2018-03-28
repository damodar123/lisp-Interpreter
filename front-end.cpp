#include <iostream>
#include <string.h>
#include<bits/stdc++.h>
#include <vector>
#include "EvalClass.h"
#include <fstream>

using namespace std;

//#define VERBOSE
const int max_char_symbol = 10;
const int max_digit_int = 10;

enum class status
{
	success = 0,
	exp_end,
	input_end,
	misplaced_braces,
	unequal_braces,
	invalid_charecter,
	incompliant_names,
	expected_paranthesis,
	extra_dot
};

status createtokens(string inp);
status read_expression();
status error = status::success;

int token_index=0;

enum class tokentype
{
	openbrace = 0,
	closebrace,
	dot,
	integer,
	identifier,
	space,
	endexp,		//$
	endinput	//$$
};

string input_expression = "";
vector< pair <string, tokentype> > tokens;

void clear_global_state()
{
	input_expression = "";
	tokens.clear();
	error = status::success;
	token_index=0;
}

class Analyser {
public:
    Analyser();
    ~Analyser();
    S_Exprsn * createtree();
    S_Exprsn * createtree2();
	string toStringfromExpression(S_Exprsn * exp);
};

Analyser::Analyser()
{
    cout<<"<Program Started>"<<endl;
    S_Exprsn::InitializeDefaultSymbolizAtoms();
    EvalClass evaluator;
    S_Exprsn * Alist = S_Exprsn::symbolicAtom("NIL");
    S_Exprsn * pDList = S_Exprsn::symbolicAtom("NIL");
    S_Exprsn ** Dlist = &pDList;
	status ret = status::success;

	while (true)
	{
		S_Exprsn *  expTree = NULL;
		string expString;
		clear_global_state();
		ret = read_expression();
//		for(int i = 0; i < tokens.size(); i++)
//		{
//			cout << tokens[token_index].first << endl;
//		}
        if(ret == status::exp_end || ret == status::input_end)
		{
			expTree = createtree();
            expString = toStringfromExpression(expTree);
            cout << "Dot notation>" << expString << endl;
            expTree = evaluator.eval(expTree,Alist,Dlist);
            expString = toStringfromExpression(expTree);
            cout << ">" << expString << endl;
            if(ret == status::input_end)
                break;
        }
        else
		{
            throw std::runtime_error(">Error:: Invalid input");
			break;
		}
	}

    cout<<"<End of program>"<<endl;
}

Analyser::~Analyser() {
    S_Exprsn::DeleteSymbolicAtoms();
}

S_Exprsn* Analyser::createtree()
{
	if(tokens.size() == 0)
		return NULL;

	if(tokens[token_index].second==tokentype::openbrace)
	{
		token_index++;
		if(tokens[token_index].second==tokentype::closebrace)
		{
			return createtree2();
		}
        S_Exprsn * leftExpression = createtree();
        S_Exprsn * rightExpression;
		if(tokens[token_index].second==tokentype::dot)
		{
			token_index++;
            rightExpression = createtree();
			if(tokens[token_index].second!=tokentype::closebrace)
			{
                throw std::runtime_error(">Error::Expected ')' ,found "+tokens[token_index].first );
                return NULL;
            }
			token_index++;
        }
        else
		{
            rightExpression = createtree2();
        }
        S_Exprsn * newExpression = new S_Exprsn(NONATOM);
        newExpression->setLeft(leftExpression);
        newExpression->setRight(rightExpression);
        return  newExpression;
    }
	else if(tokens[token_index].second == tokentype::identifier)
	{
		token_index++;
        return S_Exprsn::symbolicAtom(tokens[token_index-1].first);
    }
	else if(tokens[token_index].second==tokentype::integer)
	{
        S_Exprsn * newIntegerExpression = new S_Exprsn(INTEGERATOM);
        newIntegerExpression->setVal(stoi(tokens[token_index].first));
		token_index++;
        return  newIntegerExpression;
    }
    else
	{
        throw std::runtime_error(">Error:: Invalid token in s-expression:"+tokens[token_index].first);
		return NULL;
    }
}

S_Exprsn* Analyser::createtree2()
{
	if(tokens[token_index].second==tokentype::closebrace)
	{
		token_index++;
        return S_Exprsn::symbolicAtom("NIL");
    }
	else if(tokens[token_index].second==tokentype::space)
	{
		token_index++;
        S_Exprsn * newExpression = new S_Exprsn(NONATOM);
        newExpression->setLeft(createtree());
        newExpression->setRight(createtree2());
        return newExpression;
    }
    else
	{
        throw std::runtime_error(">Error:: Invalid token in s-expression:"+tokens[token_index].first);
        return NULL;
    }
}

string Analyser::toStringfromExpression(S_Exprsn * exp)
{
    string expString;
    switch(exp->getType()){
        case NONATOM:
            expString+= '(';
            expString += toStringfromExpression(exp->getLeft());
            expString += '.';
            expString += toStringfromExpression(exp->getRight());
            expString += ')';
            break;
        case INTEGERATOM:
            expString += to_string(exp->getVal());
            break;
        case SYMBOLICATOM:
            expString += exp->getName();
            break;
        default:
            break;

    }
    return expString;
}

//create array with populated tokens. Check all the conditions for validness.
status createtokens(string inp)
{
	int i=0, countOpen=0;
	string token;
	while(i<=inp.length())
	{
		int token_length=i;

		//Starts with an Alphabet
		if((inp[i]>64 && inp[i]<91) || (inp[i]>96 && inp[i]<123))
		{
			token=inp[i];
			i++;
			while((inp[i]>64 && inp[i]<91) || (inp[i]>96 && inp[i]<123) || (inp[i]>47 && inp[i]<58))
			{
				token=token+inp[i];
#ifdef VERBOSE
			cout << "appended: " << inp[i] << "to " << token << endl;
#endif
				i++;
			}
			if((i - token_length) <= max_char_symbol)
			{
				tokens.push_back(make_pair(token, tokentype::identifier));
#ifdef VERBOSE
				cout << "added token: " << token << "of length" << (i - token_length) << endl;
#endif
			}
			else
			{
#ifdef VERBOSE
				cout << "Createtokens return incompliant_names " << "." << endl;
#endif
				return status::incompliant_names;
			}
		}
		else if((inp[i]>47 && inp[i]<58) || inp[i]==45 || inp[i]==43 )
		{
			token=inp[i];
			i++;
			while(inp[i]>47 && inp[i<58])
			{
				token=token+inp[i];
#ifdef VERBOSE
				cout << "appended: " << inp[i] << "to" << token << endl;
#endif
				i++;
			}
			if((token == "-") || (token == "+"))
			{
#ifdef VERBOSE
				cout << "Createtokens return incompliant_names " << "." << endl;
#endif
				return status::incompliant_names; //just '-' found, not an tokentype::integer followed by.
			}
			else if((i - token_length) <= max_digit_int) //TODO: check if - is found then 7 chars is allowed
			{
				tokens.push_back(make_pair(token, tokentype::integer));
#ifdef VERBOSE
				cout << "added token: " << token << "of length" << (i - token_length) << endl;
#endif
			}
			else
			{
#ifdef VERBOSE
				cout << "Createtokens return incompliant_names " << "." << endl;
#endif
				return status::incompliant_names;
			}
		}
		else if(inp[i]==40)
		{
			if((i !=0) and (inp[i-1]==41))
			{
				return status::misplaced_braces;
			}
			i++;
			tokens.push_back(make_pair("(", tokentype::openbrace));
			countOpen++;
#ifdef VERBOSE
			cout << "added token: " << "(" << endl;
#endif
		}
		else if(inp[i]==41)
		{
			i++;
			if(tokens.size()!=0)
			{
				if(tokens.back().second == tokentype::space)
				{
					tokens.pop_back();
#ifdef VERBOSE
					cout << "removed: " << " " << endl;
#endif
				}
			}
			tokens.push_back(make_pair(")", tokentype::closebrace));
			countOpen--;
#ifdef VERBOSE
			cout << "added token: " << ")" << endl;
#endif
		}
		else if(inp[i]==46)
		{
			if(countOpen <= 0)
			{
				return status::expected_paranthesis;
			}
			if ((tokens.back().second == tokentype::dot) || (tokens.back().second == tokentype::openbrace) || inp[i+1]==41)
			{
				return status::extra_dot;
			}
			tokens.push_back(make_pair(".", tokentype::dot));
#ifdef VERBOSE
			cout << "added token: " << "." << endl;
#endif
			i++;
		}
		else if(inp[i]==32 || inp[i]==9 )
		{
			if(token.size() > 0)
			{
				if ((tokens.back().second == tokentype::dot) ||
					(tokens.back().second == tokentype::openbrace) ||
					(tokens.back().second == tokentype::space) ||
					inp[i+1]==46)
				{
					i++;
					continue;
				}
				tokens.push_back(make_pair(" ", tokentype::space ));
#ifdef VERBOSE
			cout << "added token: " << " " << endl;
#endif
			}
			i++;
		}
		else if(inp[i]==0)
		{
#ifdef VERBOSE
			cout << "Createtokens return Success: " << "." << endl;
#endif
			return status::success;
		}
		else if(inp[i]=='\t')
		{
			i++;
		}
		else
		{
#ifdef VERBOSE
			cout << "Createtokens return invalid_charecter " << "." << endl;
#endif
			return status::invalid_charecter;
		}
	}
	return status::success;
}

status checkparenthesis(string inp)
{
	int i=0, countOpen=0;
	while(i<inp.length())
	{
		if(inp[i]==40)
		{
			countOpen++;
			i++;
		}
		else if(inp[i]==41)
		{
			countOpen--;
			if(countOpen<0)
			{
				return status::misplaced_braces;
			}
			i++;
		}
		else
		{
			i++;
		}
	}

	if(countOpen == 0)
		return status::success;
	else
		return status::unequal_braces;
}

void printerrormsg(status flag)
{
	switch(flag)
	{
		case status::misplaced_braces:
			cout<<"ERROR: invalid input_expression-expression: incorrectly placed opening and closing paranthesis" << endl;
			break;
		case status::unequal_braces:
			cout<<"ERROR: invalid input_expression-expression: unequal opening and closing paranthesis" << endl;
			break;
		case status::invalid_charecter:
			cout<<"ERROR: invalid input_expression-expression: Invalid charecter found in the input" << endl;
			break;
		case status::incompliant_names:
			cout<<"ERROR: invalid input_expression-expression: name of an atom or a value is incompliant" << endl;
			break;
		case status::extra_dot:
			cout<<"ERROR: invalid input_expression-expression: Unexpected dot found" << endl;
			break;
		case status::expected_paranthesis:
			cout<<"ERROR: invalid input_expression-expression: Missing Paranthesis" << endl;
			break;
		default:
			cout << "God save me!" << endl;
	}
}



void checkandcreatetokens()
{
	status ret = status::success;
	ret = checkparenthesis(input_expression);	//s is a global variable
	if(ret != status::success)
	{
		printerrormsg(ret);
		clear_global_state();
		return;
	}
	ret = createtokens(input_expression);
	if(ret != status::success)
	{
		printerrormsg(ret);
	}
	return;
}

void addinput(string inp)
{
	if(inp.substr( inp.length()-1 ) != "." && inp.substr( inp.length()-1 ) != "$" && inp.substr( inp.length()-1 ) != ")" && inp.substr( inp.length()-1 ) != "(")
	{
		inp.append(" ");
	}
	input_expression = input_expression + inp;
}

status parseinput(string line)
{
	unsigned int len;
	len = line.length();
	if(len == 0)
	{
		return status::success;
	}

	addinput(line);

	if(len == 1)
	{
		if(line == "$")
		{
			input_expression.pop_back();
			checkandcreatetokens();
			return status::exp_end;
		}
	}
	else if(len == 2)
	{
		if(line == "$$")
		{
			input_expression.pop_back();
			input_expression.pop_back();
			checkandcreatetokens();
			return status::input_end;
		}
		else if(line.substr( len-1 ) == "$")
		{
			input_expression.pop_back();
			checkandcreatetokens();
			return status::exp_end;
		}
	}
	else
	{
		if(line.substr( len-2 ) == "$$")
		{
			input_expression.pop_back();
			input_expression.pop_back();
			checkandcreatetokens();
			return status::input_end;
		}
		else if(line.substr( len-1 ) == "$")
		{
			input_expression.pop_back();
			checkandcreatetokens();
			return status::exp_end;
		}
	}
	return status::success;
}

//std::ifstream infile("test_case_others");

/* Reads input */
status read_expression()
{
	string line;
	status ret;
	do
	{
		//getline(infile,line);
		getline(cin,line);
		ret = parseinput(line);
	}
	while((ret != status::input_end)&&(ret != status::exp_end)) ;
	return ret;
}

int main()
{
    Analyser Analyser;
    return 0;
}
