//! An implementation of the pong game.

use pong::pong;

const FRAMES_PER_SECOND: u32 = 10;

fn main() {
    let mut toggle_autorefresh = true;
    let mut siv = cursive::default();
    siv.set_fps(FRAMES_PER_SECOND);
    siv.add_global_callback('q', |s| s.quit());
    siv.add_global_callback(' ', move |s| {
        toggle_autorefresh ^= true;
        s.set_autorefresh(toggle_autorefresh);
    });

    let mut pong = pong::Pong::default();
    pong.restart();
    siv.add_layer(pong);
    siv.run();
}
