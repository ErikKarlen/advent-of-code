use std::collections::{HashMap, HashSet};


fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let mut total_score = 0;

    let input_width: i32 = input_string.find("\n").unwrap() as i32;
    let input_height: i32 = input_string.len() as i32 / input_width;

    let mut height_to_pos: HashMap<i32, HashSet<(i32, i32)>> = HashMap::new();

    let topographic_map: Vec<Vec<i32>> = input_string
        .split("\n")
        .enumerate()
        .map(|(row, line)| {
            let topographic_row: Vec<i32> = line
                .chars()
                .enumerate()
                .map(|(col, c)| -> i32 {
                    if !c.is_numeric() {
                        return -2;
                    }
                    let height = c as i32 - '0' as i32;
                    height_to_pos
                        .entry(height)
                        .or_insert_with(HashSet::new)
                        .insert((col as i32, row as i32));
                    height
                })
                .collect();
            topographic_row
        })
        .collect();

    let trailheads : Vec<(i32, i32)> = Vec::from_iter(height_to_pos[&0].clone());
    let dirs = vec![(0, -1), (1, 0), (0, 1), (-1, 0)];

    for trailhead in trailheads
    {
        let mut pos_to_check = vec![trailhead];
        let mut trailends: HashSet<(i32, i32)> = HashSet::new();
        while !pos_to_check.is_empty()
        {
            let curr_pos = pos_to_check.pop().unwrap();
            let curr_height = topographic_map[curr_pos.1 as usize][curr_pos.0 as usize];
            if curr_height == 9 {
                trailends.insert(curr_pos);
                continue;
            }
            //dbg!(curr_pos);
            for dir in &dirs
            {
                let next_pos = (curr_pos.0 + dir.0, curr_pos.1 + dir.1);
                //dbg!(next_pos);
                if 0 <= next_pos.0 && next_pos.0 < input_width && 0 <= next_pos.1 && next_pos.1 < input_height
                {
                    let next_height = topographic_map[next_pos.1 as usize][next_pos.0 as usize];
                    if next_height == curr_height + 1
                    {
                        pos_to_check.push(next_pos);
                    }
                }
            }
        }
        total_score += trailends.len();
    }

    println!("The sum of the scores of all trailheads on the topographic map is {total_score}.");
}
