# 
# name = x           xsxxxaxxxxxxxxxxx
import base64

b64_data = "IRZjBh6GxjeYI7YZvxwfBIWl6zRC+m9bMwaVzdL5Ax0CqysGWAm6R6OdxdV+xc3r6293RraAf5gR6U4Fuqpti1JokCqFh50yuPa0eqphvswTA8G/9k0vHmbIBvxgn89l"

binary_data = bytearray(base64.b64decode(b64_data))  # Используем bytearray для изменения
print("Original data:", binary_data.hex())

trueBytes = b"true;"
falseBytes = b"false"

print("true; =", trueBytes.hex())
print("false =", falseBytes.hex())

# Маска для XOR (должна быть одинаковой длины)
mask = bytes(a ^ b for a, b in zip(falseBytes, trueBytes))
print("mask =", mask.hex())

# Применяем XOR к нужной части данных
for i in range(5):
    binary_data[43 + i] ^= mask[i]

print("Modified data:", binary_data.hex())

# Кодируем обратно в base64
new_b64_data = base64.b64encode(binary_data)
print("New Base64:", new_b64_data.decode())
# tokenBinary: bytes = bytes.fromhex("211663061e86c6379823b619bf1c1f0485a5eb3442fa6f5b330695cdd2f9031d2834fdda264da3ea24af60c23fa77070667ac3d1a90ae464f440a848ddebd6ede7aa40e6a2299a6cfeaa822334363d5d7c5bc54602d89fc7e8e2662e00ceb3c3")


# token: bytes = bytes(a ^ b for a, b in zip(bytes.fromhex("726c719a18"), mask)).hex()

# print("false xor mask = ", bytes(a ^ b for a, b in zip(bytes.fromhex("726c719a18"), mask)).hex())

# 607f688c46

# i = 44 <= 49

# 
# 
# 
# [?] Name : admin1
# [?] Mail address (To receive alert when new exploits are published) :   adminmail
# [*] Let's generate the authentification token....
# 1)--> First, a plaintext token is generated :
# |	b'[id=546815648;name=admin1;is_member=false;mail=adminmail;pad=00]'
# 2)--> Second, the token is encrypted with military grade encryption (AES CBC)
# |	AES_CBC(<Secret_key>,<IV>,b'[id=546815648;name=admin1;is_member=false;mail=adminmail;pad=00]')
# |	Your token is : 'IRZjBh6GxjeYI7YZvxwfBAj8TwKez1RzBoOE+cBtY5JZ5/Ao2EMGgr/0hjlZ4ANox7UE+q+dURDiNUSSJwpAhg=='
# |	Save it to be able to login later...
# 
# 
# [id=546815648;name=admin1;is_member=false;mail=adminmail;pad=00] = 211663061e86c6379823b619bf1c1f0408fc4f029ecf5473068384f9c06d639259e7f028d8430682bff4863959e00368c7b504faaf9d5110e2354492270a4086
# 
# [id=546815648;na = 211663061e86c6379823b619bf1c1f04
# me=admin1;is_mem = 08fc4f029ecf5473068384f9c06d6392
# ber=false;mail=a = 59e7f028d8430682bff4863959e00368
# dminmail;pad=00] = c7b504faaf9d5110e2354492270a4086
#  
# [id=546815648;name=x           xsxxxaxxxxxxxxxxx;is_member=false;mail=adminmail;pad=00000000000] = 211663061e86c6379823b619bf1c1f0485a5eb3442fa6f5b330695cdd2f9031d0557b7df6ab241dc4d8c6890b0269c381abe75074504544c45c400607a18392358288f3e4217d97d2cd990d5498f8734993f8dc1fbb66d9fa1e25238ec9991f1
# [id=546815648;name=x           xadmin1xxxxxxxxxx;is_member=false;mail=adminmail;pad=00000000000]
# 
# 
# 
# 
# [id=546815648;na = 211663061e86c6379823b619bf1c1f04
# me=x           x = 85a5eb3442fa6f5b330695cdd2f9031d
# x              x = 0557b7df6ab241dc4d8c6890b0269c38
# ;is_member=false = 1abe75074504544c45c400607a183923
# ;mail=adminmail; = 58288f3e4217d97d2cd990d5498f8734
# pad=00000000000] = 993f8dc1fbb66d9fa1e25238ec9991f1
# 
# 
#
# 
# 
# 
# 
# 
# 
# 
# 
# 
# d02cbe6635
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
