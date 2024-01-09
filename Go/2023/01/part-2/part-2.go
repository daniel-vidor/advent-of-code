package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
	"unicode"
)

var digitWords = []string{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}

// Day 1: Trebuchet?!

// On each line, the calibration value can be found by combining the first
// digit and the last digit (in that order) to form a single two-digit number.
// What is the sum of all of the calibration values?
func main() {
	file, err := os.Open("..\\input.txt")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	sum := 0
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		var firstDigit int
		var secondDigit int
		buffer := ""
		line := scanner.Text()
		runeLine := []rune(line)

		// Parse from left-to-right until we match something
	forwards:
		for i := 0; i < len(runeLine); i++ {
			r := runeLine[i]

			if unicode.IsDigit(r) {
				firstDigit, _ = strconv.Atoi(string(r))
				break
			} else {
				buffer = buffer + string(r) // append to buffer
				for i := 0; i < len(buffer); i++ {
					s := buffer[i:]
					if slices.Contains(digitWords, s) {
						firstDigit = DigitWordToInt(s)
						break forwards
					}
				}
			}
		}

		buffer = ""

		// Parse from right-to-left until we match something
	backwards:
		for i := len(runeLine) - 1; i >= 0; i-- {
			r := runeLine[i]

			if unicode.IsDigit(r) {
				secondDigit, _ = strconv.Atoi(string(r))
				break
			} else {
				buffer = string(r) + buffer // prepend to buffer
				for i := 0; i < len(buffer); i++ {
					s := buffer[:len(buffer)-i]
					if slices.Contains(digitWords, s) {
						secondDigit = DigitWordToInt(s)
						break backwards
					}
				}
			}
		}

		value := firstDigit*10 + secondDigit
		fmt.Println(fmt.Sprint(value) + " <- " + line)

		sum += value
	}

	fmt.Println("\nSum: " + fmt.Sprint(sum))
}

func DigitWordToInt(s string) int {
	for index, word := range digitWords {
		if word == s {
			return index
		}
	}
	return -1
}
