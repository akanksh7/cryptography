# cryptography
This repository contains various cryptographic algorithms implemented using C++ and Python, categorized into symmetric and asymmetric encryption, hashing, and socket communication.

<pre> ``` cryptography/ ├── asymmetricKeyCiphers/ │ └── rsa.cpp # RSA encryption algorithm in C++ ├── hashes/ │ └── hashes.py # Hashing using SHA, MD5, etc. in Python ├── Sockets/ │ ├── client.py # Python client for encrypted communication │ └── server.py # Python server for encrypted communication ├── symmetricKeyCiphers/ │ ├── Classical/ │ │ ├── caesarCipher.cpp │ │ ├── hillCipher.cpp │ │ ├── playFairCipher.cpp │ │ └── vigenereCipher.cpp │ └── Modern/ │ ├── AES.cpp # AES encryption in C++ │ ├── AES.exe # Compiled executable │ ├── DES.cpp # DES encryption in C++ │ └── DES.exe # Compiled executable └── README.md ``` </pre>

🔐 Algorithms Implemented
🟩 Symmetric Key Ciphers
Classical
Caesar Cipher – Basic shift cipher.

Hill Cipher – Based on matrix encryption.

Playfair Cipher – 5x5 matrix digraph substitution.

Vigenère Cipher – Repeating-key polyalphabetic substitution.

Modern
AES (Advanced Encryption Standard) – 128-bit block cipher.

DES (Data Encryption Standard) – 64-bit block cipher.

🟨 Asymmetric Key Cipher
RSA – Public-key cryptography algorithm (basic implementation).

🟦 Hashing
SHA / MD5 – Hashing implemented in Python (hashes.py).

🟧 Socket Communication
client.py & server.py – Basic TCP client-server setup (for secure message transfer simulation, e.g., using encrypted payloads).



Future improvements: 
1. Fix AES code (Some problems in it).
2. Complete Socket codes.
3. Add DSS Code in asymmetric key ciphers.
4. Understand better and write complete codes for hashing algorithms.


