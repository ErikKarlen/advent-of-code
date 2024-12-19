use std::collections::HashMap;


fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let mut stones_counts: HashMap<usize, usize> = input_string
        .split(" ")
        .map(|s| (s.parse::<usize>().unwrap(), 1))
        .collect();

    let num_blinks = 25;

    for _blink in 0..num_blinks
    {
        let mut new_stones_counts: HashMap<usize, usize> = HashMap::new();
        stones_counts
            .iter()
            .for_each(|(&stone, &count)| {
                if stone == 0 as usize {
                    *new_stones_counts.entry(1).or_insert(0) += count;
                } else if stone.to_string().len() % 2 == 0 {
                    let stone_str = stone.to_string();
                    let left: usize = stone_str[0..stone_str.len()/2].parse::<usize>().unwrap();
                    let right: usize = stone_str[stone_str.len()/2..stone_str.len()].parse::<usize>().unwrap();
                    //dbg!(left);
                    //dbg!(right);
                    *new_stones_counts.entry(left).or_insert(0) += count;
                    *new_stones_counts.entry(right).or_insert(0) += count;
                } else {
                    *new_stones_counts.entry(stone * 2024 as usize).or_insert(0) += count;
                }
            });
        stones_counts = new_stones_counts;
    }

    let num_stones: usize = stones_counts
        .iter()
        .map(|(&_stone, &count)| count)
        .sum();

    println!("After blinking a total of {num_blinks} times we will have {num_stones} stones.")
}
