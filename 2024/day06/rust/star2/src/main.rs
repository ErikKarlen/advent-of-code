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

    let (obstacles, guard_init): (HashSet<(i32, i32)>, (i32, i32)) = input_string
        .lines()
        .enumerate()
        .fold(
        (HashSet::new(), (0, 0)),
        |(mut obstacles, mut guard_init), (row, line)|
        {
            line.chars().enumerate().for_each(|(col, c)|
            {
                // row is y, col is x
                if c == '#'
                {
                    obstacles.insert((col as i32, row as i32));
                } else if c == '^'
                {
                    guard_init = (col as i32, row as i32);
                }
            });
            (obstacles, guard_init)
        },
    );

    let mut guard = guard_init;
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

    visited.remove(&guard_init);

    let mut num_obstacle_positions  = 0;

    //for (i, new_obstacle) in visited.iter().enumerate()
    for new_obstacle in visited
    {
        //dbg!(i);
        //dbg!(visited.len());
        let mut new_obstacles: HashSet<(i32, i32)> = obstacles.clone();
        new_obstacles.insert(new_obstacle);
        let mut new_guard: (i32, i32) = guard_init;
        let mut new_visited_obstacles_dir_index: HashSet<((i32, i32), usize)> = HashSet::new();
        let new_dirs: Vec<(i32, i32)> = vec![(0, -1), (1, 0), (0, 1), (-1, 0)];
        let mut new_dirs_index: usize = 0;

        while 0 <= new_guard.0 && new_guard.0 < width && 0 <= new_guard.1 && new_guard.1 < height
        {
            let next_pos = (new_guard.0 + new_dirs[new_dirs_index].0, new_guard.1 + new_dirs[new_dirs_index].1);

            if new_visited_obstacles_dir_index.contains(&(next_pos, new_dirs_index))
            {
                num_obstacle_positions += 1;
                break;
            }

            if new_obstacles.contains(&next_pos)
            {
                new_visited_obstacles_dir_index.insert((next_pos, new_dirs_index));
                new_dirs_index = (new_dirs_index + 1) % new_dirs.len();
                continue;
            }

            new_guard = next_pos;
        }

    }

    println!("There are a total of {num_obstacle_positions} different positions for the obstruction so the guard gets stuck.")

}