//! A multi-threaded program to echo command line arguments.

use std::env;
use std::thread;

fn work(arg: String) {
    print!("{} ", arg);
}

fn main() {
    let mut vec = Vec::new();

    for arg in env::args().skip(1) {
        let handle = thread::spawn(move || {
            work(arg);
        });
        vec.push(handle);
    }

    for handle in vec {
        handle.join().unwrap();
    }
    println!();
}
