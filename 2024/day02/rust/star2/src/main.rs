fn is_safe(report: &Vec<i32>) -> bool {
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

    return is_increasing_safe || is_decreasing_safe;
}

fn main() {
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let mut num_safe_reports: i32 = 0;

    for line in std::fs::read_to_string(input_file)
        .unwrap()
        .lines()
    {
        let report: Vec<i32> = line
            .split(" ")
            .map(|x| x
                .parse::<i32>()
                .unwrap())
            .collect();

        if is_safe(&report)
        {
            num_safe_reports += 1;
            continue;
        }

        let possible_reports: Vec<Vec<i32>> = (0..report.len())
            .map(|index: usize| {
                let mut possible_report: Vec<i32> = report.clone();
                possible_report.remove(index);
                possible_report
            })
            .collect();

        //dbg!(&possible_reports);

        for possible_report  in possible_reports
        {
            if is_safe(&possible_report) {
                num_safe_reports += 1;
                break;
            }
        }
    }

    println!("The total number of safe reports when the Problem Dampener is used is {num_safe_reports}.");
}