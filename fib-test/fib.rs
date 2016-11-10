fn main() {
    println!("{}", fib(40));
}

fn fib(n: i32) -> i32 {
    if n < 2 {
        1
    } else {
        fib(n - 2) + fib(n - 1)
    }
}
