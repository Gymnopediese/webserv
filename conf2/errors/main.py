import requests
from glob import glob
# Read the contents of REQUEST.TXT
PATH = "conf2/errors/"


def run_request_file(file):
	import socket
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(('localhost', 4242))
	with open(file) as f:
		text = bytes(f.read().replace('\n', '\r\n').replace('LONG', 'K' * 5000), 'utf-8')
		data = s.sendall(text)
	paket = s.recv(3000).decode('utf-8')
	print(file)
	print(paket.split('\r\n')[0])
	s.close()


def main():
    with open(PATH + "DELETEME", 'w') as e:
        e.write("delete me please")
    print("BASIC TESTS")
    files = glob(PATH + "requests/*")
    files.sort()
    for file in files:
        run_request_file(file)
    
    print("ERROR HANDLING")
    files = glob(PATH + "errors/*")
    files.sort()
    for file in files:
        run_request_file(file)


main()