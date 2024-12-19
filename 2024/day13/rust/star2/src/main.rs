fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let re = regex::Regex::new(r"Button A: X\+(\d+), Y\+(\d+)\nButton B: X\+(\d+), Y\+(\d+)\nPrize: X=(\d+), Y=(\d+)")
        .unwrap();

    let min_tokens: u64 = re
        .captures_iter(&input_string)
        .map(|cap| {
            let a1 = cap[1].parse::<f64>().unwrap();
            let a2 = cap[2].parse::<f64>().unwrap();
            let b1 = cap[3].parse::<f64>().unwrap();
            let b2 = cap[4].parse::<f64>().unwrap();
            let c1 = cap[5].parse::<f64>().unwrap() + 10000000000000.0;
            let c2 = cap[6].parse::<f64>().unwrap() + 10000000000000.0;
            // Solve linear equation system:
            // { a1*a + a2*a = c1
            // { b1*b + b2*b = c2
            let a: f64 = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
            let b: f64 = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
            //dbg!(&a);
            //dbg!(&b);
            let p: f64 = 3.0 * a + b;
            if p.fract() == 0.0 {
                return p as u64;
            }
            0
        })
        .sum();

    println!("The fewest number of tokens we would have to spend to win all possible prizes is {min_tokens}.");
}
