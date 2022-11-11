/*
 * pthread/src/bin/pthread-mutex.rs --
 *
 *      A simple demonstration of mutexes in Rust. This example lacks
 *      error handling code to keep it short.
 */

use std::env;
use std::sync::{Arc, Mutex};
use std::thread;

fn work(arc: Arc<Mutex<u64>>) {
    let mut c = arc.lock().unwrap();
    *c += 1;
}

fn main() {
    let counter = Mutex::new(0);
    let arc = Arc::new(counter);

    let mut vec = Vec::new();
    for _ in env::args().skip(1) {
        let a = arc.clone();
        vec.push(thread::spawn(move || work(a)));
    }

    for handle in vec {
        handle.join().unwrap();
    }
}
