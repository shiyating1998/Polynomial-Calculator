

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <string>
using namespace std;

class Expression{
    public:
        virtual void prettyprint()=0;
        virtual void unset(string var)=0;
        virtual void set(string var, int a)=0;
        virtual int evaluate()=0;
        virtual ~Expression();
};

class LoneInt:public Expression{
    int x;
    public:
        LoneInt(int a); //ctor
        void prettyprint() override;
        int evaluate() override;
        void unset(string var) override;
        void set(string var, int a) override;
};

class Variable:public Expression {
    string name;
    int val;
    bool hasVal = false;
    public:
        Variable(string str); //ctor
        void prettyprint() override;
        int evaluate() override;
        void set(string var, int a) override;
        void unset(string var) override;
        bool hasValue() const;
};

class UnaryExp:public Expression {
    bool NEG=false;
    bool ABS=false;
    Expression *exp=nullptr;

    public:
        UnaryExp(string str, Expression *exp); //ctor
        ~UnaryExp(); //dtor

        void prettyprint() override;
        int evaluate() override;
        void unset(string var) override;
        void set(string var, int a) override;
};

class BinExp:public Expression{
    char op;
    Expression *operand1=nullptr;
    Expression *operand2=nullptr;

    public:
        BinExp(string oper, Expression* op1, Expression* op2);
        ~BinExp();
        void prettyprint() override;
        int evaluate() override;
        void unset(string var) override;
        void set(string var, int a) override;
};
#endif

