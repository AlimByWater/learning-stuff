/*
   В этой задаче вам надо разработать класс для представления рациональных чисел и внедрить его в систему 
   типов языка С++ так, чтобы им можно было пользоваться естественным образом.

   Класс Rational должен гарантировать, что p/q — это несократимая дробь.
   Так же, реализовать операторы(==, +, -, /, *), так чтобы с дробями можно было бы рабоать естественным образом.
   Реализовать операторы ввода и выводы.

   С помощью исключений обработать ситуации, когда знаменатель равен нулю и при делении на ноль.

   В функции main() находится юнит-тест для арифметических операций над дробями
   Входные данные могут быть в формате 1/2 + 1/4, например

*/




#include <iostream>
#include <numeric>      // для gcd() - НОД двух чисел
#include <algorithm>    // для min() и max()
#include <iomanip>      // для setw() - устанавливает ширину перед вводом
using namespace std;


class Rational {
public:
    Rational() { // конструктор по умолчанию 0/1
        numerator = 0;
        denominator = 1;
    }

    Rational(int a, int b) { // конструктор 
        numerator = a;
        if (b < 0) {
            denominator = -b;               // Если Знаменатель меньше нуля, то
            numerator = min(numerator, -a); //делаем его положительным,а Числитель отрицательным
        } else {
            denominator = b;
        }   
        
        // Обработка случая, когда знаменатель = 0
        if (b == 0) throw invalid_argument("Denominator can't be a zero");

        //если НОД не равен 1 - делаем дробь несократимой
        int nod = gcd(numerator,denominator); 
        if (nod != 1) {                            
            numerator = numerator / nod;
            denominator = denominator / nod;
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;

};

Rational operator+(const Rational& lhs, const Rational& rhs){
    int nok = lhs.Denominator() * rhs.Denominator()/gcd(lhs.Denominator(), rhs.Denominator());
    return Rational{lhs.Numerator()*(nok/lhs.Denominator()) + rhs.Numerator()*(nok/rhs.Denominator()),
    nok};
}

Rational operator-(const Rational& lhs, const Rational& rhs){
    int nok = lhs.Denominator() * rhs.Denominator()/gcd(lhs.Denominator(), rhs.Denominator());
    return Rational{lhs.Numerator()*(nok/lhs.Denominator()) - rhs.Numerator()*(nok/rhs.Denominator()),
    nok};
}


bool operator==(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()
        && lhs.Numerator() == rhs.Numerator())
        return true;
    return false;
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational{lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator()};
}

Rational operator/(const Rational& lhs, const Rational& rhs){
    if (lhs.Numerator() == 0 || rhs.Numerator() == 0 ){
        throw domain_error("Divizion by zero");
    }  else
        return Rational{lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator()};
}

// Перегрузка оператора вывода для класса Rational
// в формате n/d 
ostream& operator<<(ostream& stream, const Rational& rational){
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

// Эта функция принимает на вход две дроби и символ операции, которую надо
// провести над этими дробями. Возвращает результат вычисления.
Rational OpHandler(const Rational& lhs, const Rational& rhs, const char& op){
    
    Rational res;
    switch (op)
    {
        case '+': res = lhs + rhs; return res;
        case '-': res = lhs - rhs; return res;
        case '*': res = lhs * rhs; return res;
        case '/': res = lhs / rhs; return res;
    }
    
    return res;
}


Rational Calculate(istream& cin){
    int n1,d1,n2,d2;
    char op;

    // Вводить с консоли в формате можно в формате 1/2 + 1/4
    cin >> n1; cin.ignore(1); cin >> d1;            // ввод первой дроби 
    cin.ignore(1); op = getchar(); cin.ignore(1);  // ввод оператора
    cin >> n2; cin.ignore(1); cin >> d2;          // ввод второй дроби

    Rational res = OpHandler(Rational{n1, d1}, Rational{n2, d2}, op);
    return res;
}




int main() {

    cout << setw(20) <<  "Input your fraction expression" << '\n';
    try {                                   
        Rational res = Calculate(cin); // передаем входной поток с в специальную функцию
        cout << res << '\n';
    } catch (exception& ex) {
        cout << "exception happens: " << ex.what() << '\n';
    }
    return 0;
}