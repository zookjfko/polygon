#include <iostream>//ввод-вывод
#include <stdexcept>//обработка исключений
using namespace std;

class MyVector {
private://определение приватных членов класса.обеспечивает контроль над доступом к данным
    int* data;// Указатель на динамический массив
    size_t size;// Размер вектора

public:
    // Конструктор. принимает размер вектора
    MyVector(size_t size) : size(size) {
        if (size == 0) {//Если размер равен нулю, выбрасывается исключение
            throw invalid_argument("Размер должен быть > 0");
        }
        data = new int[size]();//Выделяется память для массива data с указанным размером и инициализируется нулями
    }

    // Деструктор. освобождает выделенную память для массива data, предотвращая утечки памяти
    ~MyVector() {
        delete[] data;
    }

    // Метод для получения размера вектора
    size_t getSize() const {//бъявлен как const: он не изменяет состояние объекта
        return size;
    }

    // Индексация. позволяет получить доступ к отдельным элементам в массиве 
    int& operator[](size_t index) {// Перегрузка оператора [] для доступа к элементам вектора
        if (index >= size) {
            throw out_of_range("Индекс выходит за пределы");
        }
        return data[index];//Возвращается ссылка на элемент массива, чтобы можно было изменять его значение
    }

    // Сложение векторов
    MyVector operator+(const MyVector& other) const {//Перегрузка оператора + для сложения двух векторов
        if (size != other.size) {//Проверерка совпадения размеров векторов 
            throw invalid_argument("Векторы должны иметь одинаковый размер для сложения");
        }
        MyVector result(size);//поэлементное сложение
        for (size_t i = 0; i < size; ++i) {//цикл проходит по всем эл-там массива. увеличение i на 1 после каждой итерации цикла
            result[i] = data[i] + other.data[i];//i эл-т текущего векора + i эл-т другого
        }
        return result;
    }

    // Вычитание векторов
    MyVector operator-(const MyVector& other) const {
        if (size != other.size) {
            throw invalid_argument("Векторы должны иметь одинаковый размер для вычитания");
        }
        MyVector result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Умножение векторов (поэлементное)
    MyVector operator*(const MyVector& other) const {
        if (size != other.size) {
            throw invalid_argument("Векторы должны иметь одинаковый размер для умножения");
        }
        MyVector result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] * other.data[i];
        }
        return result;
    }

    // Деление векторов (поэлементное)
    MyVector operator/(const MyVector& other) const {
        if (size != other.size) {
            throw invalid_argument("Векторы должны иметь одинаковый размер для деления");
        }
        MyVector result(size);
        for (size_t i = 0; i < size; ++i) {//проверка деления на ноль
            if (other.data[i] == 0) {
                throw runtime_error("Нельзя делить на ноль");
            }
            result[i] = data[i] / other.data[i];
        }
        return result;
    }

    // Метод для вывода вектора
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    try {
        MyVector v1(3);
        v1[0] = 1;
        v1[1] = 2;
        v1[2] = 3;

        MyVector v2(3);
        v2[0] = 4;
        v2[1] = 5;
        v2[2] = 0;

        MyVector sum = v1 + v2;
        MyVector diff = v1 - v2;
        MyVector prod = v1 * v2;
        MyVector quot = v1 / v2;

        cout << "v1: ";
        v1.print();
        
        cout << "v2: ";
        v2.print();

        cout << "Sum: ";
        sum.print();

        cout << "Difference: ";
        diff.print();

        cout << "Product: ";
        prod.print();

        cout << "Quotient: ";
        quot.print();
        
    } catch (const exception& e) {//обработка исключений
        cerr << "Ошибка: " << e.what() << endl;
    }//если возникает ошибка во время выполнения кода внутри блока try, она перехватывается и выводится сообщение об ошибке.

    return 0;
}
