print fib(40);

sub fib {
    my $n = shift;
    if ($n < 2) {
        return 1;
    } else {
        return fib($n - 2) + fib($n - 1);
    }
}
