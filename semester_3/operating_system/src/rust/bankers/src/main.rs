use ndarray::prelude::*;
// use ndarray::{Zip,FoldWhile};
use std::fmt;

#[derive(Debug)]
struct Banker {
    total: Array1<i32>,
    max: Array2<i32>,
    alloc: Array2<i32>,
}

impl fmt::Display for Banker {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Banker {{ total: {}, max: {}, alloc: {} }}",
	       self.total, self.max, self.alloc)
    }
    
}

impl Banker {
    fn is_safe(self: &Banker) -> bool {
	
	let inuse = self.alloc.sum_axis(Axis(0));
	println!("inuse:\n{}", inuse);
	
	let avail = self.total - inuse;
	println!("avail:\n{}", avail);
	
	// let need = self.max - self.alloc;
	// println!("need:\n{}", need);
	
	true
    }

    fn is_dead(self: &Banker) -> bool {
	false
    }
}

fn main() {

    let s1 = Banker {
	total: array![6,8,10,12],
	max: array![
            [3,1,2,5],
            [3,2,5,7],
            [2,6,3,1],
            [5,4,9,2],
            [1,3,8,9],
	],
	alloc: array![
            [0,0,2,1],
	    [1,0,1,2],
            [1,2,1,1],
            [3,4,0,0],
            [0,0,4,2],
	],
    };

    println!("{}", s1);
    s1.is_safe();

    // for row in need.rows() {
    // 	println!("{} <= {} ?", row, avail);
    // 	let xx = Zip::from(&row).and(&avail).fold_while(0, |acc, &x, &y| {
    // 	    if x > y {
    // 		FoldWhile::Done(acc)
    // 	    } else {
    // 		FoldWhile::Continue(acc+1)
    // 	    }
    // 	}).into_inner();
    // 	println!("{}", xx);
    // }

    // need.remove_index(Axis(0), 0);
    // println!("{}", need);

}
