#include <bits/stdc++.h>
using namespace std;

// Function to perform 3x3 matrix multiplication mod 26
vector<int> multiplyMatrix(const vector<vector<int>> &matrix, const vector<int> &textVector) 
{
    vector<int> result(3, 0);
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            result[i] += matrix[i][j] * textVector[j];
        }
        result[i] %= 26;
    }
    return result;
}

// Function to find determinant of 3x3 matrix mod 26
int determinant(const vector<vector<int>> &m) 
{
    int det = m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
            - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0])
            + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    return (det % 26 + 26) % 26;
}

// Function to find modular inverse under mod 26
int modInverse(int a) 
{
    for (int x = 1; x < 26; x++) 
    {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

// Function to get cofactor of 3x3 matrix
vector<vector<int>> cofactorMatrix(const vector<vector<int>> &m) 
{
    vector<vector<int>> cof(3, vector<int>(3));
    cof[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]);
    cof[0][1] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]);
    cof[0][2] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    cof[1][0] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]);
    cof[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]);
    cof[1][2] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]);
    cof[2][0] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]);
    cof[2][1] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]);
    cof[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
    return cof;
}

// Transpose a 3x3 matrix
vector<vector<int>> transpose(const vector<vector<int>> &m)
{
    vector<vector<int>> t(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            t[i][j] = m[j][i];
    return t;
}

// Function to compute inverse of 3x3 matrix mod 26
vector<vector<int>> inverseMatrix(const vector<vector<int>> &keyMatrix) 
{
    int det = determinant(keyMatrix);
    int detInv = modInverse(det);
    if (detInv == -1) 
    {
        cerr << "Matrix not invertible under mod 26.\n";
        exit(1);
    }

    vector<vector<int>> cof = cofactorMatrix(keyMatrix);
    vector<vector<int>> adj = transpose(cof);
    vector<vector<int>> inv(3, vector<int>(3));
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            inv[i][j] = ((adj[i][j] * detInv) % 26 + 26) % 26;

    return inv;
}

// Function to encrypt or decrypt text using Hill cipher
string processText(string text, const vector<vector<int>> &matrix) 
{
    string result = "";
    if (text.size() % 3 != 0) 
    {
        while (text.size() % 3 != 0) text += 'X';
    }
    
    for (size_t i = 0; i < text.length(); i += 3) 
    {
        vector<int> textVector = {text[i] - 'A', text[i + 1] - 'A', text[i + 2] - 'A'};
        vector<int> processedVector = multiplyMatrix(matrix, textVector);
        for (int v : processedVector)
            result += char(v + 'A');
    }
    return result;
}

int main() {
    string text;
    cout << "Enter plaintext (uppercase, will be padded to multiple of 3): ";
    cin >> text;
    // Example invertible 3x3 key matrix mod 26
    vector<vector<int>> keyMatrix = {{2, 4, 5}, {9, 2, 1}, {3, 17, 7}};
    vector<vector<int>> invMatrix = inverseMatrix(keyMatrix);
    string encryptedText = processText(text, keyMatrix);
    cout << "Encrypted text: " << encryptedText << endl;
    string decryptedText = processText(encryptedText, invMatrix);
    cout << "Decrypted text: " << decryptedText << endl;
    return 0;
}
