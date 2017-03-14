#!/usr/bin/python3

import unittest

from mathfuncs import gcd, lcm

class TestMathfuncs(unittest.TestCase):

    def test_gcd(self):
        self.assertEqual(2, gcd(1024, 2))
        self.assertEqual(3, gcd(123, 321))
        self.assertEqual(1024, gcd(2048, 3072))

    def test_lcm(self):
        self.assertEqual(15, lcm(5, 3))
        self.assertEqual(240, lcm(80, 12))
        self.assertEqual(13161, lcm(123, 321))


if __name__ == '__main__':
    unittest.main()
