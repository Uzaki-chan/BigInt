#ifndef _BigInt_H_
#define _BigInt_H_
struct BigInt {
    std::vector<int> Digits;
    bool IsNegativ;          
    BigInt() : IsNegativ(false) {}
    BigInt(const std::string& num);
    BigInt(int num);
    BigInt(long long num);
    BigInt(long num);
    void input();
    void output() const;
    BigInt operator-() const;
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    const BigInt operator++();
    const BigInt operator--();
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;
    bool odd() const;
    const BigInt pow(BigInt n) const;
};
#endif;