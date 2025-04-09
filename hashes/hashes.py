import hashlib
#This code uses hashlib library to implement the hash code.
msg = input("Enter message: ")
md5 = hashlib.md5(msg.encode()).hexdigest()
sha256 = hashlib.sha256(msg.encode()).hexdigest()
sha512 = hashlib.sha512(msg.encode()).hexdigest()

print("MD5:", md5)
print("SHA-256:", sha256)
print("SHA-512:", sha512)

print("\n--- Verify Hashes ---")
if input("Enter MD5 to verify: ") == md5: print("MD5 correct")
else: print("MD5 wrong")

if input("Enter SHA-256 to verify: ") == sha256: print("SHA-256 correct")
else: print("SHA-256 wrong")

if input("Enter SHA-512 to verify: ") == sha512: print("SHA-512 correct")
else: print("SHA-512 wrong")
