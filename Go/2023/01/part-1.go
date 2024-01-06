package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

// Day 1: Trebuchet?!

// On each line, the calibration value can be found by combining the first
// digit and the last digit (in that order) to form a single two-digit number.
// What is the sum of all of the calibration values?
func main() {
	file, err := os.Open("input-example-part-1.txt")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	sum := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		fmt.Println(line)

		var firstDigit string
		var secondDigit string

		runeLine := []rune(line)

		for i := 0; i < len(runeLine); i++ {
			if unicode.IsDigit(runeLine[i]) {
				firstDigit = string(runeLine[i])
				break;
			}
		}

		for i := len(runeLine) - 1; i >= 0; i-- {
			if unicode.IsDigit(runeLine[i]) {
				secondDigit = string(runeLine[i])
				break;
			}
		}

		fmt.Println(firstDigit + ", " + secondDigit)
		valueString := string(firstDigit) + string(secondDigit)

		value, err := strconv.Atoi(valueString)
		if err != nil {
			fmt.Println(err)
		}
		sum += value
		fmt.Println(value)
	}

	fmt.Println(sum)
}
