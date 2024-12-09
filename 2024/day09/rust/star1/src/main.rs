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

    let mut block_pos = 0;
    let mut disk_map_end = disk_map.len() - 1;
    let mut disk_map_index = 0;

    while disk_map_index <= disk_map_end
    {
        for _block in 0..disk_map[disk_map_index]
        {
            let mut id = disk_map_index / 2;
            if disk_map_index % 2 == 1 {
                if disk_map[disk_map_end] == 0 {
                    disk_map_end -= 2;
                }
                id = disk_map_end / 2;
                disk_map[disk_map_end] -= 1;
            }
            //dbg!(id);
            filesystem_checksum += block_pos * id;

            //dbg!(filesystem_checksum);

            block_pos += 1;
        }
        disk_map_index += 1;
    }

    println!("After compacting the hard drive usign the process requested the resulting \
        filesystem checksum is {filesystem_checksum}.");
}
