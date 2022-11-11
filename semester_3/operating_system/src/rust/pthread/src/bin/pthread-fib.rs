/*
 * pthread/src/bin/pthread-fib.rs --
 *
 *	A simple program to compute numbers: ./pthread-fib $(seq 0 12)
 */

use std::env;
use std::process;
use std::thread;

fn fib(n: u64) -> u64 {
    if n > 1 {
        let h1 = thread::spawn(move || fib(n - 1));
        let h2 = thread::spawn(move || fib(n - 2));
        h1.join().unwrap() + h2.join().unwrap()
    } else {
        n
    }
}

fn main() {
    let mut code: i32 = 0;
    for arg in env::args().skip(1) {
        let n = match arg.parse::<u64>() {
            Ok(num) => num,
            Err(_) => {
                println!("argument '{}' must be a positive integer", arg);
                code = 1;
                continue;
            }
        };
        println!("{}\t{}", arg, fib(n));
    }
    process::exit(code);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_fib() {
        assert_eq!(fib(0), 0);
        assert_eq!(fib(1), 1);
        assert_eq!(fib(10), 55);
    }
}
