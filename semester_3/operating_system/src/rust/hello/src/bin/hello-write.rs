use std::io::Write;

fn main() -> Result<(), std::io::Error> {
    let stdout = std::io::stdout();

    writeln!(&stdout, "Hello, world!")
}
