package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
	"unicode"
)

var digitWords = []string{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" }

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
		line := scanner.Text()
		// fmt.Println(line)

		buffer := ""

		var firstDigit int
		var secondDigit int

		runeLine := []rune(line)

		// fmt.Println("Forwards!")

		outForwards:
		for i := 0; i < len(runeLine); i++ {
			r := runeLine[i]

			if unicode.IsDigit(r) {
				firstDigit, _ = strconv.Atoi(string(r))
				// fmt.Println(fmt.Sprint(firstDigit))
				break
			} else {
				buffer += string(r)
				// fmt.Print(buffer + " -> [")
				for i := 0; i < len(buffer); i++ {
					s := buffer[i:]
					// fmt.Print(s + ", ")
					if slices.Contains(digitWords, s) {
						// fmt.Println("]")
						// fmt.Println("Found a word: " + s)
						firstDigit = DigitWordToInt(s)
						break outForwards
					}
				}
				// fmt.Println("]")
			}
		}

		buffer = ""

		// fmt.Println("Backwards!")

		outBackwards:
		for i := len(runeLine) - 1; i >= 0; i-- {
			r := runeLine[i]

			if unicode.IsDigit(r) {
				secondDigit, _ = strconv.Atoi(string(r))
				// fmt.Println(fmt.Sprint(secondDigit))
				break
			} else {
				buffer = string(r) + buffer
				// fmt.Print(buffer + " -> [")
				for i := 0; i < len(buffer); i++ {
					s := buffer[:len(buffer) - i]
					// fmt.Print(s + ", ")
					if slices.Contains(digitWords, s) {
						// fmt.Println("]")
						// fmt.Println("Found a word: " + s)
						secondDigit = DigitWordToInt(s)
						break outBackwards
					}
				}
				// fmt.Println("]")
			}
		}

		// fmt.Println(fmt.Sprint(firstDigit) + ", " + fmt.Sprint(secondDigit))
		value := firstDigit * 10 + secondDigit
		sum += value
		fmt.Println(value)
		// fmt.Println("--------------------")
	}

	fmt.Println("\nSum: " + fmt.Sprint(sum))
}

// func GetAllSubstrings(s string) []string {
// 	substrings := []string{}

// 	if s != "" {
// 		for i := 0; i < len(s); i++ {
// 			substrings += s[]
// 		}
// 	}

// 	return substrings
// }

func DigitWordToInt(s string) int {
	for index, word := range digitWords {
        if word == s {
            return index
        }
    }
	return -1
}
