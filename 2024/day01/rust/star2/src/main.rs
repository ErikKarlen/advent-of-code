use std::collections::HashMap;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let mut left_counts: HashMap<u32, u32> = HashMap::new();
    let mut right_counts: HashMap<u32, u32> = HashMap::new();

    for line in std::fs::read_to_string(input_file).unwrap().lines() {
        let nums: Vec<u32> = line.split("   ").map(|x| x.parse::<u32>().unwrap()).collect();
        *left_counts.entry(nums[0]).or_insert(0) += 1;
        *right_counts.entry(nums[1]).or_insert(0) += 1;
    }

    // dbg!(&left_counts);
    // dbg!(&right_counts);

    let similarity_score: u32 = left_counts
        .iter()
        .filter_map(|(lk, lv)| { right_counts.get(lk).map(|&rv| lk * lv * rv) })
        .sum();

    println!("The similarity score between the lists is {similarity_score}.");
}