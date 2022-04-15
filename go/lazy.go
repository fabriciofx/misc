package main

import "fmt"

type interface Text {
	AsString() string
}

type struct LoweredText {
	text string
}

func NewLoweredText(txt string) LoweredText {
	return LoweredText{
		text: func(t string) string {
			return "abc"
		}
	}
}

func main() {

}
