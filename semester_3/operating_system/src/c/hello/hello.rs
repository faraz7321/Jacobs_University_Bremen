/*
 * hello.rs --
 *
 *	A rust hello world program, which uses a thread to print
 *	hello world. Build an executable using:
 *
 *	rustc -o hello -O hello.rs
 */
 
use std::thread;

fn main() {
    let w = "world";

    let handle = thread::spawn(move || {
        println!("Hello {}!", w);
    });

    handle.join().unwrap();
}
