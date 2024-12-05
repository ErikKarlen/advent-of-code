use std::collections::{HashMap, HashSet};

fn main()
{
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let mut sorted_middle_page_sum: usize = 0;
    let mut rules_map: HashMap<usize, HashSet<usize>> = HashMap::new();

    let parts: Vec<&str> = input_string
        .split("\n\n")
        .collect();

    parts[0]
        .lines()
        .map(|line| {
            // split the string into two parts and convert to usize and store in tuple (before: usize, after: usize)
            let line_parts: Vec<&str> = line
                .split("|")
                .collect();
            let before: usize = line_parts[0]
                .parse::<usize>()
                .unwrap();
            let after: usize = line_parts[1]
                .parse::<usize>()
                .unwrap();
            (before, after)
        })
        .for_each(|(before, after)| {
            // insert after into set if before exists in map, otherwise create new set first
            rules_map
                .entry(before)
                .or_insert_with(HashSet::new)
                .insert(after);
        });

    let updates: Vec<Vec<usize>> = parts[1]
        .lines()
        .map(|line| line
                .split(",")
                .map(|num_str| num_str
                    .parse::<usize>()
                    .unwrap()
                )
                .collect())
        .collect();


    for update in updates
    {
        let mut seen_pages: HashSet<usize> = HashSet::new();
        let mut valid_update = true;
        for page in &update
        {
            seen_pages.insert(*page);
            if rules_map.contains_key(&page) {
                for after_page in &rules_map[&page]
                {
                    if seen_pages.contains(&after_page) {
                        valid_update = false;
                        break;
                    }
                }
            }
        }
        if !valid_update {
            let mut sorted_pages: Vec<usize> = update
                .to_vec();
            sorted_pages
                .sort_by(|l, r| {
                    if rules_map.contains_key(l) && rules_map[l].contains(r) {
                        return std::cmp::Ordering::Less;
                    }
                    std::cmp::Ordering::Greater
                });

            sorted_middle_page_sum += sorted_pages[sorted_pages.len() / 2];
            //dbg!(&sorted_pages);
        }
    }

    println!("If you add up all the middle page numbers from the incorrectly-ordered updates after ordering them you get {sorted_middle_page_sum}.");
}