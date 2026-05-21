#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// метод Борда, очки от 0 до n-1 кандидатов, избиратель составляет рейтинг
vector<int> bordaCount( const vector<vector<int>>& rankings,int candidates)
{
    vector<int> scores(candidates, 0); // массив очков кандидатов

    for (const auto& rank : rankings) { // проходим по каждому голосу избирателя

        for (int pos = 0; pos < rank.size(); pos++) { // позиции кандидатов

            int candidate = rank[pos];

            scores[candidate] += (candidates - 1 - pos); // чем выше место, тем больше очков
        }
    }
    return scores;
}

// парное сравнение кандидатов для Кондорсе
bool wins(
    const vector<vector<int>>& rankings,
    int a,
    int b)
{
    int winsA = 0; // победы A,B
    int winsB = 0;

    for (const auto& rank : rankings) {

        int posA = find(rank.begin(), rank.end(), a) - rank.begin(); // позиция A в рейтинге

        int posB = find(rank.begin(), rank.end(), b) - rank.begin(); // позиция B

        if (posA < posB) // кто выше в списке — получает голос
            winsA++;
        else
            winsB++;
    }
    return winsA > winsB; // true если A победил B
}

// метод Кондорсе: кандидат должен победить всех остальных
int condorcetWinner( const vector<vector<int>>& rankings, int candidates)
{
    for (int c = 0; c < candidates; c++) {
        bool isWinner = true;

        for (int other = 0; other < candidates; other++) {

            if (c == other) // не сравниваем с самим собой
                continue;

            if (!wins(rankings, c, other)) { // если проиграл хотя бы одному
                isWinner = false;
                break;
            }
        }
        if (isWinner) // победил всех
            return c;
    }
    return -1; // победителя нет
}

void run( const vector<vector<int>>& rankings,const vector<string>& names,string title){
    int n = names.size();

    // вывод названия сценария
    cout << title << endl;

    //метод борда считаем очки кандидатов
    vector<int> scores = bordaCount(rankings, n);
    cout << "\nБаллы Борда:\n";

    // вывод очков каждого кандидата
    for (int i = 0; i < n; i++) {

        cout << names[i] << ": "<< scores[i]<< endl;
    }
    //  поиск кандидата с максимальным количеством очков
    int bordaWinner = max_element(scores.begin(), scores.end()) - scores.begin();

    cout << "\nПобедитель Борда: " << names[bordaWinner] << endl;

    int condWinner = condorcetWinner(rankings, n); // поиск победителя Кондорсе

    if (condWinner != -1) // если победитель найден
        cout << "Победитель Кондорсе:" << names[condWinner]<<  "\n"<< endl;

    else // если победителя нет
        cout << "Кондорсе: не определён (парадокс Кондорсе)\n" << endl;
}
int main() {

    vector<string> names = {"A", "B", "C"};

// сценарий 1
    vector<vector<int>> test1 = {
        {0,1,2},
        {0,1,2},
        {0,2,1},
        {1,0,2},
        {0,2,1}
    };

// сценарий 2
vector<vector<int>> test2 = {
    {0,1,2},
    {0,1,2},
    {0,1,2},
    {0,1,2},
    {0,1,2},

    {1,2,0},
    {1,2,0},
    {1,2,0},
    {1,2,0},
    {1,2,0},
    {1,2,0},

    {2,0,1},
    {2,0,1},
    {2,0,1},
    {2,0,1}
};
    run(test1, names, "Сценарий 1");
    run(test2, names, "Сценарий 2");
    return 0;
}
