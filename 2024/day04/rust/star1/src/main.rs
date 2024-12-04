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

    let search_word = "XMAS";
    let mut search_word_count: usize = 0;

    let word_search_grid: Vec<&str> = input_string
        .lines()
        .collect();

    for row in 0..word_search_grid.len()
    {
        for col in 0..word_search_grid[0].len() {
            if col + search_word.len() <= word_search_grid[0].len() 
            {
                let word_horiz: String = (0..search_word.len())
                    .map(|i| letter(&word_search_grid, row, col + i))
                    .collect();
                if search_word == word_horiz || search_word == word_horiz.chars().rev().collect::<String>()
                {
                    search_word_count += 1;
                }

                if row + search_word.len() <= word_search_grid.len()
                {
                    let word_rdiag: String = (0..search_word.len())
                        .map(|i| letter(&word_search_grid, row + i, col + i))
                        .collect();

                    if search_word == word_rdiag || search_word == word_rdiag.chars().rev().collect::<String>()
                    {
                        search_word_count += 1;
                    }
                }
            }
            if row + search_word.len() <= word_search_grid.len() 
            {
                let word_verti: String = (0..search_word.len())
                    .map(|i| letter(&word_search_grid, row + i, col))
                    .collect();
                if search_word == word_verti || search_word == word_verti.chars().rev().collect::<String>()
                {
                    search_word_count += 1;
                }

                if col >= search_word.len() - 1
                {
                    let word_ldiag: String = (0..search_word.len())
                        .map(|i| letter(&word_search_grid, row + i, col - i))
                        .collect();

                    if search_word == word_ldiag || search_word == word_ldiag.chars().rev().collect::<String>()
                    {
                        search_word_count += 1;
                    }
                }
            }
        }
    }

    dbg!(&word_search_grid);

    println!("The word {search_word} appears a total of {search_word_count} times in the little Elf's word search.");
}