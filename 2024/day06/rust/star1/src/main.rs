use std::collections::HashSet;

fn main()
{
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let width: i32 = input_string.find("\n").unwrap() as i32;
    let height: i32 = input_string.len() as i32 / width;

    let (obstacles, mut guard): (HashSet<(i32, i32)>, (i32, i32)) = input_string
        .lines()
        .enumerate()
        .fold(
        (HashSet::new(), (0, 0)),
        |(mut obstacles, mut guard), (row, line)|
        {
            line.chars().enumerate().for_each(|(col, c)|
            {
                // row is y, col is x
                if c == '#'
                {
                    obstacles.insert((col as i32, row as i32));
                } else if c == '^'
                {
                    guard = (col as i32, row as i32);
                }
            });
            (obstacles, guard)
        },
    );

    let dirs: Vec<(i32, i32)> = vec![(0, -1), (1, 0), (0, 1), (-1, 0)];
    let mut dirs_index: usize = 0;
    let mut visited: HashSet<(i32, i32)> = HashSet::new();

    while 0 <= guard.0 && guard.0 < width && 0 <= guard.1 && guard.1 < height
    {
        visited.insert(guard);

        let mut next_pos = (guard.0 + dirs[dirs_index].0, guard.1 + dirs[dirs_index].1);

        if obstacles.contains(&next_pos)
        {
            dirs_index = (dirs_index + 1) % dirs.len();
            next_pos = (guard.0 + dirs[dirs_index].0, guard.1 + dirs[dirs_index].1);
        }

        guard = next_pos;
    }

    println!("The guard will visit a total of {} distinct positions before leaving the mapped area.", visited.len());

}