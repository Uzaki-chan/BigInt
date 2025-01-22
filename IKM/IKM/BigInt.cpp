#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"
BigInt toBigIntStr(std::string& num) {
    BigInt result;
    if (num[0] == '-') {
        result.IsNegativ = true;
        for (size_t i = num.size() - 1; i > 0; --i) {
            if (num[i] >= '0' && num[i] <= '9') {
                result.Digits.push_back(num[i] - '0');
            }
            else {
                std::cout << "были обнаружены и удалены буквы из ввода\n";
            }
        }
    }
    else {
        result.IsNegativ = false;
        for (size_t i = num.size(); i > 0; --i) {
            if (num[i - 1] >= '0' && num[i - 1] <= '9') {
                result.Digits.push_back(num[i - 1] - '0');
            }
            else {
                std::cout << "были обнаружены и удалены буквы из ввода\n";
            }
        }
    }
    return result;
}

// Создание от int
BigInt toBigIntInt(long long num) {
    BigInt result;
    if (num < 0) {
        result.IsNegativ = true;
        num = -num;
    }
    else {
        result.IsNegativ = false;
    }
    if (num == 0) {
        result.Digits.push_back(0);
    }
    while (num > 0) {
        result.Digits.push_back(num % 10);
        num /= 10;
    }
    return result;
}

// Функция ввода
void input(BigInt& th1s) {
    std::string num;
    std::cin >> num;
    th1s = toBigIntStr(num);
}

// Функция вывода
void output(BigInt th1s) {
    if (th1s.IsNegativ) {
        std::cout << '-';
    }
    if (th1s.Digits.empty()) {
        std::cout << '0';
    }
    else {
        for (size_t i = th1s.Digits.size(); i >0; --i) {
            std::cout << th1s.Digits[i-1];
        }
    }
}
// Унарный оператор для изменения знака числа
BigInt negative(BigInt th1s) {
    th1s.IsNegativ = !th1s.IsNegativ; // Изменяем знак
    return th1s;
}
// Операция сравнения
bool equally(BigInt left, BigInt right) {
    return left.IsNegativ == right.IsNegativ && left.Digits == right.Digits;
}
bool IsMin(BigInt left, BigInt right) {
    // Сравнение по модулю
    if (left.IsNegativ != right.IsNegativ) {
        return left.IsNegativ; // Если одно отрицательное, а другое нет, то меньше
    }
    if (left.Digits.size() != right.Digits.size()) {
        return left.IsNegativ ? (left.Digits.size() > right.Digits.size()) : (left.Digits.size() < right.Digits.size());
    }
    for (size_t i = 0; i < left.Digits.size(); ++i) {
        if (left.Digits[left.Digits.size() - 1 - i] != right.Digits[right.Digits.size() - 1 - i]) {
            return left.IsNegativ ? (left.Digits[left.Digits.size() - 1 - i] > right.Digits[right.Digits.size() - 1 - i]) :
                (left.Digits[left.Digits.size() - 1 - i] < right.Digits[right.Digits.size() - 1 - i]);
        }
    }
    return false; // Равны
}
// Операция вычитания (подразумевается, что this >= other)
BigInt substract(BigInt left, BigInt right) {
    if (IsMin(left, right)) {
        return negative(substract(right, left));
    }
    BigInt result;
    if (left.IsNegativ != right.IsNegativ) {
        return substract(right, negative(left));
    }
    // Реализация вычитания
    long carry = 0;
    size_t maxSize = left.Digits.size();
    for (size_t i = 0; i < maxSize; ++i) {
        long digit1 = left.Digits[i];
        long digit2 = (i < right.Digits.size()) ? right.Digits[i] : 0;
        long sub = digit1 - digit2 - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1; // берем заимствование
        }
        else {
            carry = 0;
        }
        result.Digits.push_back(sub);
    }
    // Удаляем ведущие нули
    while (result.Digits.size() > 1 && result.Digits.back() == 0) {
        result.Digits.pop_back();
    }

    // Устанавливаем знак результата
    if (result.Digits.empty() || (result.Digits.size() == 1 && result.Digits[0] == 0)) {
        result.IsNegativ = false; // результат 0
    }
    else {
        result.IsNegativ = (left.IsNegativ); // сохраняем знак
    }

    return result;
}
// Операция сложения
BigInt summ(BigInt left, BigInt right) {
    BigInt result;
    if (left.IsNegativ == right.IsNegativ) {
        result.IsNegativ = left.IsNegativ;  // Сохраняем знак
        long carry = 0;
        size_t maxSize = left.Digits.size() > right.Digits.size() ? left.Digits.size() : right.Digits.size();
        for (size_t i = 0; i < maxSize || carry != 0; ++i) {
            long sum = carry;
            if (i < left.Digits.size()) sum += left.Digits[i];
            if (i < right.Digits.size()) sum += right.Digits[i];
            result.Digits.push_back(sum % 10);
            carry = sum / 10;
        }
    }
    else if (!(left.IsNegativ)) {
        // A + (-B) = A - B
        return substract(left, negative(right));
    }
    else {
        // -A + B = B - A
        return substract(right, negative(left));
    }
    return result;
}



