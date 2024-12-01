fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let mut left_list: Vec<i32> = Vec::new();
    let mut right_list: Vec<i32> = Vec::new();

    for line in std::fs::read_to_string(input_file).unwrap().lines() {
        let nums: Vec<i32> = line.split("   ").map(|x| x.parse::<i32>().unwrap()).collect();
        left_list.push(nums[0]);
        right_list.push(nums[1]);
    }

    left_list.sort();
    right_list.sort();

    let total_distance: i32 = left_list
        .iter()
        .zip(right_list)
        .map(|(left_id, right_id)| (left_id - right_id).abs())
        .sum();

    println!("The total distance between the lists is {total_distance}.");
}