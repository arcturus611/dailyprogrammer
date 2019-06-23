use std::io;
use std::cmp::Ordering;

fn main(){
 	let mut user_input_str = String::new();
 	io::stdin().read_line(&mut user_input_str)
 		.expect("Failed to read input"); 
 	let user_input_int = user_input_str
 		.split_whitespace()
 		.map(|x| x.parse::<i128>())
 		.collect::<Result<Vec<i128>, _>>()
 		.unwrap();
 	assert!(user_input_int.len()==4);
 	let room_x = user_input_int[0];
 	let room_y = user_input_int[1];
 	let box_x = user_input_int[2];
 	let box_y = user_input_int[3];
	
	println!("The user input is {}, {}, {}, {}", room_x, room_y, box_x, box_y);
	println!("The number of crates using FIT1 is {}", fit1(room_x, room_y, box_x, box_y));
	println!("The number of creates using FIT2 is {}", fit2(room_x, room_y, box_x, box_y));
}

fn fit1(a: i128, b: i128, x:i128, y:i128)->i128{
	return (a/x)*(b/y)
}

fn fit2(a: i128, b:i128, x:i128, y:i128)->i128{
	let fit1_xy = fit1(a, b, x, y);
	let fit1_yx = fit1(a, b, y, x);
	match fit1_xy.cmp(&fit1_yx){
		Ordering::Less => return fit1_yx,
		Ordering::Greater => return fit1_xy,
		Ordering::Equal => return fit1_xy
	}
}