BigInt multiply(BigInt left, BigInt right) {
    // Хранит результат умножения
    BigInt result = toBigIntInt(0);
    result.Digits.resize(left.Digits.size() + right.Digits.size(), 0);

    // Умножение
    for (size_t i = 0; i < left.Digits.size(); ++i) {
        long long carry = 0;  // Перенос
        for (size_t j = 0; j < right.Digits.size() || carry; ++j) {
            long long current = result.Digits[i + j] + carry; // Текущая ячейка
            if (j < right.Digits.size()) {
                current += left.Digits[i] * right.Digits[j]; // Умножение
            }
            result.Digits[i + j] = current % 10; // Последняя цифра
            carry = current / 10; // Перенос
        }
    }

    // Убираем ведущие нули
    while (result.Digits.size() > 1 && result.Digits.back() == 0) {
        result.Digits.pop_back();
    }

    result.IsNegativ = left.IsNegativ != right.IsNegativ; // Устанавливаем знак результата
    return result;
}
// Деление
BigInt shift(BigInt left, BigInt right) {
    if (equally(right, toBigIntInt(0))) {
        throw std::invalid_argument("Деление на ноль");
    }
    BigInt result = toBigIntInt(0);
    BigInt denominator = left;
    BigInt numerator = right;
    result.IsNegativ = (left.IsNegativ != right.IsNegativ); // Устанавливаем знак

    denominator.IsNegativ = false; // Работаем с положительными числами
    numerator.IsNegativ = false;

    while (!(IsMin(denominator, numerator)) || equally(denominator, numerator)) {
        denominator = substract(denominator, numerator);
        result = summ(result, toBigIntInt(1)); // Увеличиваем результат
    }

    return result;
}
BigInt remains(BigInt left, BigInt right) {
    if (equally(right, toBigIntInt(0))) {
        throw std::invalid_argument("Деление на ноль");
    }
    BigInt denominator = left;
    BigInt numerator = right;

    denominator.IsNegativ = false; // Работаем с положительными числами
    numerator.IsNegativ = false;

    while (!(IsMin(denominator, numerator)) || equally(denominator, numerator)) {
        denominator = substract(denominator, numerator);
    }

    return denominator;
}
// проверяет, является ли текущее число нечетным
bool odd(BigInt th1s) {
    if (th1s.Digits.size() == 0) return false;  // Убедитесь, что число не пустое
    return (th1s.Digits[0] % 2);  // Возвращает true, если последнее число нечетное
}
BigInt pow(BigInt a, BigInt n) {
    if (equally(n, toBigIntInt(0))) return toBigIntInt(1);  // любое число в нулевой степени равно 1
    if (IsMin(n, toBigIntInt(0))) throw std::invalid_argument("Возведение в отрицательную степень");
    BigInt result = toBigIntInt(1);  // Инициализируем result как 1
    while (!(equally(n, toBigIntInt(0)))) {
        if (odd(n)) result = multiply(result, a); // умножаем на основание если n нечетное
        a = multiply(a, a);  // возводим основание в квадрат
        n = shift(n, toBigIntInt(2));  // делим n на 2
    }

    return result;
}