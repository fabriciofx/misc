// compile with: go build -gcflags -m inline.go
package main

import "fmt"

func f1() int {
	return 1
}

func f2() int {
	return f1()
}

func main() {
	r := f2()
	fmt.Printf("%d\n", r)
}
