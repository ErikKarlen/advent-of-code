use std::cmp::max;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let num_seconds = 100;

    let re = regex::Regex::new(r"p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)")
        .unwrap();

    let mut robots: Vec<((i32, i32),(i32, i32))> = re
        .captures_iter(&input_string)
        .map(|cap| {
            let px = cap[1].parse::<i32>().unwrap();
            let py = cap[2].parse::<i32>().unwrap();
            let vx = cap[3].parse::<i32>().unwrap();
            let vy = cap[4].parse::<i32>().unwrap();
            //dbg!(cap);
            ((px, py), (vx, vy))
        })
        .collect();

    let (width, height): (i32, i32) = robots
        .iter()
        .fold((0, 0), |(width, height), robot|
            (max(width, robot.0.0 + 1), max(height, robot.0.1 + 1))
        );

    // After num_seconds seconds have passed
    robots = robots
        .iter()
        .map(|((px, py),(vx, vy))| {
            let new_px = (px + vx * num_seconds).rem_euclid(width);
            let new_py = (py + vy * num_seconds).rem_euclid(height);
            ((new_px, new_py),(*vx, *vy))
        })
        .collect();

    let quadrants: (i32, i32, i32, i32) = robots
        .iter()
        .fold((0, 0, 0, 0), |mut quadrants, (p,_v)| {
            if p.0 < width / 2 && p.1 < height / 2 {
                quadrants.0 += 1;
            } else if p.0 > width / 2 && p.1 < height / 2 {
                quadrants.1 += 1;
            } else if p.0 < width / 2 && p.1 > height / 2 {
                quadrants.2 += 1;
            } else if p.0 > width / 2 && p.1 > height / 2 {
                quadrants.3 += 1;
            }
            //dbg!(quadrants);
            quadrants
        });
    
    let safety_factor = quadrants.0 * quadrants.1 * quadrants.2 * quadrants.3;

    //dbg!(width);
    //dbg!(height);

    //dbg!(robots[10]);
    dbg!(safety_factor);

    println!("The safety factor after exactly {num_seconds} seconds have elapsed is {safety_factor}.");

}