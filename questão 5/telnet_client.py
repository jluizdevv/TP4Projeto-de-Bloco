import socket
import sys

HOST = '127.0.0.1'
PORT = 2323

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        data = s.recv(4096)
        if not data:
            break
        sys.stdout.write(data.decode('utf-8'))
        sys.stdout.flush()
        comando = input()
        s.sendall(comando.encode('utf-8') + b'\n')
        if comando.lower() == 'sair':
            break