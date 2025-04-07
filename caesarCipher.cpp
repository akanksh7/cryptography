#include <bits/stdc++.h>
using namespace std;

//This code takes input text and gives the caesar cipher of the text and decrypts it too.
//The input text can consist of alphabets, numbers, other symbols included in ASCII and spaces.
//Only the alphabets will be converted according to the caeser cipher and other symbols remain the same.
string encrypt(string text, int shift) 
{
    string result = "";
    for (char c : text) 
    {
        if (isalpha(c)) 
        {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base + shift) % 26 + base;
        } 
        else 
        {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, int shift) 
{
    return encrypt(text, 26 - shift);
}

int main() 
{
    string text;
    int shift;
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter shift value: ";
    cin >> shift;
    string encryptedText = encrypt(text, shift);
    cout << "Encrypted text: " << encryptedText << endl;
    string decryptedText = decrypt(encryptedText, shift);
    cout << "Decrypted text: " << decryptedText << endl;
    return 0;
}