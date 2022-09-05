package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type comparable interface {
	int | int8 | int16 | int32 | int64 |
		uint | uint8 | uint16 | uint32 | uint64 |
		float32 | float64
}

func Max[T comparable](x, y T) T {
	return T(math.Max(float64(x), float64(y)))
}
func Min[T comparable](x, y T) T {
	return T(math.Min(float64(x), float64(y)))
}

type pair[T comparable] struct {
	First  T
	Second T
}

func main() {
	r := bufio.NewReader(os.Stdin)
	tc := ReadInt(r)

	pairs := []pair[int]{{1, 1}, {1, 2}, {2, 1}, {1, 3}, {3, 1}}
	for ; tc > 0; tc -= 1 {
		n := ReadInt(r)
		ans := 0
		for _, pair := range pairs {
			ans += Min(n/pair.First, n/pair.Second)
		}
		fmt.Println(ans)
	}
}

func ReadInt(r *bufio.Reader) int {
	nStr, _ := r.ReadString('\n')
	nStr = strings.ReplaceAll(nStr, "\r", "")
	nStr = strings.ReplaceAll(nStr, "\n", "")
	n, _ := strconv.Atoi(nStr)
	return n
}

func ReadLineNumbs(r *bufio.Reader) []string {
	line, _ := r.ReadString('\n')
	line = strings.ReplaceAll(line, "\r", "")
	line = strings.ReplaceAll(line, "\n", "")
	numbs := strings.Split(line, " ")
	return numbs
}

func ReadArrInt(r *bufio.Reader) []int {
	numbs := ReadLineNumbs(r)
	arr := make([]int, len(numbs))
	for i, n := range numbs {
		val, _ := strconv.Atoi(n)
		arr[i] = val
	}
	return arr
}

func ReadArrInt64(r *bufio.Reader) []int64 {
	numbs := ReadLineNumbs(r)
	arr := make([]int64, len(numbs))
	for i, n := range numbs {
		val, _ := strconv.ParseInt(n, 10, 64)
		arr[i] = val
	}
	return arr
}
