use std::collections::{HashMap, HashSet};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let width: i32 = input_string.find("\n").unwrap() as i32;

    let pos_to_plant: HashMap<(i32, i32), char> = input_string
        .chars()
        .filter(|c| c.to_string() != "\n")
        .enumerate()
        .map(|(i, plant)| {
            let row: i32 = i as i32 / width;
            let col: i32 = i as i32 % width;
            ((col, row), plant)
        })
        .collect();

    let mut total_price = 0;
    let dirs = vec![(0, -1), (1, 0), (0, 1), (-1, 0)];
    let mut visited: HashSet<(i32, i32)> = HashSet::new();

    for (pos, plant) in &pos_to_plant
    {
        if visited.contains(pos) {
            continue;
        }
        visited.insert(*pos);

        let mut region_area = 0;
        let mut region_fences: HashSet<((i32, i32), (i32, i32))> = HashSet::new(); // (pos, dir)
        let mut pos_to_check: Vec<(i32, i32)> = vec![*pos];

        while !pos_to_check.is_empty()
        {
            let curr_pos = pos_to_check.pop().unwrap();
            region_area += 1;
            for dir in &dirs
            {
                let neighbour = (curr_pos.0 + dir.0, curr_pos.1 + dir.1);
                if !pos_to_plant.contains_key(&neighbour) || pos_to_plant[&neighbour] != *plant {
                    region_fences.insert((curr_pos, *dir));
                    continue;
                }
                if visited.contains(&neighbour) {
                    continue;
                }
                pos_to_check.push(neighbour);
                visited.insert(neighbour);
                //dbg!(&pos_to_check);
            }
        }

        let mut region_sides = 0;
        let mut sides_parts: HashSet<((i32, i32),(i32, i32))> = HashSet::new();
        for fence in &region_fences
        {
            if sides_parts.contains(&fence) {
                continue;
            }
            region_sides += 1;
            sides_parts.insert(*fence);

            let (pos, dir) = fence;
            let mut up = (pos.0, pos.1 - 1);
            let mut down = (pos.0, pos.1 + 1);
            let mut left = (pos.0 - 1, pos.1);
            let mut right = (pos.0 + 1, pos.1);

            // Add fences connected to fence to the side
            if dir.0 == 0 {
                while region_fences.contains(&(left, *dir)) {
                    sides_parts.insert((left, *dir));
                    left = (left.0 - 1, left.1);
                }
                while region_fences.contains(&(right, *dir)) {
                    sides_parts.insert((right, *dir));
                    right = (right.0 + 1, right.1);
                }
            }
            if dir.1 == 0 {
                while region_fences.contains(&(up, *dir)) {
                    sides_parts.insert((up, *dir));
                    up = (up.0, up.1 - 1);
                }
                while region_fences.contains(&(down, *dir)) {
                    sides_parts.insert((down, *dir));
                    down = (down.0, down.1 + 1);
                }
            }
        }

        //dbg!(plant);
        //dbg!(region_sides);
        total_price += region_sides * region_area;
    }

    println!("The new total price of fencing all regions on the map is {total_price}.");
}
