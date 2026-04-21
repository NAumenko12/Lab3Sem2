package main

import (
	"fmt"
	"math"
)

func main() {
	var xStart, xEnd, dx float64
	fmt.Print("Введите Xнач, Xкон и шаг dx: ")
	fmt.Scan(&xStart, &xEnd, &dx)
	fmt.Printf("|   x   |   f(x)   |\n")
	fmt.Println("-------------------")
	for x := xStart; x <= xEnd+dx/2; x += dx {
		y := f(x)
		fmt.Printf("| %6.2f | %8.2f |\n", x, y)
	}
}

func f(x float64) float64 {
	if x < -6 {
		return leftLine(x)
	} else if x <= -2 {
		return leftSemicircle(x)
	} else if x < 2 {
		return logFunction(x)
	} else if x <= 4 {
		return rightSemicircle(x)
	} else {
		return rightLine(x)
	}
}

func leftLine(x float64) float64 {
	return -2*x - 14
}

func leftSemicircle(x float64) float64 {
	return -4 + math.Sqrt(4-math.Pow(x+2, 2))
}

func logFunction(x float64) float64 {
	return math.Log2(x + 2)
}

func rightSemicircle(x float64) float64 {
	return math.Sqrt(1 - math.Pow(x-3, 2))
}

func rightLine(_ float64) float64 {
	return 0
}
