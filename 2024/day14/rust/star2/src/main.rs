use std::{cmp::max, collections::HashSet};
//use std::{cmp::max, collections::HashSet, thread::sleep, time::Duration, io::{self, Write}};
//use crossterm::{terminal::{Clear, ClearType}, cursor::MoveTo, execute};

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let num_seconds = 6888;

    let re = regex::Regex::new(r"p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)")
        .unwrap();

    let robots_init: Vec<((i32, i32),(i32, i32))> = re
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

    let (width, height): (i32, i32) = robots_init
        .iter()
        .fold((0, 0), |(width, height), robot|
            (max(width, robot.0.0 + 1), max(height, robot.0.1 + 1))
        );

    for second in num_seconds..num_seconds+1
    {

        // After num_seconds seconds have passed
        let robots: Vec<((i32, i32), (i32, i32))> = robots_init
            .iter()
            .map(|((px, py),(vx, vy))| {
                let new_px = (px + vx * second).rem_euclid(width);
                let new_py = (py + vy * second).rem_euclid(height);
                ((new_px, new_py),(*vx, *vy))
            })
            .collect();

        let robots_p: HashSet<(i32, i32)> = robots
            .iter()
            .fold(HashSet::new(), |mut robots_p, (p, _v)| {
                robots_p.insert(*p);
                robots_p
            });
        
        //dbg!(width);
        //dbg!(height);

        let mut s = String::new();

        for y in 0..height
        {
            for x in 0..width
            {
                if robots_p.contains(&(x, y)) {
                    s.push('@');
                } else {
                    s.push('.');
                }
            }
            s.push('\n');
        }

        println!("{s}");
        println!("{second}");
        //sleep(Duration::new(0, 500000000));
        // Clear the screen
        //execute!(io::stdout(), Clear(ClearType::All)).unwrap();
        // Move the crusor to the top-left corner
        //execute!(io::stdout(), MoveTo(0, 0)).unwrap();
    }

    println!("The fewest number of seconds that must elapse for the robots to display the Easter egg is {num_seconds}.");

}