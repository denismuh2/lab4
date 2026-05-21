#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    string key; // Ключ для RC4
    int N;     // Количество генерируемых чисел
    cout << "Введите ключ: ";
    cin >> key;

    // проверка: ключ не должен быть пустым
    if (key.empty()) {
        cout << "Ошибка: ключ не может быть пустым\n";
        return 1;
    }
    cout << "Введите количество чисел N: ";
    cin >> N;

//KSA (Key Scheduling Algorithm) перемешивается массив с помощью ключа
    vector<int> S(256);
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;

    for (int i = 0; i < 256; i++) {
        j = (j + S[i] +
            (unsigned char)key[i % key.length()]) % 256; // берёт символ ключа циклически ASCII

        swap(S[i], S[j]); // Меняем местами элементы S[i] и S[j]
    }

    // PRGA (Pseudo-Random Generation Algorithm)
    int i = 0;
    j = 0;
    cout << "\nСгенерированные псевдослучайные числа:\n";

    // Генерация N чисел
    for (int k = 0; k < N; k++) {

        i = (i + 1) % 256; // Увеличиваем i по модулю 256
        j = (j + S[i]) % 256; // Изменяем j в зависимости от значения S[i]

        swap(S[i], S[j]);         // Снова меняем элементы местами

        int t = (S[i] + S[j]) % 256; // Вычисляем индекс t
        int K_byte = S[t]; // Получаем псевдослучайный байт

        // Вывод числа
        cout << K_byte << " ";
    }
    cout << endl;
    return 0;
}
