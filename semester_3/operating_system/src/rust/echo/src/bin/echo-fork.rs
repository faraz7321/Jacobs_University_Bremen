//! A multi-process program to echo command line arguments.

use nix::sys::wait;
use nix::unistd;
use std::env;
use std::process;

fn work(arg: String) {
    print!("{} ", arg);
    process::exit(0);
}

fn main() {
    let mut vec = Vec::new();
    let mut status = 0;

    for arg in env::args().skip(1) {
        match unistd::fork() {
            Ok(unistd::ForkResult::Parent { child, .. }) => vec.push(child),
            Ok(unistd::ForkResult::Child) => work(arg),
            Err(msg) => {
                eprintln!("fork() failed: {}", msg);
                status = 1;
            }
        }
    }

    for child in vec {
        match wait::waitpid(child, None) {
            Ok(_) => (),
            Err(msg) => {
                eprintln!("waitpid() failed: {}", msg);
                status = 1;
            }
        }
    }
    println!();
    if status > 0 {
        process::exit(status);
    }
}
