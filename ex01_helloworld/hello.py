#!/usr/bin/env python

print("Test: ")
import build.hello_ext as hello_ext
print(hello_ext.greet("WORLD!"))
print(hello_ext.sum(12, 12))