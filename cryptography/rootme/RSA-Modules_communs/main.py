import base64
import math
from Crypto.PublicKey import RSA


firstPublicKey: bytes = base64.b64decode("MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCtbdQAzdaO7GHXxUsVZ+FmcddAHrugq+azkVdfgnHu6teK3hDQlk0BdNz9LlQT3BoHXg5/g9FDv3bBwaulpQEQPlGMUXEUnQAJ69KSVaLxHb5Wmb0vqX/qySKc8Hseqt5wbXklOrnZeHJ3Hm3mUeIplpWPf19C6goN3bUGrrniwwIDAQAB")
secondPublicKey: bytes = base64.b64decode("MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCtbdQAzdaO7GHXxUsVZ+FmcddAHrugq+azkVdfgnHu6teK3hDQlk0BdNz9LlQT3BoHXg5/g9FDv3bBwaulpQEQPlGMUXEUnQAJ69KSVaLxHb5Wmb0vqX/qySKc8Hseqt5wbXklOrnZeHJ3Hm3mUeIplpWPf19C6goN3bUGrrniwwIDBTy3")
module: int = int.from_bytes(bytes.fromhex("00ad6dd400cdd68eec61d7c54b1567e16671d7401ebba0abe6b391575f8271eeead78ade10d0964d0174dcfd2e5413dc1a075e0e7f83d143bf76c1c1aba5a501103e518c5171149d0009ebd29255a2f11dbe5699bd2fa97feac9229cf07b1eaade706d79253ab9d97872771e6de651e22996958f7f5f42ea0a0dddb506aeb9e2c3"))
firstKey = RSA.import_key(firstPublicKey)

print(firstKey.n == module)

# print("First public key: ", firstPublicKey.hex())
# print("Second public key: ", secondPublicKey.hex())

print(math.gcd(65537, 343223))


firstMessageInt : int = int.from_bytes(base64.b64decode("BzFd4riBUZdFuPCkB3LOh+5iyMImeQ/saFLVD+ca2L8VKSz0+wtTaL55RRpHBAQdl24Fb3XyVg2N9UDcx3slT+vZs7tr03W7oJZxVp3M0ihoCwer3xZNieem8WZQvQvyNP5s5gMT+K6pjB9hDFWWmHzsn7eOYxRJZTIDgxA4k2w="))
secondMessageInt : int = int.from_bytes(base64.b64decode("jmVRiKyVPy1CHiYLl8fvpsDAhz8rDa/Ug87ZUXZ//rMBKfcJ5MqZnQbyTJZwSNASnQfgel3J/xJsjlnf8LoChzhgT28qSppjMfWtQvR6mar1GA0Ya1VRHkhggX1RUFA4uzL56X5voi0wZEpJITUXubbujDXHjlAfdLC7BvL/5+w="))

temp : int = pow(secondMessageInt, 25421, module)
openTextInt : int = (pow(firstMessageInt, 133132, module) * pow(temp, -1, module) % module)

print((openTextInt.to_bytes(256, byteorder="big")).decode("ASCII"))
# First key: 
# MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCtbdQAzdaO7GHXxUsVZ+FmcddA
# Hrugq+azkVdfgnHu6teK3hDQlk0BdNz9LlQT3BoHXg5/g9FDv3bBwaulpQEQPlGM
# UXEUnQAJ69KSVaLxHb5Wmb0vqX/qySKc8Hseqt5wbXklOrnZeHJ3Hm3mUeIplpWP
# f19C6goN3bUGrrniwwIDAQAB
# 
# Second key:
# MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCtbdQAzdaO7GHXxUsVZ+FmcddA
# Hrugq+azkVdfgnHu6teK3hDQlk0BdNz9LlQT3BoHXg5/g9FDv3bBwaulpQEQPlGM
# UXEUnQAJ69KSVaLxHb5Wmb0vqX/qySKc8Hseqt5wbXklOrnZeHJ3Hm3mUeIplpWP
# f19C6goN3bUGrrniwwIDBTy3
# 
# 1) 010001 = 65537 v = 133132 
# 2) 053cb7 = 343223 u = -25421
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
