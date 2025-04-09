#include <bits/stdc++.h>
using namespace std;
const int SIZE = 5;

//This code uses playfair cipher, but while deciphering the encrypted text, it does not remove the additional X's added while processing the data initally
//and it does not add the spaces from the plain text as well. This code is a basic implementation of playfair cipher

// Function to remove duplicate characters from the key and construct the key matrix
vector<vector<char>> generateKeyMatrix(const string &key) 
{
    string processedKey;
    unordered_set<char> charSet;
    vector<vector<char>> keyMatrix(SIZE, vector<char>(SIZE));
    
    for (char c : key) 
    {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c) && charSet.insert(c).second) 
        {
            processedKey += c;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) 
    {
        if (c != 'J' && charSet.insert(c).second) 
        {
            processedKey += c;
        }
    }
    int k = 0;
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            keyMatrix[i][j] = processedKey[k++];
        }
    }
    return keyMatrix;
}

// Function to find the position of a character in the key matrix
pair<int, int> findPosition(const vector<vector<char>> &matrix, char c) 
{
    if (c == 'J') c = 'I';
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (matrix[i][j] == c) 
            {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never reach here
}

// Function to prepare the plaintext for encryption
string prepareText(string text) 
{
    string newText;
    for (char c : text) 
    {
        if (isalpha(c)) 
        {
            newText += toupper(c);
        }
    }
    text = newText;
    for (int i = 0; i < text.length(); i += 2) 
    {
        if (i + 1 < text.length() && text[i] == text[i + 1]) 
        {
            text.insert(i + 1, "X");
        }
    }
    if (text.length() % 2 != 0) {
        text += 'X';
    }
    return text;
}

// Function to encrypt the plaintext using the Playfair cipher
string encrypt(const string &text, const vector<vector<char>> &keyMatrix) 
{
    string cipherText;
    string preparedText = prepareText(text);    
    for (int i = 0; i < preparedText.length(); i += 2) 
    {
        pair<int, int> p1 = findPosition(keyMatrix, preparedText[i]);
        pair<int, int> p2 = findPosition(keyMatrix, preparedText[i + 1]);
        int row1 = p1.first, col1 = p1.second;
        int row2 = p2.first, col2 = p2.second;
        if (row1 == row2) 
        {   // Same row
            cipherText += keyMatrix[row1][(col1 + 1) % SIZE];
            cipherText += keyMatrix[row2][(col2 + 1) % SIZE];
        } 
        else if (col1 == col2) 
        {   // Same column
            cipherText += keyMatrix[(row1 + 1) % SIZE][col1];
            cipherText += keyMatrix[(row2 + 1) % SIZE][col2];
        } 
        else 
        {   // Rectangle swap
            cipherText += keyMatrix[row1][col2];
            cipherText += keyMatrix[row2][col1];
        }
    }
    return cipherText;
}

// Function to decrypt the ciphertext using the Playfair cipher
string decrypt(const string &text, const vector<vector<char>> &keyMatrix) 
{
    string plainText;    
    for (int i = 0; i < text.length(); i += 2) 
    {
        pair<int, int> p1 = findPosition(keyMatrix, text[i]);
        pair<int, int> p2 = findPosition(keyMatrix, text[i + 1]);
        int row1 = p1.first, col1 = p1.second;
        int row2 = p2.first, col2 = p2.second;    
        if (row1 == row2) 
        {   // Same row
            plainText += keyMatrix[row1][(col1 - 1 + SIZE) % SIZE];
            plainText += keyMatrix[row2][(col2 - 1 + SIZE) % SIZE];
        } 
        else if (col1 == col2) 
        {   // Same column
            plainText += keyMatrix[(row1 - 1 + SIZE) % SIZE][col1];
            plainText += keyMatrix[(row2 - 1 + SIZE) % SIZE][col2];
        } 
        else 
        {   // Rectangle swap
            plainText += keyMatrix[row1][col2];
            plainText += keyMatrix[row2][col1];
        }
    }
    return plainText;
}

int main() 
{
    string key, plaintext;
    cout << "Enter the key: ";
    getline(cin, key);
    cout << "Enter the plaintext: ";
    getline(cin, plaintext); 
    vector<vector<char>> keyMatrix = generateKeyMatrix(key);
    string encryptedText = encrypt(plaintext, keyMatrix);
    cout << "Encrypted text: " << encryptedText << endl;
    string decryptedText = decrypt(encryptedText, keyMatrix);
    cout << "Decrypted text: " << decryptedText << endl;
    return 0;
}
