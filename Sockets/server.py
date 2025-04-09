import socket, hashlib, rsa
from cryptography.fernet import Fernet

msg = input("Enter message: ")
hash_val = hashlib.sha512(msg.encode()).digest()

# Generate RSA key pair (use at least 1024 bits for SHA-512)
pub, priv = rsa.newkeys(1024)
signature = rsa.sign(hash_val, priv, 'SHA-512')

# Encrypt message and signature with AES (Fernet)
aes_key = Fernet.generate_key()
cipher = Fernet(aes_key)
enc_msg = cipher.encrypt(msg.encode())
enc_sig = cipher.encrypt(signature)

with socket.socket() as s:
    s.bind(('localhost', 12345)); s.listen(1)
    conn, _ = s.accept()
    with conn:
        conn.send(pub.save_pkcs1() + b'||' + aes_key + b'||' + enc_msg + b'||' + enc_sig)


