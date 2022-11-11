from ctypes import cdll
import os.path

paths = ['target/debug/libembed.so', 'target/release/libembed.so',
         'target/debug/libembed.dylib', 'target/release/libembed.dylib']

for p in paths:
    if os.path.exists(p):
        lib = cdll.LoadLibrary(p)
        lib.process()
        break
