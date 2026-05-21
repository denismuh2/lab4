package main

import (
	"fmt"
	"math"
)

const EPS = 1e-4 // точность вычислений 0.0001
const MAX_ITER = 100 // максимальное количество итераций

// исходная функция f(x) = 2ln(x) - 0.5x + 1
func f(x float64) float64 {
	return 2*math.Log(x) - 0.5*x + 1
}

// производная исходной для метода Ньютона
func df(x float64) float64 {
	return 2.0/x - 0.5
}

// функция Ф(x) для метода простых итераций, Ф(x) = 4ln(x) + 2
func phi(x float64) float64 {
	return 4*math.Log(x) + 2
}

// метод половинного деления
func bisection(a float64, b float64) {

	fmt.Println("\n=== Метод половинного деления ===\n")

	fmt.Printf("%5s%15s%15s%15s\n",
		"n", "a", "b", "b-a")

	n := 0

	for (b-a) > EPS && n < MAX_ITER {

		c := (a + b) / 2.0 // середина текущего отрезка

		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, a, b, (b - a))

		if f(a)*f(c) <= 0 { // смена знака, значит корень лежит между a и c
			b = c
		} else {
			a = c
		}
		n++
	}

	root := (a + b) / 2.0 //Приближённый корень = середина последнего отрезка

	fmt.Printf("Корень: %.6f\n", root)
	fmt.Println("Итераций:", n)
}

//метод Ньютона, ищет касательную к графику, формула: x(n+1) = x(n) - f(x)/f'(x)
func newton(x0 float64) {

	fmt.Println("\n=== Метод Ньютона, x - f(x) / df(x) ===\n")

	fmt.Printf("%5s%15s%15s%15s\n",
		"n", "x_n", "x_n+1", "|dx|")

	x := x0 // x = текущее приближение
	n := 0
	var delta float64 // разница между приближениями

	for {
		x_new := x - f(x)/df(x) // формула Ньютона
		delta = math.Abs(x_new - x)

		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, x, x_new, delta)

		x = x_new // след приблежение
		n++

		if !(delta > EPS && n < MAX_ITER) {
			break
		}
	}

	fmt.Printf("Корень: %.6f\n", x)
	fmt.Println("Итераций:", n)
}

//метод простых итераций, формула: x(n+1) = Ф(x(n)), моя: Ф(x) = 4ln(x) + 2
func simple_iteration(x0 float64) {

	fmt.Println("\n=== Метод простых итераций, x(n+1) = Ф(x(n)), Ф(x) = 4ln(x) + 2 ===\n")

	fmt.Printf("%5s%15s%15s%15s\n",
		"n", "x_n", "x_n+1", "|dx|")

	x := x0 // Начальное приближение
	n := 0
	var delta float64

	for {
		x_new := phi(x) // новое приближение
		delta = math.Abs(x_new - x)

		fmt.Printf("%5d%15.6f%15.6f%15.6f\n",
			n, x, x_new, delta)

		x = x_new //обновляем x
		n++

		if !(delta > EPS && n < MAX_ITER) {
			break
		}
	}

	fmt.Printf("Корень: %.6f\n", x)
	fmt.Println("Итераций:", n)
}

func main() {

	//1) f(0.5) < 0, f(1) > 0, значит корень есть на [0.5 ; 1]
	fmt.Println("Первый корень [0.5 ; 1]")

	bisection(0.5, 1.0) // Метод половинного деления
	newton(0.8)          // Для Ньютона и итераций задаём начальное приближение
	simple_iteration(0.8)

	//2) f(10) > 0, f(12) < 0, значит корень на [10 ; 12]
	fmt.Println("\n\nВторой корень [10 ; 12]")

	bisection(10.0, 12.0)
	newton(11.0) // начальное приближение
	simple_iteration(11.0)
}
