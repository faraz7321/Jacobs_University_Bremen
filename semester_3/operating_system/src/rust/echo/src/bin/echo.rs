//! An minimal program to echo command line arguments.

use std::env;

fn main() {
    for arg in env::args().skip(1) {
        print!("{} ", arg);
    }
    println!();
}
