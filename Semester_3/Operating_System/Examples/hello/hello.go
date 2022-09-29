/*
 * hello.go --
 *
 *	A go hello world program, which uses a goroutine and a
 *	channel to block the main function. Build an executable
 *	using 'go build hello.go'.
 */
 
package main

import "fmt"

func hello(d chan<- bool) {
	fmt.Println("hello world")
 	d <- true
}

func main() {
        d := make(chan bool)
	go hello(d)
        <- d // block on a channel that indicates that the hello() is done
}
