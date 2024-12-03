fn main()
{
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let re_instructions = regex::Regex::new(r"mul\((\d+),(\d+)\)|do\(\)|don't\(\)")
        .unwrap();

    let multiplication_sum: i32 = re_instructions
        .captures_iter(&input_string)
        .scan(true, |last_was_do, cap| {
            if let Some(matched) = cap.get(0).map(|m| m.as_str()) {
                if matched == "do()" {
                    *last_was_do = true;
                } else if matched == "don't()" {
                    *last_was_do = false;
                } else if matched.starts_with("mul(") && *last_was_do {
                    if let (Some(num1), Some(num2)) = (cap.get(1), cap.get(2)) {
                        return Some(num1.as_str().parse::<i32>().unwrap() * num2.as_str().parse::<i32>().unwrap());
                    }
                }
            }
            Some(0)
        })
        .filter_map(|x| Some(x))
        .sum();

    println!("If you add up all of the results of just the enabled multiplications you get {multiplication_sum}.");
}
