use std::collections::{HashMap, HashSet};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let mut antinode_locations: HashSet<(i32, i32)> = HashSet::new();
    let mut num_antinode_locations = 0;

    let width: i32 = input_string.find("\n").unwrap() as i32;
    let height: i32 = input_string.len() as i32 / width;

    //dbg!((width, height));

    let frequency_to_antennas: HashMap<char, Vec<(i32, i32)>> = input_string
        .lines()
        .enumerate()
        .fold(
        HashMap::new(),
        |mut antennas, (row, line)|
        {
            line
                .chars()
                .enumerate()
                .for_each(|(col, c)|
                {
                    // row is y, col is x
                    if c == '.' || c == '#'
                    {
                        return;
                    }
                    antennas
                        .entry(c)
                        .or_insert(Vec::new())
                        .push((col as i32, row as i32));
                });
            antennas
        },
    );

    //dbg!(&frequency_to_antennas);

    for (_frequency, antennas) in frequency_to_antennas
    {
        let ants = &antennas.clone();

        let antenna_pairs: Vec<_> = ants
            .iter()
            .enumerate()
            .flat_map(|(i, &antenna1)| {
                ants[i + 1..]
                    .iter()
                    .map(move |&antenna2|
                        (antenna1, antenna2)
                    )
            })
            .collect();

        for (antenna1, antenna2) in &antenna_pairs
        {
            let dx = antenna2.0 - antenna1.0;
            let dy = antenna2.1 - antenna1.1;
            let antinode1 = (antenna2.0 + dx, antenna2.1 + dy);
            let antinode2 = (antenna1.0 - dx, antenna1.1 - dy);
            if 0 <= antinode1.0 && antinode1.0 < width && 0 <= antinode1.1 && antinode1.1 < height
            {
                //dbg!(antinode1);
                antinode_locations.insert(antinode1);
            }
            if 0 <= antinode2.0 && antinode2.0 < width && 0 <= antinode2.1 && antinode2.1 < height
            {
                //dbg!(antinode2);
                antinode_locations.insert(antinode2);
            }
        }

        //dbg!(antenna_pairs);
    }

    num_antinode_locations = antinode_locations.len();

    println!("The number of unique locations within the bounds of the map that contain an \
        antinode is {num_antinode_locations}.");
}