/*
 * pthread/src/bin/pthread-cond.rs --
 *
 *      A simple demonstration of condition variables in Rust. This
 *      example lacks error handling code to keep it short.
 */

use std::env;
use std::sync::{Arc, Condvar, Mutex};
use std::thread;

struct Counter {
    mutex: Mutex<u64>,
    cvar: Condvar,
}

fn even(arc: Arc<Counter>) {
    let mut ctr = arc
        .cvar
        .wait_while(arc.mutex.lock().unwrap(), |c| *c % 2 != 0)
        .unwrap();
    eprintln!("even: {}", *ctr);
    *ctr += 1;
    arc.cvar.notify_all();
}

fn odd(arc: Arc<Counter>) {
    let mut ctr = arc
        .cvar
        .wait_while(arc.mutex.lock().unwrap(), |c| *c % 2 == 0)
        .unwrap();
    eprintln!("odd:  {}", *ctr);
    *ctr += 1;
    arc.cvar.notify_all();
}

fn main() {
    let ctr = Counter {
        mutex: Mutex::new(0),
        cvar: Condvar::new(),
    };
    let data = Arc::new(ctr);

    let mut vec = Vec::new();
    for _ in env::args().skip(1) {
        let c = data.clone();
        vec.push(thread::spawn(move || even(c)));
        let c = data.clone();
        vec.push(thread::spawn(move || odd(c)));
    }

    for handle in vec {
        handle.join().unwrap();
    }
}
