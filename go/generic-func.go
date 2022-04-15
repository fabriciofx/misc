package main

import "fmt"

type Func[X, Y any] func(x X) Y

type Set[X, Y any] interface {
	Fn(apply Func[X, Y]) Set[X, Y]
	Print()
}

type Numbers struct {
	values []int
}

func NewNumbers(values ...int) Set[int, bool] {
	return &Numbers{values: append([]int{}, values...)}
}

func IsEven(n int) bool {
	if n%2 == 0 {
		return true
	}
	return false
}

func (ns *Numbers) Fn(apply Func[int, bool]) Set[int, bool] {
	var evens []int
	for _, v := range ns.values {
		if apply(v) {
			evens = append(evens, v)
		}
	}
	return NewNumbers(evens...)
}

func (ns *Numbers) Print() {
	fmt.Printf("%v", ns.values)
}

func main() {
	a := NewNumbers(1, 2, 3, 4, 5, 6)
	r := a.Fn(IsEven)
	r.Print() // deve mostrar 2, 4 e 6
}

