#ifndef _BigInt_H_
#define _BigInt_H_
#include <iostream>
#include <vector>
#include <string>
struct BigInt {
    std::vector<int> Digits;  // ������ ����� � �������� �������
    bool IsNegativ;            // ���������, �������� �� ����� �������������

    // �������� ������ ���������� �� ���������
    BigInt() : IsNegativ(false) {}

    // �������� �� ������
    BigInt(const std::string& num) {
        if (num[0] == '-') {
            IsNegativ = true;
            for (size_t i = num.size() - 1; i > 0; --i) {
                if (num[i-1] >= '0' && num[i-1] <= '9') {
                    Digits.push_back(num[i-1] - '0');
                }
                else {
                    std::cout << "���� ���������� � ������� ����� �� �����\n";
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
                    std::cout << "���� ���������� � ������� ����� �� �����\n";
                }
            }
        }
    }

    // �������� �� int
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

    // ������� �����
    void input() {
        std::string num;
        std::cin >> num;
        *this = BigInt(num);
    }

    // ������� ������
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
    // ������� �������� ��� ��������� ����� �����
    BigInt operator-() const {
        BigInt result = *this;
        result.IsNegativ = !IsNegativ; // �������� ����
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
    // �������� ��������
    BigInt operator+(const BigInt& other) const {
        BigInt result;
        if (this->IsNegativ == other.IsNegativ) {
            result.IsNegativ = this->IsNegativ;  // ��������� ����
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

    // �������� ��������� (���������������, ��� this >= other)
    BigInt operator-(const BigInt& other) const {
        if (*this < other) {
            return -(other - *this);
        }
        BigInt result;
        if (this->IsNegativ != other.IsNegativ) {
            return *this + (-other);
        }
        // ���������� ���������
        long carry = 0;
        size_t maxSize = Digits.size();
        for (size_t i = 0; i < maxSize; ++i) {
            long digit1 = Digits[i];
            long digit2 = (i < other.Digits.size()) ? other.Digits[i] : 0;
            long sub = digit1 - digit2 - carry;
            if (sub < 0) {
                sub += 10;
                carry = 1; // ����� �������������
            }
            else {
                carry = 0;
            }
            result.Digits.push_back(sub);
        }
        // ������� ������� ����
        while (result.Digits.size() > 1 && result.Digits.back() == 0) {
            result.Digits.pop_back();
        }

        // ������������� ���� ����������
        if (result.Digits.empty() || (result.Digits.size() == 1 && result.Digits[0] == 0)) {
            result.IsNegativ = false; // ��������� 0
        }
        else {
            result.IsNegativ = (this->IsNegativ); // ��������� ����
        }

        return result;
    }
    // �������� ���������
    bool operator==(const BigInt& other) const {
        return IsNegativ == other.IsNegativ && Digits == other.Digits;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    bool operator<(const BigInt& other) const {
        // ��������� �� ������
        if (IsNegativ != other.IsNegativ) {
            return IsNegativ; // ���� ���� �������������, � ������ ���, �� ������
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
        return false; // �����
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
        // ������ ��������� ���������
        BigInt result("0");
        result.Digits.resize(Digits.size() + other.Digits.size(), 0);

        // ���������
        for (size_t i = 0; i < Digits.size(); ++i) {
            long long carry = 0;  // �������
            for (size_t j = 0; j < other.Digits.size() || carry; ++j) {
                long long current = result.Digits[i + j] + carry; // ������� ������
                if (j < other.Digits.size()) {
                    current += Digits[i] * other.Digits[j]; // ���������
                }
                result.Digits[i + j] = current % 10; // ��������� �����
                carry = current / 10; // �������
            }
        }

        // ������� ������� ����
        while (result.Digits.size() > 1 && result.Digits.back() == 0) {
            result.Digits.pop_back();
        }

        result.IsNegativ = IsNegativ != other.IsNegativ; // ������������� ���� ����������
        return result;
    }
    // �������
    BigInt operator/(const BigInt& other) const {
        if (other == 0) {
            throw std::invalid_argument("������� �� ����");
        }
        BigInt result("0");
        BigInt denominator = *this;
        BigInt numerator = other;
        result.IsNegativ = (IsNegativ != other.IsNegativ); // ������������� ����

        denominator.IsNegativ = false; // �������� � �������������� �������
        numerator.IsNegativ = false;

        while (denominator >= numerator) {
            denominator = denominator - numerator;
            result += 1; // ����������� ���������
        }

        return result;
    }
    BigInt operator%(const BigInt& other) const {
        if (other == 0) {
            throw std::invalid_argument("������� �� ����");
        }
        BigInt denominator = *this;
        BigInt numerator = other;

        denominator.IsNegativ = false; // �������� � �������������� �������
        numerator.IsNegativ = false;

        while (denominator >= numerator) {
            denominator = denominator - numerator;
        }

        return denominator;
    }
    // ���������, �������� �� ������� ����� ��������
    bool odd() const {
        if (this->Digits.size() == 0) return false;  // ���������, ��� ����� �� ������
        return (this->Digits[0] % 2);  // ���������� true, ���� ��������� ����� ��������
    }

    const BigInt pow(BigInt n) const {
        if (n == 0) return 1;  // ����� ����� � ������� ������� ����� 1
        if (n < 0) throw std::invalid_argument("���������� � ������������� �������");

        BigInt a(*this), result(1);  // �������������� result ��� 1
        while (n != 0) {
            if (n.odd()) result = result * a; // �������� �� ��������� ���� n ��������
            a = a * a;  // �������� ��������� � �������
            n = n / 2;  // ����� n �� 2
        }

        return result;
    }
};
#endif;