#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"

int main() {
    setlocale(LC_ALL, "RU");
    BigInt n;
    std::cout << "введите число n>=10,чтобы посчитать сумму последовательности от 1^n до n^n\n";
    n.input();
    while (n < 10) {

        std::cout << "вы ввели n<10, вводите снова или ввели слово, или букву\n";
        n.input();

    }
    BigInt result = 0;
    for (BigInt i{ 1 }; i <= n; ++i) {
        result += i.pow(n);
    }
    std::cout << "сумма = ";
    result.output();
    return 0;
}
