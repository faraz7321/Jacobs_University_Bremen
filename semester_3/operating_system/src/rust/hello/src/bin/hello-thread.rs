/*
 * hello-thread.rs --
 *
 *      A rust hello world program, which uses a thread to print
 *      hello world. Build an executable using
 *
 *          cargo build
 *
 *      in the .../rust/hello directory.
 */

use std::thread;

fn main() {
    let w = "world";

    let handle = thread::spawn(move || {
        println!("Hello {}!", w);
    });

    handle.join().unwrap();
}
