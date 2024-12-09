use std::collections::HashSet;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let input_string = std::fs::read_to_string(input_file)
        .expect("Failed to read input file");

    let mut filesystem_checksum = 0;

    let mut disk_map: Vec<i32> = input_string
        .chars()
        .enumerate()
        .map(|(_i, c)| c as i32 - '0' as i32)
        .collect();

    let disk_map_orig = disk_map.clone();

    let mut block_indexes: Vec<i32> = disk_map_orig
        .iter()
        .scan(0, |block_index, &size| {
            *block_index += size;
            Some(*block_index)
        })
        .collect();

    let mut disk_map_index = disk_map.len() - 1;
    let mut moved_indexes: HashSet<usize> = HashSet::new();

    while disk_map_index > 1
    {
        for empty_space_index in (1..disk_map_index).step_by(2)
        {
            if disk_map[empty_space_index] >= disk_map[disk_map_index]
            {
                moved_indexes.insert(disk_map_index);
                let id = disk_map_index / 2;
                disk_map[empty_space_index] -= disk_map[disk_map_index];
                for i in 0..disk_map_orig[disk_map_index]
                {
                    let block_pos = &block_indexes[empty_space_index - 1] + i;
                    //dbg!((id, block_pos));
                    filesystem_checksum += id * block_pos as usize;
                }
                block_indexes[empty_space_index - 1] += disk_map_orig[disk_map_index];
                break;
            }
        }
        disk_map_index -= 2;
    }

    for index in (2..disk_map.len()).step_by(2)
    {
        if !moved_indexes.contains(&index) {
            let id = index / 2;
            for i in 0..disk_map_orig[index]
            {
                let block_pos = &block_indexes[index - 1] + i;
                //dbg!((id, block_pos));
                filesystem_checksum += id * block_pos as usize;
            }
        }
    }

    println!("After compacting the hard drive usign the process requested the resulting \
        filesystem checksum is {filesystem_checksum}.");
}
