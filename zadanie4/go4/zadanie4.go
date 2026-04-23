package main

import "fmt"

func main() {
	_, m, chisla := input()
	pavel, vika := playGame(chisla, m)
	if pavel > vika {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}

func input() (n int, m int, chisla []int) {
	fmt.Scan(&n, &m)
	chisla = make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&chisla[i])
	}
	return
}

func selectBestMove(pos, m, lastMove int, chisla []int) (bestK int, bestSum int64) {
	bestK = 1
	bestSum = -1 << 62
	currentSum := int64(0)
	for k := 1; k <= m && pos+k <= len(chisla); k++ {
		if k == lastMove {
			continue
		}
		currentSum += int64(chisla[pos+k-1])
		if currentSum > bestSum {
			bestSum = currentSum
			bestK = k
		}
	}
	return
}

func playGame(chisla []int, m int) (pavel, vika int64) {
	pos := 0
	lastMove := -1
	isPavel := true
	pavel, vika = 0, 0
	for pos < len(chisla) {
		bestK, bestSum := selectBestMove(pos, m, lastMove, chisla)
		if isPavel {
			pavel += bestSum
		} else {
			vika += bestSum
		}
		pos += bestK
		lastMove = bestK
		isPavel = !isPavel
	}
	return
}
