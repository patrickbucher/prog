#!/usr/bin/python3

import unittest

from fib import fib

# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
class FibTest(unittest.TestCase):

    def test_n0(self):
        self.assertEqual(0, fib(0))

    def test_n1(self):
        self.assertEqual(1, fib(1))

    def test_n2(self):
        self.assertEqual(1, fib(2))

    def test_n3(self):
        self.assertEqual(2, fib(3))

    def test_n4(self):
        self.assertEqual(3, fib(4))

    def test_n8(self):
        self.assertEqual(21, fib(8))

    def test_n9(self):
        self.assertEqual(34, fib(9))

if __name__ == '__main__':
    unittest.main()
