#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"

int main() {
    setlocale(LC_ALL, "RU");
    std::string stop = "";
    while(stop != "no") {
        BigInt n;
        std::cout << "введите число n>=10,чтобы посчитать сумму последовательности от 1^n до n^n\n";
        input(n);
        while (IsMin(n, toBigIntInt(1))) {

            std::cout << "вы ввели n<10 или ввели слово, или букву, вводите n снова \n";
            input(n);

        }
        BigInt n1 = summ(n, toBigIntInt(1));
        BigInt result = toBigIntInt(1);
        for (BigInt i{ toBigIntInt(2) }; IsMin(i, n1); i = summ(i, toBigIntInt(1))) {
            result = summ(result, pow(i, n));
        }
        std::cout << "сумма = ";
        output(result);
        std::cout << "\n";
        std::cout << "Хотите вычислить ещё 1 число yes/no\n";
        std::cin >> stop;
    }
    return 0;
}