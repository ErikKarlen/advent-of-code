fn main()
{
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let re = regex::Regex::new(r"mul\((\d+),(\d+)\)")
        .unwrap();

    let multiplication_sum: u32 = re.captures_iter(&input_string)
        .map(|cap| {
            let num1 = cap[1].parse::<u32>().unwrap();
            let num2 = cap[2].parse::<u32>().unwrap();
            num1 * num2
        })
        .sum();

    //dbg!(input_string);

    println!("If you add up all of the results of the multiplications you get {multiplication_sum}.");
}
