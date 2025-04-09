#include<bits/stdc++.h>
using namespace std;
//This code takes input text and gives the vigenere cipher of the text and decrypts it too.
//The input text can consist of alphabets, numbers, other symbols included in ASCII and spaces.
//Only the alphabets will be converted according to the vigenere cipher and other symbols remain the same.
string extendKey(string key, int length)
{
    string extendedKey = "";
    int keyLength = key.length();
    for(int i=0;i<length;i++)
    {
        extendedKey+=key[i%keyLength];
    }
    return extendedKey;
}
string encrypt(string text, string key)
{
    string encryptedText="";
    int i=0;
    for(char c : text)
    {
        if(isalpha(c))
        {
            char base = (isupper(c))? 'A' : 'a';
            char keyBase = (isupper(key[i]))? 'A' : 'a';
            encryptedText+=((c-base+key[i++]-keyBase)%26)+base;
        }
        else
        {
            encryptedText+=c;
            i++;
        }
    }
    return encryptedText;
}
string decrypt(string text, string key)
{
    string decryptedText="";
    int i=0;
    for(char c : text)
    {
        if(isalpha(c))
        {
            char base = (isupper(c))? 'A' : 'a';
            char keyBase = (isupper(key[i]))? 'A' : 'a';
            decryptedText+=((c-base-key[i++]+keyBase+26)%26)+base;
        }
        else
        {
            decryptedText+=c;
            i++;
        }
    }
    return decryptedText;
}
int main()
{
    string key, text;
    cout<<"Enter text: ";
    getline(cin, text);
    cout<<"Enter key: ";
    getline(cin, key);
    int textLength = text.length();
    string extendedKey = extendKey(key, textLength);
    string encrypted = encrypt(text, extendedKey);
    cout<<"Encrypted Text: "<<encrypted<<endl;
    string decrypted = decrypt(encrypted, extendedKey);
    cout<<"Decrypted text: "<<decrypted<<endl;
    return 0;
}