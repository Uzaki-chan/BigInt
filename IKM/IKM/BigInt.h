#ifndef _BigInt_H_
#define _BigInt_H_
#include <iostream>
#include <vector>
#include <string>
struct BigInt {
    std::vector<int> Digits;  // Хранит цифры в обратном порядке
    bool IsNegativ;            // Указывает, является ли число отрицательным

    // Создание просто переменной по умолчанию
    BigInt() : IsNegativ(false) {}

    // Создание от строки
    BigInt(const std::string& num) {
        if (num[0] == '-') {
            IsNegativ = true;
            for (size_t i = num.size() - 1; i > 0; --i) {
                if (num[i-1] >= '0' && num[i-1] <= '9') {
                    Digits.push_back(num[i-1] - '0');
                }
                else {
                    std::cout << "были обнаружены и удалены буквы из ввода\n";
                }
            }
        }
        else {
            IsNegativ = false;
            for (size_t i = num.size(); i > 0; --i) {
                if (num[i-1] >= '0' && num[i-1] <= '9') {
                    Digits.push_back(num[i-1] - '0');
                }
                else {
                    std::cout << "были обнаружены и удалены букви из ввода\n";
                }
            }
        }
    }

    // Создание от int
    BigInt(int num) {
        if (num < 0) {
            IsNegativ = true;
            num = -num;
        }
        else {
            IsNegativ = false;
        }
        if (num == 0) {
            Digits.push_back(0);
        }
        while (num > 0) {
            Digits.push_back(num % 10);
            num /= 10;
        }
    }
    BigInt(long long num) {
        if (num < 0) {
            IsNegativ = true;
            num = -num;
        }
        else {
            IsNegativ = false;
        }
        while (num > 0) {
            Digits.push_back(num % 10);
            num /= 10;
        }
    }
    BigInt(long num) {
        if (num < 0) {
            IsNegativ = true;
            num = -num;
        }
        else {
            IsNegativ = false;
        }
        while (num > 0) {
            Digits.push_back(num % 10);
            num /= 10;
        }
    }

    // Функция ввода
    void input() {
        std::string num;
        std::cin >> num;
        *this = BigInt(num);
    }

    // Функция вывода
    void output() const {
        if (IsNegativ) {
            std::cout << '-';
        }
        if (Digits.empty()) {
            std::cout << '0';
        }
        else {
            for (size_t i = Digits.size(); i > 0; --i) {
                std::cout << Digits[i - 1];
            }
        }
    }
    // Унарный оператор для изменения знака числа
    BigInt operator-() const {
        BigInt result = *this;
        result.IsNegativ = !IsNegativ; // Изменяем знак
        return result;
    }
    BigInt& operator+=(const BigInt& other) {
        return *this = (*this + other);
    }
    BigInt& operator-=(const BigInt& other) {
        return *this = (*this - other);
    }
    const BigInt operator++() {
        return (*this += 1);
    }
    const BigInt operator--() {
        return (*this -= 1);
    }
    // Операция сложения
    BigInt operator+(const BigInt& other) const {
        BigInt result;
        if (this->IsNegativ == other.IsNegativ) {
            result.IsNegativ = this->IsNegativ;  // Сохраняем знак
            long carry = 0;
            size_t maxSize = Digits.size() > other.Digits.size() ? Digits.size() : other.Digits.size();
            for (size_t i = 0; i < maxSize || carry != 0; ++i) {
                long sum = carry;
                if (i < Digits.size()) sum += Digits[i];
                if (i < other.Digits.size()) sum += other.Digits[i];
                result.Digits.push_back(sum % 10);
                carry = sum / 10;
            }
        }
        else if (!(this->IsNegativ)) {
            // A + (-B) = A - B
            return *this - (-(other));
        }
        else {
            // -A + B = B - A
            return other - (-(*this));
        }
        return result;
    }

