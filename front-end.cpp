#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

//#define VERBOSE
const int max_char_symbol = 10;
const int max_digit_int = 10;

enum class status
{
	success = 0,
	done,
	misplaced_braces,
	unequal_braces,
	invalid_charecter,
	incompliant_names,
	expected_paranthesis,
	extra_dot
};

status createtokens(string inp);
status error = status::success;

int token_index=0;

struct Node{
	string data;
	Node *right;
	Node *left;
};

Node* createtree();
Node* createtree2();

Node* GetNewNode(string d)
{
	Node* newNode = new Node;
	newNode->data = d;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

string input_expression = "";
vector <string> tokens;

void printoutput(Node* root)
{
	if(root!=NULL)
	{
		if(root->left==NULL && root->right==NULL)
		{
			cout << root->data;
		}
		else
		{
			cout<<"(";
			printoutput(root->left);
			cout<<" . ";
			printoutput(root->right);
			cout<<")";
		}
	}
}

Node* createtree2()
{
	Node *root = NULL;
	if(tokens[token_index]==")")
	{
		token_index++;
		return GetNewNode("NIL");
	}
	else if(tokens[token_index]==" ")
	{
		token_index++;
		root = GetNewNode(" ");
		root->left = createtree();
		root->right = createtree2();
		return root;
	}
}

Node* createtree()
{
	Node *root = NULL;
	
	if(tokens[token_index]=="(")
	{
		token_index++;
		if(tokens[token_index]==")")
		{
			token_index++;
			return GetNewNode("NIL");
		}
		Node *left = createtree();
		Node *right = NULL; 
		if(tokens[token_index]==".")
		{
			token_index++;
			right = createtree();
			if(tokens[token_index]!=")")
			{
				error = status::expected_paranthesis;
				return NULL;
			}
			token_index++;
		}
		else
		{
			right = createtree2();
		}

		root = GetNewNode(" ");
		root->left = left;
		root->right = right;
		return root;
	}
	else if((tokens[token_index][0]==45)
			|| (tokens[token_index][0]>47 && tokens[token_index][0]<58) 
			|| (tokens[token_index][0]>64 && tokens[token_index][0]<91)
			|| (tokens[token_index][0]>96 && tokens[token_index][0]<123)
			)
	{
		root = GetNewNode(tokens[token_index]);
		token_index++;
		return root;
	}	
	return root;
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
				tokens.push_back(token);
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
		else if((inp[i]>47 && inp[i]<58) || inp[i]==45)
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
			if(token == "-")
			{
#ifdef VERBOSE
				cout << "Createtokens return incompliant_names " << "." << endl;
#endif
				return status::incompliant_names; //just '-' found, not an integer followed by.
			}
			else if((i - token_length) <= max_digit_int) //TODO: check if - is found then 7 chars is allowed
			{
				tokens.push_back(token);
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
			if(inp[i-1]==41)
			{
				return status::misplaced_braces;
			}
			i++;
			tokens.push_back("(");
			countOpen++;
#ifdef VERBOSE
			cout << "added token: " << "(" << endl;
#endif
		}
		else if(inp[i]==41)
		{
			i++;
			tokens.push_back(")");
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
			if ((tokens.back() == ".") || (tokens.back() == "(") || inp[i+1]==41)
			{
				return status::extra_dot;
			}
			tokens.push_back(".");
			i++;
		}
		else if(inp[i]==32)
		{
			if(token.size() > 0)
			{
				if ((tokens.back() == ".") || (tokens.back() == "(") || (tokens.back() == " ") || inp[i+1]==46)
				{
					i++;
					continue;
				}
				tokens.push_back(" ");
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

void clear_global_state()
{
	input_expression = "";
	tokens.clear();
}

void executeexpression()
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
		clear_global_state();
		return;
	}
	else
	{
		token_index = 0;	//set global vairable used by createtreeList()
		error = status::success;
		Node *toproot;
		toproot = createtree();
		if(error != status::success)
		{
			printerrormsg(error);
			clear_global_state();
			return;
		}
		else
		{
			printoutput(toproot);
			cout << endl;
			toproot = NULL;
		}
	}
	clear_global_state();
	return;
}

void addinput(string inp)
{
	if(inp.substr( inp.length()-1 ) != "." && inp.substr( inp.length()-1 ) != "$")
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
			executeexpression();
			return status::success;
		}
	}
	else if(len == 2)
	{
		if(line == "$$")
		{
			input_expression.pop_back();
			input_expression.pop_back();
			executeexpression();
			return status::done;
		}
		else if(line.substr( len-1 ) == "$")
		{
			input_expression.pop_back();
			executeexpression();
			return status::success;
		}
	}
	else
	{
		if(line.substr( len-2 ) == "$$")
		{
			input_expression.pop_back();
			input_expression.pop_back();
			executeexpression();
			return status::done;
		}
		else if(line.substr( len-1 ) == "$")
		{
			input_expression.pop_back();
			executeexpression();
			return status::success;
		}
		else
		{
			return status::success;
		}
	}
}

/* Reads input */
int main()
{
	string line;
	status ret;

	do
	{
		getline(cin,line);
		ret = parseinput(line);
	}
	while(ret != status::done);
	//cout << "Bye, Have a good day!" << endl;
	return 0;
}
