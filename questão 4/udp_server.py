import socket

HOST = '127.0.0.1'
PORT = 6000

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.bind((HOST, PORT))
    print(f"Servidor UDP aguardando mensagens em {HOST}:{PORT}...")
    while True:
        data, addr = s.recvfrom(1024)
        print(f"Recebido de {addr}: {data.decode('utf-8')}")
        s.sendto(b"Mensagem UDP recebida!", addr)