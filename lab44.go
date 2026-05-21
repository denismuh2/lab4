package main

import (
	"fmt"
)

// метод Борда, очки от 0 до n-1 кандидатов, избиратель составляет рейтинг
func bordaCount(rankings [][]int, candidates int) []int {
	scores := make([]int, candidates) // массив очков кандидатов

	for _, rank := range rankings { // проходим по каждому голосу избирателя

		for pos := 0; pos < len(rank); pos++ { // позиции кандидатов

			candidate := rank[pos]

			scores[candidate] += (candidates - 1 - pos) // чем выше место, тем больше очков
		}
	}
	return scores
}

// парное сравнение кандидатов для Кондорсе
func wins(
	rankings [][]int,
	a int,
	b int,
) bool {
	winsA := 0 // победы A,B
	winsB := 0

	for _, rank := range rankings {

		posA := -1
		for i, candidate := range rank { // позиция A в рейтинге
			if candidate == a {
				posA = i
				break
			}
		}

		posB := -1
		for i, candidate := range rank { // позиция B
			if candidate == b {
				posB = i
				break
			}
		}

		if posA < posB { // кто выше в списке — получает голос
			winsA++
		} else {
			winsB++
		}
	}
	return winsA > winsB // true если A победил B
}

// метод Кондорсе: кандидат должен победить всех остальных
func condorcetWinner(rankings [][]int, candidates int) int {
	for c := 0; c < candidates; c++ {
		isWinner := true

		for other := 0; other < candidates; other++ {

			if c == other { // не сравниваем с самим собой
				continue
			}

			if !wins(rankings, c, other) { // если проиграл хотя бы одному
				isWinner = false
				break
			}
		}
		if isWinner { // победил всех
			return c
		}
	}
	return -1 // победителя нет
}

func run(rankings [][]int, names []string, title string) {
	n := len(names)

	// вывод названия сценария
	fmt.Println(title)

	//метод борда считаем очки кандидатов
	scores := bordaCount(rankings, n)
	fmt.Println("\nБаллы Борда:")

	// вывод очков каждого кандидата
	for i := 0; i < n; i++ {

		fmt.Println(names[i] + ": " + fmt.Sprint(scores[i]))
	}

	//  поиск кандидата с максимальным количеством очков
	bordaWinner := 0
	for i := 1; i < len(scores); i++ {
		if scores[i] > scores[bordaWinner] {
			bordaWinner = i
		}
	}

	fmt.Println("\nПобедитель Борда:", names[bordaWinner])

	condWinner := condorcetWinner(rankings, n) // поиск победителя Кондорсе

	if condWinner != -1 { // если победитель найден
		fmt.Println("Победитель Кондорсе:", names[condWinner], "\n")
	} else { // если победителя нет
		fmt.Println("Кондорсе: не определён (парадокс Кондорсе)\n")
	}
}

func main() {

	names := []string{"A", "B", "C"}

	// сценарий 1
	test1 := [][]int{
		{0, 1, 2},
		{0, 1, 2},
		{0, 2, 1},
		{1, 0, 2},
		{0, 2, 1},
	}

	// сценарий 2
	test2 := [][]int{
		{0, 1, 2},
		{0, 1, 2},
		{0, 1, 2},
		{0, 1, 2},
		{0, 1, 2},

		{1, 2, 0},
		{1, 2, 0},
		{1, 2, 0},
		{1, 2, 0},
		{1, 2, 0},
		{1, 2, 0},

		{2, 0, 1},
		{2, 0, 1},
		{2, 0, 1},
		{2, 0, 1},
	}

	run(test1, names, "Сценарий 1")
	run(test2, names, "Сценарий 2")
}