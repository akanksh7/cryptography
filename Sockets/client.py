import socket, hashlib, rsa
from cryptography.fernet import Fernet

with socket.socket() as s:
    s.connect(('localhost', 12345))
    data = s.recv(8192)


# Split received data
pub_bytes, aes_key, enc_msg, enc_sig = data.split(b'||')
pub_key = rsa.PublicKey.load_pkcs1(pub_bytes)
cipher = Fernet(aes_key)

# Decrypt
msg = cipher.decrypt(enc_msg)
sig = cipher.decrypt(enc_sig)

# Verify
hash_val = hashlib.sha512(msg).digest()
try:
    rsa.verify(hash_val, sig, pub_key)
    print("✔ Integrity Verified:", msg.decode())
except:
    print("✖ Verification Failed")
