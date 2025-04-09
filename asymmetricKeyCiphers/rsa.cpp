#include <bits/stdc++.h>
using namespace std;

// Inefficient but simpler way to compute (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    for (long long i = 0; i < exp; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// Function to compute the greatest common divisor (GCD)
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Simplified function to compute modular inverse
long long modInverse(long long e, long long phi) {
    for (long long x = 1; x < phi; x++) {
        if ((e * x) % phi == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

int main() {
    long long p = 61, q = 53; // Example prime numbers
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    long long e = 17; // Public exponent
    while (gcd(e, phi) != 1)
        e++;
    
    long long d = modInverse(e, phi); // Private exponent
    
    long long message;
    cout << "Enter a number to encrypt (less than " << n << "): ";
    cin >> message;
    
    long long encryptedMessage = modExp(message, e, n);
    cout << "Encrypted message: " << encryptedMessage << endl;
    
    long long decryptedMessage = modExp(encryptedMessage, d, n);
    cout << "Decrypted message: " << decryptedMessage << endl;
    
    return 0;
}