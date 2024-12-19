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

        let mut region_perimeter = 0;
        let mut region_area = 0;
        let mut pos_to_check: Vec<(i32, i32)> = vec![*pos];

        while !pos_to_check.is_empty()
        {
            let curr_pos = pos_to_check.pop().unwrap();
            //dbg!(curr_pos);
            region_area += 1;
            for dir in &dirs
            {
                let neighbour = (curr_pos.0 + dir.0, curr_pos.1 + dir.1);
                if !pos_to_plant.contains_key(&neighbour) || pos_to_plant[&neighbour] != *plant {
                    region_perimeter += 1;
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

        //dbg!(plant);
        //dbg!(region_area);
        //dbg!(region_perimeter);
        //dbg!(region_area * region_perimeter);
        total_price += region_area * region_perimeter;
    }

    println!("The total price of fencing all regions on the map is {total_price}.");
}
