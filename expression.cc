#include "expression.h"
#include <iostream>
#include <string>
using namespace std;
// Expression class

Expression::~Expression(){} //pure virtual dtor definition


// LoneInt class
LoneInt::LoneInt(int a): x{a}{}

void LoneInt::prettyprint(){
    cout << x;
}

int LoneInt::evaluate(){
    return x;
}

void LoneInt::unset(string var) {}
void LoneInt::set(string var, int a) {}


// Variable class
Variable::Variable(string str): name(str){}

void Variable::prettyprint() {
    if (hasValue()){
        cout<<val;
    }
    else {
        cout<<name;
    }
}

int Variable::evaluate() {
    if (hasValue()){
        return val;
    }
    else {
        string msg = name + " has no value.";
        throw msg;
    }
}

void Variable::set(string var, int a) {
    if (var==name) {
        val = a;
        hasVal = true;
    }
}

void Variable::unset(string var) {
    if (var==name)
        hasVal = false;
}

bool Variable::hasValue() const {
    return hasVal;
}



//UnaryExp class
UnaryExp::UnaryExp(string str, Expression *ex) {
    if (str=="NEG") {
        NEG = true;
    }
    else if (str=="ABS") {
        ABS = true;
    }

    exp = ex;
}


UnaryExp::~UnaryExp(){
    delete exp;
}

void UnaryExp::prettyprint(){
    if (NEG==true){
        cout << "-";
        exp->prettyprint();
    }
    else {
        cout << "|";
        exp->prettyprint();
        cout << "|";
    }
}

int UnaryExp::evaluate(){
    int val = exp->evaluate();
    if (NEG) {
        return -1*val;
    }
    else {
        if (val<0) {
            val *= -1;
        }
        return val;
    }
}
void UnaryExp::unset(string var) {
    exp->unset(var);
}
void UnaryExp::set(string var, int a) {
    exp->set(var,a);
}

//class BinExp
BinExp::BinExp(string oper, Expression *op1, Expression *op2):
    operand1{op1}, operand2{op2}{
        op = oper[0];
    }

BinExp::~BinExp(){
    delete operand1;
    delete operand2;
}

void BinExp::prettyprint() {
    cout << "(";
    operand1->prettyprint();
    cout << " " << op << " ";
    operand2->prettyprint();
    cout << ")" ;
}
int BinExp::evaluate() {
    int val1 = operand1->evaluate();
    int val2 = operand2->evaluate();
    if (op=='+') {
        return val1+val2;
    }
    else if (op=='-'){
        return val1-val2;
    }
    else if (op=='*'){
        return val1*val2;
    }
    else if (op=='/'){
        if (val2==0) {
            string msg = "Floating point exception";
            throw msg;
        }
        return val1/val2;
    }
}

void BinExp::unset(string var) {
    operand1->unset(var);
    operand2->unset(var);
}
void BinExp::set(string var, int a) {
    operand1->set(var,a);
    operand2->set(var,a);
}

