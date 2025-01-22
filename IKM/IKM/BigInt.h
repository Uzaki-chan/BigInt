#ifndef _BigInt_H_
#define _BigInt_H_
#include <iostream>
#include <vector>
#include <string>
struct BigInt {
    std::vector<int> Digits;  // Хранит цифры в обратном порядке
    bool IsNegativ;            // Указывает, является ли число отрицательным
};
BigInt toBigIntStr(std::string& num);
BigInt toBigIntInt(long long num);
void input(BigInt& th1s);
void output(BigInt th1s);
BigInt negative(BigInt th1s);
BigInt summ(BigInt left, BigInt right);
BigInt substract(BigInt left, BigInt right);
bool equally(BigInt left, BigInt right);
bool IsMin(BigInt left, BigInt right);
BigInt multiply(BigInt left, BigInt right);
BigInt shift(BigInt left, BigInt right);
BigInt remains(BigInt left, BigInt right);
bool odd(BigInt th1s);
BigInt pow(BigInt a, BigInt n);
#endif;