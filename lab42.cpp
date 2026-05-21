#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

int main() {

    random_device rd;
    mt19937 gen(rd());          // генератор случайных чисел mt19937

    const int n = 10;           // размер массива
    uniform_int_distribution<> dist(-100, 100);  // диапазон случайных чисел

    vector<int> arr(n);
    for (int& x : arr)  // заполняем массив случайными числами
        x = dist(gen);

    cout << "Исходный массив mt19937:\n";
    for (int x : arr)
        cout << x << " ";
    cout << "\n\n";

    // Пункт 2
    int positive_count = 0; // подсчет количества положительных элементов
    for (int x : arr) {
        if (x > 0)
            positive_count++;
    }
    int max_abs_index = 0;  // поиск индекса элемента с максимальным модулем
    for (int i = 1; i < arr.size(); i++) {

        if (abs(arr[i]) > abs(arr[max_abs_index])) { // если текущий элемент больше по модулю, запоминаем индекс
            max_abs_index = i;  //
        }
    }

    int sum_after = 0; // вычисление суммы элементов, после максимального
    for (int i = max_abs_index + 1; i < arr.size(); i++) {
        sum_after += arr[i];
    }
    cout << " Пункт 2 \n";
    cout << "Количество положительных элементов: " << positive_count << endl;
    cout << "Максимальный по модулю элемент: " << arr[max_abs_index]
         << " (индекс " << max_abs_index << ")\n";
    cout << "Сумма элементов после него: " << sum_after << "\n\n";

    // Пункт 3
    int best_start = 0;     // Начальный лучшей последовательности
    int best_length = 1;    // Длина лучшей

    int current_start = 0;
    int current_length = 1;

    for (int i = 1; i < arr.size(); i++) {

        if (arr[i] > arr[i - 1]) {
            current_length++; // Если текущий элемент больше предыдущего, увеличиваем длину последовательности
        }
        else {
            if (current_length > best_length) { //прервалась, сравниваем с лучшей
                best_length = current_length;
                best_start = current_start;
            }
            current_start = i;
            current_length = 1;
        }
    }
    if (current_length > best_length) {
        best_length = current_length;
        best_start = current_start;
    }

    vector<int> posledv; // // массив для хранения найденной последовательности
    for (int i = best_start; i < best_start + best_length; i++) {
        posledv.push_back(arr[i]);  // Копируем элементы
    }

    // Вывод результатов пункта 3
    cout << " Пункт 3 \n";
    cout << "Самая длинная возрастающая последовательность:\n";
    for (int x : posledv)
        cout << x << " ";
    cout << "\n";
    cout << "Длина последовательности: " << posledv.size() << "\n\n";

    // Пункт 4
    cout << " Пункт 4 \n";
    int positive = 0;
    int negative = 0; // количество + и - чисел

    for (int x : arr) {
        if (x > 0)
            positive++;
        else if (x < 0) // 0 не учитывается
            negative++;
    }
    if (positive > negative) {
        for (int& x : arr) { // + больше => заменяем все - числа на 0
            if (x < 0)
                x = 0;
        }
        cout << "Положительных больше.\n";
        cout << "Все отрицательные заменены на 0.\n";
    }
    else if (negative > positive) {
        for (int& x : arr) { // - больше => заменяем все + числа на 1
            if (x > 0)
                x = 1;
        }
        cout << "Отрицательных больше.\n";
        cout << "Все положительные заменены на 1.\n";
    }
    else {
        cout << "Количество положительных и отрицательных равно.\n"; // если + = -
    }
    cout << "\nМодифицированный массив:\n";
    for (int x : arr)
        cout << x << " ";
    cout << "\n\n";

    // Пункт 5
    cout << " Пункт 5 \n";

    int N;  // строки в матрице

    while (true) { // Проверка корректности ввода
        cout << "Введите N (положительное целое число): ";

        if (cin >> N) {     // считали ли число
            if (N > 0) {
                break;
            } else {
                cout << "Ошибка: N должно быть больше 0\n";
            }
        } else {  // если ввели не число
            cin.clear();                // Сброс флага ошибки
            cin.ignore(32767, '\n');    // Очистка буфера ввода
            cout << "Ошибка: Введите целое число\n";
        }
    }
    // матрица (двумерный вектор) размером N строк и 6 столбцов
    vector<vector<int>> matrix(N, vector<int>(6));
    int even_start = 50; // четные строки
    int odd_start = 95; // нечетные строки

    for (int i = 0; i < N; i++) {  // заполняем матрицу построчно

        if (i % 2 == 0) {  // четные строки возрастают на 10
            for (int j = 0; j < 6; j++) {
                matrix[i][j] = even_start + j * 10;
            }
            even_start += 30;
        }
        else {
            for (int j = 0; j < 6; j++) { // нечетные убывают на 5
                matrix[i][j] = odd_start - j * 5;
            }
            odd_start += 30;
        }
    }
    cout << "\nРезультат:\n";
    for (const auto& row : matrix) {
        for (int x : row)
            cout << x << "\t";
        cout << endl;
    }
    return 0;
}
