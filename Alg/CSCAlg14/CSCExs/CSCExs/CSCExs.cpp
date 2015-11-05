#include <string>
#include <iostream>
#include "stdafx.h"

using namespace std;

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
	virtual ~Expression() { }
	virtual double evaluate() const = 0;
	virtual Expression *transform(Transformer *tr) const = 0;
};

struct Transformer
{
	virtual ~Transformer() { }
	virtual Expression *transformNumber(Number const *) = 0;
	virtual Expression *transformBinaryOperation(BinaryOperation const *) = 0;
	virtual Expression *transformFunctionCall(FunctionCall const *) = 0;
	virtual Expression *transformVariable(Variable const *) = 0;
};

struct Number : Expression
{
	Number(double value);
	double value() const;
	double evaluate() const;
	Expression *transform(Transformer *tr) const;

private:
	double value_;
};

struct BinaryOperation : Expression
{
	enum {
		PLUS = '+',
		MINUS = '-',
		DIV = '/',
		MUL = '*'
	};
	BinaryOperation(Expression const *left, int op, Expression const *right);
	~BinaryOperation();
	double evaluate() const;
	Expression *transform(Transformer *tr) const;
	Expression const *left() const;
	Expression const *right() const;
	int operation() const;

private:
	Expression const *left_;
	Expression const *right_;
	int op_;
};

struct FunctionCall : Expression
{
	FunctionCall(std::string const &name, Expression const *arg);
	~FunctionCall();
	double evaluate() const;
	Expression *transform(Transformer *tr) const;
	std::string const &name() const;
	Expression const *arg() const;

private:
	std::string const name_;
	Expression const *arg_;
};

struct Variable : Expression
{
	Variable(std::string const name);
	std::string const & name() const;
	double evaluate() const;
	Expression *transform(Transformer *tr) const;

private:
	std::string const name_;
};


/**
* реализуйте все необходимые методы класса
* вы можете определять любые вспомогательные
* методы, если хотите
*/
struct CopySyntaxTree : Transformer
{
	Expression *transformNumber(Number const *number)
	{
		Number *tmp = new Number(number->value());
		return tmp;
	}

	Expression *transformBinaryOperation(BinaryOperation const *binop)
	{ 
		Expression const *exp = binop->left();
		Transformer *tr = new CopySyntaxTree();
		Expression *exp1 = exp->transform(tr);
		exp = binop->right();
		Expression *exp2 = exp->transform(tr);
		
		BinaryOperation *tmp = new BinaryOperation(exp1, binop->operation(), exp2);
		return tmp;
	}

	Expression *transformFunctionCall(FunctionCall const *fcall)
	{
		Expression const *exp = fcall->arg();
		Transformer *tr = new CopySyntaxTree();
		Expression *exp1 = exp->transform(tr);

		FunctionCall *tmp = new FunctionCall(fcall->name(), exp1);
		return tmp;
	}

	Expression *transformVariable(Variable const *var)
	{ 
		Variable *tmp = new Variable(var->name());
		return tmp;
	}

	
};



int main() {
	Expression *expression = new Number(10.0);
	Transformer *transformer = new CopySyntaxTree();
	Expression *new_expression = expression->transform(transformer);

	delete expression;
	delete transformer;
	cout << "number: " << new_expression->evaluate() << endl;
	delete new_expression;

	expression = new Variable("x");
	transformer = new CopySyntaxTree();
	new_expression = expression->transform(transformer);

	delete expression;
	delete transformer;
	//cout<<"new variable: "<<new_expression->evaluate()<<endl;
	delete new_expression;

	enum { PLUS = '+', MINUS = '-', DIV = '/', MUL = '*' };
	struct Number *x = new Number(2);
	struct Number *y = new Number(3);

	expression = new BinaryOperation(x, MUL, y);
	transformer = new CopySyntaxTree();
	new_expression = expression->transform(transformer);

	delete expression;
	delete transformer;
	cout << "binary operation: " << new_expression->evaluate() << endl;
	delete new_expression;

	expression = new FunctionCall("sqrt", x);
	transformer = new CopySyntaxTree();
	new_expression = expression->transform(transformer);

	delete expression;
	delete transformer;
	cout << "function call: " << new_expression->evaluate() << endl;
	delete new_expression;

	//system("pause");
	return 0;
}
