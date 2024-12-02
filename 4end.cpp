#include <iostream> 
#include <vector>
using namespace std;

bool canPartition(vector<int>& nums, vector<int>& subset1, vector<int>& subset2) { 
//ссылка на вектор целых чисел, представляющий входной массив;вектор хранения 1 подмн. и 2 подмн.
    /// Входной вектор nums: размер вектора n * 4(размер int)
    /// Векторы subset1 и subset2: изначально пустые, но могут занимать память до  n * 4
    
    
    int totalSum = 0;//переменная для хранения общей суммы элементов массива///4 байта
    for (int num : nums) {//переменная num используется для хранения текущего элемента в каждой итерации цикла
                         //на каждой итерации переменная num будет принимать значение следующего элемента из вектора nums
                         /// num: 4 байта 
        totalSum += num;//добавляет текущий элемент к общей сумме.
    }
///O(n)

    // Если сумма нечетная, невозможно разделить на две равные части
    if (totalSum % 2 != 0) {
        return false;//если остаток от деления на 2 не равен 0 -> нечетная сумма
    }
////O(1) constant
    
    int target = totalSum / 2;//вычисляем целевую сумму для каждого из подмн.///4 байт
    int n = nums.size();//узнаем количество элементов в векторе///4 байта

    
    // Перебор всех подмножеств
    for (int mask = 0; mask < (1 << n); ++mask) {
    //1.инициализируем переменную mask с начальным значением 0. Булеан элементов. Каждое подмножество можно представить как последовательность битов, где каждый бит указывает, включен ли элемент в подмножество или нет
    //2.сравниваем текущее значение переменной mask с результатом операции 1 << n(побитовый сдвиг влево); ↓↓↓т.е.
    //не превышает ли значение mask количество всех возможных подмножеств(не превышает 2^n) для n элементов
    //3.в конце каждой итерации значение mask увеличивается на 1, чтобы перейти к следующей комбинации
    ///mask: 4 байта
    //// O(2^n) combinations
        int subsetSum = 0;//инициализируем сумму текущего подмножества.///4 байта
        subset1.clear();//очищаем предыдущие значения подмножеств перед началом новой итерации.Иначе в output будет перемешивание значений
        subset2.clear();


    //генерации подмножеств из массива чисел, используя битовые маски. 
        for (int i = 0; i < n; ++i) { //проходимся от 0 до n(кол-во эл-тов массива)
                                      //возвращает i после выполнения операции сложения i+1
                                      ///i: 4 байта
            if (mask & (1 << i)) { //  Проверяет, включен ли текущий элемент (по индексу) в подмн. с помощью битовой маски.
                                   //Если i-ый элемент включен в подмножество
                                   ////O(n)
                subsetSum += nums[i];
            //После выполнения этой строки переменная subsetSum будет содержать сумму всех элементов, которые были добавлены в текущее подмн.
                subset1.push_back(nums[i]); // если включен, добавляем в первое подмножество
                                            ///subset1 : (n * 4)
            } else {
                subset2.push_back(nums[i]); // если нет, добавляем в второе подмножество
                                            ///subset2 : (n * 4)
            }
        }

        if (subsetSum == target) {
            return true; // Найдено подмножество с суммой, равной target-->найдено подходящее разделение
        }
    }

    return false; // Не найдено подходящее подмножество
}

int main() {
    vector<int> arr = {1, 4, 3}; 
    vector<int> subset1, subset2;

    if (canPartition(arr, subset1, subset2)) {
        cout << "Массив можно разделить на две части с равной суммой." << endl;
        cout << "Подмножества: ["; 
        for (int i = 0; i < subset1.size(); ++i) {
            cout << subset1[i];
            if (i < subset1.size() - 1) cout << ", "; //строка проверяет, является ли текущий индекс i последним элементом. if no, add space
        }
        cout << "], [";
        for (int i = 0; i < subset2.size(); ++i) {
            cout << subset2[i];
            if (i < subset2.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    } else {
        cout << "Массив нельзя разделить на две части с равной суммой." << endl;
    }

    return 0;
}

///Память --> Для переменных (totalSum, num, target, n, subsetSum, mask, i): 7 * 4 = 28 байт.
///Для векторов: nums + subset1 + subset2 = n * 4 + n * 4 + n * 4 = 3n * 4 байт.
///Общая память: 28 + 3n * 4

////Ассимптотика: О(n * 2^n)