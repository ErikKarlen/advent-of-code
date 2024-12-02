fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let mut num_safe_reports: i32 = 0;

    for line in std::fs::read_to_string(input_file).unwrap().lines() {
        let report: Vec<i32> = line.split(" ").map(|x| x.parse::<i32>().unwrap()).collect();

        let levels_diffs = report
            .windows(2)
            .map(|w: &[i32]| w[1] - w[0])
            .collect::<Vec<i32>>();

        let is_increasing_safe: bool = levels_diffs
            .iter()
            .all(|d: &i32| 1 <= *d && *d <= 3);

        let is_decreasing_safe: bool = levels_diffs
            .iter()
            .all(|d: &i32| -3 <= *d && *d <= -1);

        //dbg!(levels_diffs);
        //dbg!(is_increasing_safe);
        //dbg!(is_decreasing_safe);
        
        if is_decreasing_safe || is_increasing_safe {
            num_safe_reports += 1;
        }
    }

    println!("The total number of safe reports is {num_safe_reports}.");
}