    // Операция вычитания (подразумевается, что this >= other)
    BigInt operator-(const BigInt& other) const {
        if (*this < other) {
            return -(other - *this);
        }
        BigInt result;
        if (this->IsNegativ != other.IsNegativ) {
            return *this + (-other);
        }
        // Реализация вычитания
        long carry = 0;
        size_t maxSize = Digits.size();
        for (size_t i = 0; i < maxSize; ++i) {
            long digit1 = Digits[i];
            long digit2 = (i < other.Digits.size()) ? other.Digits[i] : 0;
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
            result.IsNegativ = (this->IsNegativ); // сохраняем знак
        }

        return result;
    }
    // Операция сравнения
    bool operator==(const BigInt& other) const {
        return IsNegativ == other.IsNegativ && Digits == other.Digits;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    bool operator<(const BigInt& other) const {
        // Сравнение по модулю
        if (IsNegativ != other.IsNegativ) {
            return IsNegativ; // Если одно отрицательное, а другое нет, то меньше
        }
        if (Digits.size() != other.Digits.size()) {
            return IsNegativ ? (Digits.size() > other.Digits.size()) : (Digits.size() < other.Digits.size());
        }
        for (size_t i = 0; i < Digits.size(); ++i) {
            if (Digits[Digits.size() - 1 - i] != other.Digits[other.Digits.size() - 1 - i]) {
                return IsNegativ ? (Digits[Digits.size() - 1 - i] > other.Digits[other.Digits.size() - 1 - i]) :
                    (Digits[Digits.size() - 1 - i] < other.Digits[other.Digits.size() - 1 - i]);
            }
        }
        return false; // Равны
    }

    bool operator>(const BigInt& other) const {
        return other < *this;
    }
    bool operator>=(const BigInt& other) const {
        return other < *this || other == *this;
    }
    bool operator<=(const BigInt& other) const {
        return other > *this || other == *this;
    }
    BigInt operator*(const BigInt& other) const {
        // Хранит результат умножения
        BigInt result("0");
        result.Digits.resize(Digits.size() + other.Digits.size(), 0);

        // Умножение
        for (size_t i = 0; i < Digits.size(); ++i) {
            long long carry = 0;  // Перенос
            for (size_t j = 0; j < other.Digits.size() || carry; ++j) {
                long long current = result.Digits[i + j] + carry; // Текущая ячейка
                if (j < other.Digits.size()) {
                    current += Digits[i] * other.Digits[j]; // Умножение
                }
                result.Digits[i + j] = current % 10; // Последняя цифра
                carry = current / 10; // Перенос
            }
        }

        // Убираем ведущие нули
        while (result.Digits.size() > 1 && result.Digits.back() == 0) {
            result.Digits.pop_back();
        }

        result.IsNegativ = IsNegativ != other.IsNegativ; // Устанавливаем знак результата
        return result;
    }
    // Деление
    BigInt operator/(const BigInt& other) const {
        if (other == 0) {
            throw std::invalid_argument("Деление на ноль");
        }
        BigInt result("0");
        BigInt denominator = *this;
        BigInt numerator = other;
        result.IsNegativ = (IsNegativ != other.IsNegativ); // Устанавливаем знак

        denominator.IsNegativ = false; // Работаем с положительными числами
        numerator.IsNegativ = false;

        while (denominator >= numerator) {
            denominator = denominator - numerator;
            result += 1; // Увеличиваем результат
        }

        return result;
    }
    BigInt operator%(const BigInt& other) const {
        if (other == 0) {
            throw std::invalid_argument("Деление на ноль");
        }
        BigInt denominator = *this;
        BigInt numerator = other;

        denominator.IsNegativ = false; // Работаем с положительными числами
        numerator.IsNegativ = false;

        while (denominator >= numerator) {
            denominator = denominator - numerator;
        }

        return denominator;
    }
    // проверяет, является ли текущее число нечетным
    bool odd() const {
        if (this->Digits.size() == 0) return false;  // Убедитесь, что число не пустое
        return (this->Digits[0] % 2);  // Возвращает true, если последнее число нечетное
    }

    const BigInt pow(BigInt n) const {
        if (n == 0) return 1;  // любое число в нулевой степени равно 1
        if (n < 0) throw std::invalid_argument("Возведение в отрицательную степень");

        BigInt a(*this), result(1);  // Инициализируем result как 1
        while (n != 0) {
            if (n.odd()) result = result * a; // умножаем на основание если n нечетное
            a = a * a;  // возводим основание в квадрат
            n = n / 2;  // делим n на 2
        }

        return result;
    }
};
#endif;