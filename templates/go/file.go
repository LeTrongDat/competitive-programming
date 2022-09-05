package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type float = float32
type double = float64
type long = int64
type ulong = uint64

type comparable interface {
	int | int8 | int16 | int32 | int64 |
		uint | uint8 | uint16 | uint32 | uint64 |
		float32 | float64
}

type pair[T comparable] struct {
	First  T
	Second T
}

func Max[T comparable](x, y T) T {
	return T(math.Max(float64(x), float64(y)))
}

func Min[T comparable](x, y T) T {
	return T(math.Min(float64(x), float64(y)))
}

var in = bufio.NewReader(os.Stdin)

func _scln() string {
	ln, _ := in.ReadString('\n')
	return strings.Trim(ln, " \r\n")
}
func _sc(s []string) string {
	if len(s) == 0 {
		return _scln()
	}
	return s[0]
}
func readLine() string              { return _scln() }
func readString() string            { return _scln() }
func readStrings() []string         { return strings.Split(_scln(), " ") }
func readBool(s ...string) bool     { t, _ := strconv.ParseBool(_sc(s)); return t }
func readByte(s ...string) byte     { t, _ := strconv.ParseUint(_sc(s), 10, 8); return byte(t) }
func readDouble(s ...string) double { t, _ := strconv.ParseFloat(_sc(s), 64); return t }
func readFloat(s ...string) float   { t, _ := strconv.ParseFloat(_sc(s), 32); return float(t) }
func readInt(s ...string) int       { t, _ := strconv.Atoi(_sc(s)); return t }
func readLong(s ...string) long     { t, _ := strconv.ParseInt(_sc(s), 10, 64); return t }
func readULong(s ...string) ulong   { t, _ := strconv.ParseUint(_sc(s), 10, 64); return t }

func read[T comparable](reader func(...string) T) []T {
	strs := readStrings()
	arr := make([]T, len(strs))
	for i, val := range strs {
		arr[i] = reader(val)
	}
	return arr
}

func write(arg ...interface{})                 { fmt.Print(arg...) }
func writeLn(arg ...interface{})               { fmt.Println(arg...) }
func writeFormat(f string, arg ...interface{}) { fmt.Printf(f, arg...) }

func solve() {

}
func main() {
	tc := read(readInt)[0]
	for ; tc > 0; tc -= 1 {
		solve()
	}
}
