from time import sleep

import sys

print(f'Set-Cookie: nani=u\r')
print('\r')
print(f'salut')
for line in sys.stdin:
    if line.rstrip() == 'Exit':
        break
    print(f'Processing Message from sys.stdin *****{line}*****')
print("salut")
sleep(0.1)
print("adios")