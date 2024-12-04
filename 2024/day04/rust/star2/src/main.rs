fn letter(word_search_grid: &Vec<&str>, row: usize, col: usize) -> char {
    word_search_grid
        .get(row)
        .and_then(|s| s.chars().nth(col)).unwrap()
}

fn main()
{
    let args: Vec<String> = std::env::args()
        .collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let search_word = "MAS";
    let mut x_mas_count: usize = 0;

    let word_search_grid: Vec<&str> = input_string
        .lines()
        .collect();

    dbg!(&word_search_grid);

    for row in 0..word_search_grid.len()
    {
        for col in 0..word_search_grid[0].len() {
            if row + search_word.len() <= word_search_grid.len() && col + search_word.len() <= word_search_grid[0].len() 
            {
                let word_rdiag: String = (0..search_word.len())
                    .map(|i| letter(&word_search_grid, row + i, col + i))
                    .collect();

                let word_ldiag: String = (0..search_word.len())
                    .map(|i| letter(&word_search_grid, row + i, col + search_word.len() - 1 - i))
                    .collect();

                //dbg!(&word_rdiag);
                //dbg!(&word_ldiag);

                if (search_word == word_rdiag || search_word == word_rdiag.chars().rev().collect::<String>())
                    && (search_word == word_ldiag || search_word == word_ldiag.chars().rev().collect::<String>())
                {
                    x_mas_count += 1;
                }
            }
        }
    }

    println!("An X-MAS appears a total of {x_mas_count} times in the little Elf's word search.");
}