import socket

HOST = '127.0.0.1'
PORT = 6000

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.sendto(b"Ola, Servidor! Aqui eh o Cliente UDP.", (HOST, PORT))
    data, server = s.recvfrom(1024)
    print(f"Resposta do Servidor: {data.decode('utf-8')}")