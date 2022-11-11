//! A hello world program using async futures.

use async_std::future;
use async_std::io;
use async_std::task::block_on;
use std::time::Duration;

/// Returns a future to print `Hello `.
///
/// Calling the async function `hello()` does not execute anything.
/// The function returns a future that when executed will print
/// `Hello ` to the standard output.
async fn hello() {
    print!("Hello ");
}

/// Returns a future to print `Hello {}!` where `{}` is replaced
/// by text read from the standard input.
async fn hello_world() {
    let stdin = io::stdin();
    let mut line = String::new();
    match stdin.read_line(&mut line).await {
        Err(m) => {
            eprintln!("{}", m)
        }
        Ok(_) => {
            let stripped = line
                .strip_suffix("\r\n")
                .or_else(|| line.strip_suffix('\n'))
                .unwrap_or(&line);
            hello().await;
            println!("{}!", stripped);
        }
    }
}

/// Execute a hello_world future or timeout after `sec` seconds.
async fn timed_hello_world(secs: u64) {
    let w = hello_world();
    let d = Duration::from_secs(secs);
    future::timeout(d, w).await.unwrap_or(());
}

/// Executes the future returned by `timed_hello_world` on the main
/// thread.
fn main() {
    let f = timed_hello_world(3);
    block_on(f);
}
