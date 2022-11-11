//! An implementation of the pong game with a textual user interface.
//!
//! The textual user interface uses the `Cursive` crate to control
//! the console.

use cursive::event::{Event, EventResult};
use cursive::view::View;
use cursive::Printer;
use cursive::Vec2;

const PAD_SIZE: usize = 5;
const PAD_OFFSET: usize = 8;
const BOARD_SIZE_X: usize = 80;
const BOARD_SIZE_Y: usize = 21;
const SCORE_OFFSET: usize = 4;

pub struct Pong {
    /// The position (x,y) of the ball.
    ball: Vec2,
    /// The position (x,y) of the left pad. The coordinates identify
    /// the top of the pad.
    padl: Vec2,
    /// The position (x,y) of the right pad. The coordinates identify
    /// the top of the pad.
    padr: Vec2,
    /// The change of the ball position in each update in the
    /// x-direction.
    ball_dx: i8,
    /// The change of the ball position in each update in the
    /// x-direction.
    ball_dy: i8,
    /// The score of the left player.
    scorel: u32,
    /// The score of the right player.
    scorer: u32,
}

macro_rules! pad_up {
    ($pad:expr) => {
        if $pad.y > 0 {
            $pad.y -= 1
        }
    };
}

macro_rules! pad_down {
    ($pad:expr) => {
        if $pad.y + PAD_SIZE < BOARD_SIZE_Y {
            $pad.y += 1
        }
    };
}

macro_rules! ball_hit_pad {
    ($ball:expr,$pad:expr) => {
        $ball.x == $pad.x && ($pad.y..$pad.y + PAD_SIZE).contains(&$ball.y)
    };
}

impl Pong {
    /// Creates a new `Pong`.
    ///
    /// A struct Pong captures the state of the pong game. The initial
    /// state positions the ball in the middle of the board and the
    /// ball is not moving.
    pub fn new() -> Self {
        Pong {
            ball: Vec2::new(BOARD_SIZE_X / 2, BOARD_SIZE_Y / 2),
            padl: Vec2::new(PAD_OFFSET, (BOARD_SIZE_Y - PAD_SIZE) / 2),
            padr: Vec2::new(BOARD_SIZE_X - PAD_OFFSET - 3, (BOARD_SIZE_Y - PAD_SIZE) / 2),
            ball_dx: 0,
            ball_dy: 0,
            scorel: 0,
            scorer: 0,
        }
    }

    /// Restart the game.
    ///
    /// The `restart` method positions the ball on a randomized
    /// position in the center of the board with a randomized
    /// direction.
    pub fn restart(&mut self) {
        self.ball = Vec2::new(BOARD_SIZE_X / 2, BOARD_SIZE_Y / 2);
        self.ball_dx = if rand::random() { 1 } else { -1 };
        self.ball_dy = if rand::random() { 1 } else { -1 };
        let r: i8 = rand::random();
        self.ball.y = (self.ball.y as i8 + r / 16) as usize;
    }

    /// True if the ball leaves the board on the left side.
    fn ball_out_left(&self) -> bool {
        self.ball.x == 0
    }

    /// True if the ball leaves the board on the right side.
    fn ball_out_right(&self) -> bool {
        self.ball.x == BOARD_SIZE_X - 1
    }

    /// True if the ball hits the ceiling.
    fn ball_hit_ceiling(&self) -> bool {
        self.ball.y == 0
    }

    /// True if the ball hits the floor.
    fn ball_hit_floor(&self) -> bool {
        self.ball.y == BOARD_SIZE_Y - 1
    }

    /// True if the ball hits the left pad.
    fn ball_hit_pad_left(&self) -> bool {
        ball_hit_pad!(self.ball, self.padl)
    }

    /// True if the ball hits the right pad.
    fn ball_hit_pad_right(&self) -> bool {
        ball_hit_pad!(self.ball, self.padr)
    }

    /// Update the state of the game.
    ///
    /// The following example shows that the game is played by simply
    /// calling `update()` in a loop.
    ///
    /// ```rust
    /// # use pong::pong::Pong;
    /// # fn main() {
    /// let mut pong = Pong::default();
    /// pong.restart();
    /// for _ in 1..1000 {
    ///     pong.update();
    /// }
    /// # assert!(pong.scores().0 + pong.scores().1 > 0);
    /// # }
    /// ```
    ///
    /// This loop does not allow us to see how the game proceeds and
    /// it does not allow to us to control the pads. Note that the
    /// game restarts automatically if the ball leaves the board.
    ///
    /// For viewing and controlling the game, we need to use a
    /// interface. This has been accomplished by implementing the
    /// `View` trait of the `Cursive` crate for textual user
    /// interfaces.
    pub fn update(&mut self) {
        if self.ball_out_left() {
            self.scorer += 1;
            self.restart();
            return;
        }

        if self.ball_out_right() {
            self.scorel += 1;
            self.restart();
            return;
        }

        if self.ball_hit_ceiling() || self.ball_hit_floor() {
            self.ball_dy *= -1;
        }
        if self.ball_hit_pad_left() || self.ball_hit_pad_right() {
            self.ball_dx *= -1;
        }

        self.ball.x = (self.ball.x as i8 + self.ball_dx) as usize;
        self.ball.y = (self.ball.y as i8 + self.ball_dy) as usize;
    }

    /// Returns the scores of the two players as a tuple.
    pub fn scores(&self) -> (u32, u32) {
        (self.scorel, self.scorer)
    }
}

impl Default for Pong {
    fn default() -> Self {
        Self::new()
    }
}

impl View for Pong {
    /// Return the required size of the board.
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        Vec2::new(BOARD_SIZE_X, BOARD_SIZE_Y)
    }

    /// Draw the state of the pong game.
    fn draw(&self, printer: &Printer) {
        printer.print_vline((BOARD_SIZE_X / 2, 0), BOARD_SIZE_Y, ":");

        let ml = format!("Score {}", self.scorel);
        let xl = SCORE_OFFSET;
        printer.print((xl, 1), &ml);

        let mr = format!("Score {}", self.scorer);
        let xr = BOARD_SIZE_X - SCORE_OFFSET - mr.chars().count() - 2;
        printer.print((xr, 1), &mr);

        printer.print_box(self.padl, (2, PAD_SIZE), false);
        printer.print_box(self.padr, (2, PAD_SIZE), false);
        printer.print(self.ball, "*");
    }

    // Handle events.
    fn on_event(&mut self, event: Event) -> EventResult {
        match event {
            Event::Char(c) => match c {
                'a' => pad_up!(self.padl),
                's' => pad_down!(self.padl),
                'k' => pad_up!(self.padr),
                'l' => pad_down!(self.padr),
                _ => (),
            },
            Event::Refresh => {
                self.update();
            }
            _ => (),
        }
        EventResult::Ignored
    }
}
