#!/usr/bin/python3

import unittest

from prime import is_prime, get_primes

class PrimesTest(unittest.TestCase):

    def test_primes(self):
        self.assertTrue(is_prime(23))
        self.assertFalse(is_prime(81))

    def test_prime_range(self):
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
            41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
        self.assertEqual(sorted(primes), sorted(get_primes(1, 100)))

if __name__ == '__main__':
    unittest.main()
