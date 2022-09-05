package main

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"
)

type Reader bufio.Reader

func main() {
	fmt.Println("Hello world")
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

