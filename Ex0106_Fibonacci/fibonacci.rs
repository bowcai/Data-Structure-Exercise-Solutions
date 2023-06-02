// The first algorithm with complexity O(N^2)
pub fn fibonacci1(n: i32) {
    if n <= 0 {
        panic!("The input must be a positive integer.");
    }

    // println!("Fibonacci number {}: {}", 1, 1);
    // println!("Fibonacci number {}: {}", 2, 1);

    for i in 3..n + 1 {
        let mut current = 1i64;
        let mut previous = 1i64;

        for _ in 3..i + 1 {
            (current, previous) = (current + previous, current);
        }
        // println!("Fibonacci number {}: {}", i, current);
    }
}

// The second algorithm with complexity O(N)
pub fn fibonacci2(n: i32) {
    if n <= 0 {
        panic!("The input must be a positive integer.");
    }

    // println!("Fibonacci number {}: {}", 1, 1);
    // println!("Fibonacci number {}: {}", 2, 1);

    let mut current = 1i64;
    let mut previous = 1i64;

    for _ in 3..n + 1 {
        (current, previous) = (current + previous, current);
        // println!("Fibonacci number {}: {}", i, current);
    }
}

// The third algorithm that use recursion with complexity O(2^n)
pub fn fibonacci3(n: i32) -> i64 {
    if n <= 0 {
        panic!("The input must be a positive integer.");
    }

    match n {
        1 | 2 => 1,
        _ => fibonacci3(n - 1) + fibonacci3(n - 2),
    }
}

fn main() {
    use std::time::Instant;

    const TEST_TIMES: i32 = 100_000;
    const N_FIBONACCI: i32 = 25;

    let now1 = Instant::now();
    for _ in 0..TEST_TIMES {
        fibonacci1(N_FIBONACCI);
    }
    let elapsed1 = now1.elapsed();
    println!(
        "Total run time for algorithm 1 is {} ms.",
        elapsed1.as_millis()
    );

    let now2 = Instant::now();
    for _ in 0..TEST_TIMES {
        fibonacci2(N_FIBONACCI);
    }
    let elapsed2 = now2.elapsed();
    println!(
        "Total run time for algorithm 2 is {} ms.",
        elapsed2.as_millis()
    );

    let now3 = Instant::now();
    for _ in 0..TEST_TIMES {
        fibonacci3(N_FIBONACCI);
    }
    let elapsed3 = now3.elapsed();
    println!(
        "Total run time for algorithm 3 is {} ms.",
        elapsed3.as_millis()
    );
}
