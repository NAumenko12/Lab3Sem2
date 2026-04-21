package main

import "fmt"

func main() {
	var a, b int
	fmt.Scan(&a, &b)
	if b == 1 {
		fmt.Println("infinity")
	} else {
		num, den := sum(a, b)
		fmt.Printf("%d/%d\n", num, den)
	}
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func euler(a int) []int64 {
	prev := []int64{1}
	for n := 2; n <= a; n++ {
		cur := make([]int64, n)
		cur[0] = 1
		cur[n-1] = 1
		for k := 1; k < n-1; k++ {
			cur[k] = int64(k+1)*prev[k] + int64(n-k)*prev[k-1]
		}
		prev = cur
	}
	return prev
}

func polyEval(coef []int64, b int) int64 {
	var res int64 = 0
	powB := int64(1)
	for k := 0; k < len(coef); k++ {
		res += coef[k] * powB
		powB *= int64(b)
	}
	return res
}

func denPow(b, a int) int64 {
	d := int64(1)
	for i := 0; i <= a; i++ {
		d *= int64(b - 1)
	}
	return d
}

func sum(a, b int) (int64, int64) {
	coeff := euler(a)
	poly := polyEval(coeff, b)
	num := int64(b) * poly
	den := denPow(b, a)
	g := gcd(num, den)
	return num / g, den / g
}
