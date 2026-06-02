import socket
import subprocess

HOST = '127.0.0.1'
PORT = 2323

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Servidor Telnet rodando em {HOST}:{PORT} (Pressione Ctrl+C para parar)...")
    
    while True:
        conn, addr = s.accept()
        with conn:
            conn.sendall(b"Bem-vindo ao Servidor Telnet Simples!\nDigite 'sair' para encerrar.\n> ")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                comando = data.decode('utf-8').strip()
                if comando.lower() == 'sair':
                    break
                try:
                    resultado = subprocess.check_output(comando, shell=True, stderr=subprocess.STDOUT, text=True)
                    resposta = resultado + "\n> "
                except Exception as e:
                    resposta = "Erro ao executar o comando.\n> "
                conn.sendall(resposta.encode('utf-8'))