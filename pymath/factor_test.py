#!/usr/bin/python3

import unittest

from factor import factorize

class TestFactor(unittest.TestCase):

    def test_factorize(self):
        self.assertEqual(sorted([3, 41]), sorted(factorize(123)))
        self.assertEqual(sorted([2, 2, 3, 73]), sorted(factorize(876)))
        self.assertEqual([23], factorize(23))

if __name__ == '__main__':
    unittest.main()
