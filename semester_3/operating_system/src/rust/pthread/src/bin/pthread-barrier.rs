/*
 * pthread/src/bin/pthread-barrier.rs --
 *
 *      A simple demonstration of barriers in Rust. This example lacks
 *      error handling code to keep it short.
 */

use std::env;
use std::sync::{Arc, Barrier};
use std::thread;

fn work(me: &str, opening: Arc<Barrier>, closing: Arc<Barrier>) {
    println!("arriving {}", me);
    opening.wait();
    println!("working {}", me);
    closing.wait();
    println!("leaving {}", me);
}

fn main() {
    let mut vec = Vec::new();
    let argc = env::args().len() - 1;
    let opening = Arc::new(Barrier::new(argc));
    let closing = Arc::new(Barrier::new(argc));

    for arg in env::args().skip(1) {
        let o = Arc::clone(&opening);
        let c = Arc::clone(&closing);
        vec.push(thread::spawn(move || work(&arg, o, c)));
    }

    for handle in vec {
        handle.join().unwrap();
    }
}
