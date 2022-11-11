//! An implementation of a very minimal shell

use std::io::{self, Write};
use std::process;

fn show_prompt() {
    print!("msh > ");
    io::stdout().flush().expect("msh: could not flush stdout");
}

fn run(line: &str) {
    let mut argv: Vec<&str> = line.split_whitespace().collect();
    if !argv.is_empty() {
        let prog = argv.remove(0);
        if let "exit" = prog {
            std::process::exit(0);
        } else {
            let mut cmd = process::Command::new(prog);
            match cmd.args(argv).spawn() {
                Ok(mut child) => {
                    child.wait().expect("msh: child wasn't running");
                }
                Err(e) => {
                    eprintln!("msh: {}", e);
                }
            }
        }
    }
}

fn main() {
    loop {
        let mut input = String::new();
        show_prompt();
        match io::stdin().read_line(&mut input) {
            Ok(0) => {
                println!();
                break;
            }
            Ok(_) => run(input.trim()),
            Err(error) => eprintln!("msh: {}", error),
        }
    }
}
