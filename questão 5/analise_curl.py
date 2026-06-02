import subprocess

HOST = '127.0.0.1'
PORT = 2323

print(f"Iniciando analise com curl no servidor Telnet {HOST}:{PORT}...")
try:
    resultado = subprocess.run(
        ["curl", "-v", f"telnet://{HOST}:{PORT}"],
        input=b"sair\n",
        capture_output=True,
        timeout=5
    )
    print("\n--- SAIDA DO TERMINAL ---")
    print(resultado.stdout.decode('utf-8', errors='ignore'))
    print("\n--- LOGS DE REDE (CURL VERBOSE) ---")
    print(resultado.stderr.decode('utf-8', errors='ignore'))
    
except subprocess.TimeoutExpired as e:
    print("\n--- SAIDA DO TERMINAL (Ate o Timeout) ---")
    print(e.stdout.decode('utf-8', errors='ignore') if e.stdout else "")
    print("\n--- LOGS DE REDE (CURL VERBOSE) ---")
    print(e.stderr.decode('utf-8', errors='ignore') if e.stderr else "")
except Exception as e:
    print(f"Erro na execucao: {e}")