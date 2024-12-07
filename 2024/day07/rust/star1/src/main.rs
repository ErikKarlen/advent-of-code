use std::ops::{Add, Mul};


#[derive(Clone, Debug, Copy)]
enum Operator {
    Add,
    Mul,
}

fn apply_operation(operator: &Operator, left: u64, right: u64) -> u64
{
    match operator {
        Operator::Add => left.add(right),
        Operator::Mul => left.mul(right),
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let input_file = &args[1];

    let mut total_calibration_result: u64 = 0;

    let operators = vec![Operator::Add, Operator::Mul];

    for line in std::fs::read_to_string(input_file).unwrap().lines() {
        let parts: Vec<&str> = line
            .split(": ")
            .collect();

        let test_value: u64 = parts[0]
            .parse::<u64>()
            .unwrap();

        let numbers: Vec<u64> = parts[1]
            .split(" ")
            .map(|s: &str| s
                .parse::<u64>()
                .unwrap())
            .collect();


        let mut operator_combinations: Vec<Vec<Operator>> = operators
            .iter()
            .map(|o| vec![*o])
            .collect();

        for _i in 0..numbers.len()-2
        {
            operator_combinations = itertools::iproduct!(
                operator_combinations, operators.clone()
            )
            .map(|(mut v, o)| {
                v.push(o);
                v
            })
            .collect();
        }

        let mut produces_test_value = false;

        for operator_combination in operator_combinations
        {
            let mut test_result = numbers[0];

            for i in 1..numbers.len()
            {
                if test_result > test_value
                {
                    break;
                }
                let num_left = test_result;
                let num_right = numbers[i];
                let operator = operator_combination[i - 1];
                test_result = apply_operation(&operator, num_left, num_right);
            }

            if test_result == test_value
            {
                produces_test_value = true;
            }
        }

        if produces_test_value
        {
                total_calibration_result += test_value;
        }

        //dbg!(operator_combinations);
    }

    println!("The total calibration result from the equations is {total_calibration_result}.");
}