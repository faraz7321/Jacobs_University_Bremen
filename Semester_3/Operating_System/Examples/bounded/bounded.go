/*
 * bounded/bounded.go --
 *
 *      Bounded buffer (producer / consumer) problem solution using
 *      go channels. Well, a go channel in fact is a bounded buffer.
 *      Anyway, this code is in analogy to the C version and it
 *      primarily serves to demonstrate how channels can be used to
 *      avoid the usage of explicit synchronization primitives.
 */

package main

import (
	"flag"
	"fmt"
)

const (
	size = 12
)

var nc = flag.Int("c", 1, "number of consumers")
var np = flag.Int("p", 1, "number of producers")
var ve = flag.Bool("v", false, "verbose output")

func producer(b chan int, g <-chan int, n chan<- bool) {
	for {
		v := <-g
		b <- v
		n <- true
	}
}

func consumer(b chan int, d chan<- int, r <-chan bool) {
	for {
		<-r
		v := <-b
		d <- v
	}
}

func generator() (<-chan int, chan<- bool) {
	s := make(chan int)
	n := make(chan bool)
	cnt := 0
	go func() {
		for {
			cnt++
			s <- cnt
			<-n
		}
	}()
	return s, n
}

func discarder() (chan<- int, <-chan bool) {
	d := make(chan int)
	r := make(chan bool)
	cnt := 0
	go func() {
		for {
			r <- true
			v := <-d
			cnt++
			if *ve {
				fmt.Printf(".")
			}
			if cnt != v {
				panic(fmt.Sprintf("unexpected number %d (expected %d)", v, cnt))
			}
		}
	}()
	return d, r
}

func run(nc int, np int) {
	b := make(chan int, size) // bounded buffer
	g, n := generator()       // lock-step generator
	d, r := discarder()       // lock-step discarder
	for i := 0; i < np; i++ {
		go producer(b, g, n)
	}
	for i := 0; i < nc; i++ {
		go consumer(b, d, r)
	}
}

func main() {
	flag.Parse()
	run(*nc, *np)
	<-make(chan struct{}) // block on a channel that never delivers
}
