#include <bits/stdc++.h>
using namespace std;

// AES constants
const int Nb = 4;  // Number of columns in state
const int Nk = 4;  // Number of 32-bit words in key (AES-128)
const int Nr = 10; // Number of rounds (AES-128)

// AES S-Box
const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// AES Inverse S-Box
const uint8_t inv_sbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// Round constants
const uint8_t Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// AES helper functions
uint8_t xtime(uint8_t x) {
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

uint8_t multiply(uint8_t x, uint8_t y) {
    return (((y & 1) * x) ^
            ((y >> 1 & 1) * xtime(x)) ^
            ((y >> 2 & 1) * xtime(xtime(x))) ^
            ((y >> 3 & 1) * xtime(xtime(xtime(x)))) ^
            ((y >> 4 & 1) * xtime(xtime(xtime(xtime(x))))));
}

// AES operations
void SubBytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void InvSubBytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = inv_sbox[state[i][j]];
        }
    }
}

void ShiftRows(uint8_t state[4][4]) {
    uint8_t temp;
    
    // Row 1: shift left by 1
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    
    // Row 2: shift left by 2
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    
    // Row 3: shift left by 3 (or right by 1)
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void InvShiftRows(uint8_t state[4][4]) {
    uint8_t temp;
    
    // Row 1: shift right by 1
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;
    
    // Row 2: shift right by 2
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    
    // Row 3: shift right by 3 (or left by 1)
    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

void MixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    
    for (int c = 0; c < 4; c++) {
        temp[0] = state[0][c];
        temp[1] = state[1][c];
        temp[2] = state[2][c];
        temp[3] = state[3][c];
        
        state[0][c] = multiply(0x02, temp[0]) ^ multiply(0x03, temp[1]) ^ temp[2] ^ temp[3];
        state[1][c] = temp[0] ^ multiply(0x02, temp[1]) ^ multiply(0x03, temp[2]) ^ temp[3];
        state[2][c] = temp[0] ^ temp[1] ^ multiply(0x02, temp[2]) ^ multiply(0x03, temp[3]);
        state[3][c] = multiply(0x03, temp[0]) ^ temp[1] ^ temp[2] ^ multiply(0x02, temp[3]);
    }
}

void InvMixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    
    for (int c = 0; c < 4; c++) {
        temp[0] = state[0][c];
        temp[1] = state[1][c];
        temp[2] = state[2][c];
        temp[3] = state[3][c];
        
        state[0][c] = multiply(0x0e, temp[0]) ^ multiply(0x0b, temp[1]) ^ multiply(0x0d, temp[2]) ^ multiply(0x09, temp[3]);
        state[1][c] = multiply(0x09, temp[0]) ^ multiply(0x0e, temp[1]) ^ multiply(0x0b, temp[2]) ^ multiply(0x0d, temp[3]);
        state[2][c] = multiply(0x0d, temp[0]) ^ multiply(0x09, temp[1]) ^ multiply(0x0e, temp[2]) ^ multiply(0x0b, temp[3]);
        state[3][c] = multiply(0x0b, temp[0]) ^ multiply(0x0d, temp[1]) ^ multiply(0x09, temp[2]) ^ multiply(0x0e, temp[3]);
    }
}

void AddRoundKey(uint8_t state[4][4], const uint8_t* roundKey) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] ^= roundKey[i * 4 + j];
        }
    }
}

// Key expansion
void KeyExpansion(const uint8_t* key, uint8_t* w) {
    uint8_t temp[4];
    int i = 0;
    
    // Copy the key into the first Nk words
    while (i < Nk) {
        w[4*i] = key[4*i];
        w[4*i+1] = key[4*i+1];
        w[4*i+2] = key[4*i+2];
        w[4*i+3] = key[4*i+3];
        i++;
    }
    
    // Generate the expanded key
    i = Nk;
    while (i < Nb * (Nr + 1)) {
        // Copy the previous word
        for (int j = 0; j < 4; j++) {
            temp[j] = w[(i-1) * 4 + j];
        }
        
        if (i % Nk == 0) {
            // RotWord
            uint8_t k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;
            
            // SubWord
            for (int j = 0; j < 4; j++) {
                temp[j] = sbox[temp[j]];
            }
            
            // XOR with Rcon
            temp[0] = temp[0] ^ Rcon[i/Nk];
        }
        
        // w[i] = w[i-Nk] XOR temp
        for (int j = 0; j < 4; j++) {
            w[i * 4 + j] = w[(i - Nk) * 4 + j] ^ temp[j];
        }
        i++;
    }
}

// AES Encryption
void AES_Encrypt(const uint8_t* input, uint8_t* output, const uint8_t* expandedKey) {
    uint8_t state[4][4];
    
    // Copy input to state array (column-major order)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = input[i * 4 + j];
        }
    }
    
    // Initial round key addition
    AddRoundKey(state, expandedKey);
    
    // Main rounds
    for (int round = 1; round < Nr; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey + (round * 4 * Nb));
    }
    
    // Final round (no MixColumns)
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey + (Nr * 4 * Nb));
    
    // Copy state to output (column-major order)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            output[i * 4 + j] = state[j][i];
        }
    }
}

// AES Decryption
void AES_Decrypt(const uint8_t* input, uint8_t* output, const uint8_t* expandedKey) {
    uint8_t state[4][4];
    
    // Copy input to state array (column-major order)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = input[i * 4 + j];
        }
    }
    
    // Initial round key addition (with last round key)
    AddRoundKey(state, expandedKey + (Nr * 4 * Nb));
    
    // Main rounds
    for (int round = Nr - 1; round > 0; round--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, expandedKey + (round * 4 * Nb));
        InvMixColumns(state);
    }
    
    // Final round (no InvMixColumns)
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, expandedKey);
    
    // Copy state to output (column-major order)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            output[i * 4 + j] = state[j][i];
        }
    }
}

// Improved hex string utility functions
string bytesToHex(const vector<uint8_t>& bytes) {
    stringstream ss;
    ss << hex << setfill('0');
    for (size_t i = 0; i < bytes.size(); i++) {
        ss << setw(2) << static_cast<int>(bytes[i]);
    }
    return ss.str();
}

vector<uint8_t> hexToBytes(const string& hex) {
    vector<uint8_t> bytes;
    
    // Make sure we have an even length hex string
    string processedHex = hex;
    if (processedHex.length() % 2 != 0) {
        processedHex = "0" + processedHex;
    }
    
    for (size_t i = 0; i < processedHex.length(); i += 2) {
        string byte = processedHex.substr(i, 2);
        // Validate the hex string
        if (!isxdigit(byte[0]) || !isxdigit(byte[1])) {
            throw runtime_error("Invalid hex string");
        }
        uint8_t val = static_cast<uint8_t>(strtol(byte.c_str(), nullptr, 16));
        bytes.push_back(val);
    }
    
    return bytes;
}

// Improved PKCS#7 padding
vector<uint8_t> addPKCS7Padding(const vector<uint8_t>& data, int blockSize) {
    int padLength = blockSize - (data.size() % blockSize);
    vector<uint8_t> padded = data;
    for (int i = 0; i < padLength; i++) {
        padded.push_back(static_cast<uint8_t>(padLength));
    }
    return padded;
}

vector<uint8_t> removePKCS7Padding(const vector<uint8_t>& data) {
    if (data.empty()) {
        return data;
    }
    
    uint8_t padValue = data.back();
    if (padValue == 0 || padValue > data.size()) {
        throw runtime_error("Invalid PKCS#7 padding");
    }
    
    // Validate padding
    for (size_t i = data.size() - padValue; i < data.size(); i++) {
        if (data[i] != padValue) {
            throw runtime_error("Invalid PKCS#7 padding");
        }
    }
    
    return vector<uint8_t>(data.begin(), data.end() - padValue);
}

// Main function
int main() {
    string operation, input, key_str;
    
    cout << "Enter operation (encrypt/decrypt): ";
    getline(cin, operation);
    transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
    
    cout << "Enter input string: ";
    getline(cin, input);
    
    cout << "Enter 16-character key (will be padded/truncated if needed): ";
    getline(cin, key_str);
    
    // Process key (ensure it's 16 bytes)
    if (key_str.length() < 16) {
        key_str.append(16 - key_str.length(), '\0');  // Pad with nulls
    } else if (key_str.length() > 16) {
        key_str = key_str.substr(0, 16);  // Truncate
    }
    
    // Convert key string to bytes
    uint8_t key[16];
    for (int i = 0; i < 16; i++) {
        key[i] = static_cast<uint8_t>(key_str[i]);
    }
    
    // Expanded key storage
    uint8_t expandedKey[4 * Nb * (Nr + 1)];
    KeyExpansion(key, expandedKey);
    
    try {
        if (operation == "encrypt") {
            // For encryption, convert string to bytes
            vector<uint8_t> inputBytes(input.begin(), input.end());
            
            // Apply PKCS#7 padding
            vector<uint8_t> paddedInput = addPKCS7Padding(inputBytes, 16);
            
            // Encrypt each block
            vector<uint8_t> encryptedBytes(paddedInput.size());
            for (size_t i = 0; i < paddedInput.size(); i += 16) {
                AES_Encrypt(&paddedInput[i], &encryptedBytes[i], expandedKey);
            }
            
            // Output as hex
            string hexOutput = bytesToHex(encryptedBytes);
            cout << "Encrypted (hex): " << hexOutput << endl;
        }
        else if (operation == "decrypt") {
            // For decryption, convert hex string to bytes
            vector<uint8_t> inputBytes;
            try {
                inputBytes = hexToBytes(input);
            } catch (const exception& e) {
                cout << "Error parsing hex input: " << e.what() << endl;
                return 1;
            }
            
            // Check input size
            if (inputBytes.size() % 16 != 0) {
                cout << "Error: Encrypted data length must be a multiple of 16 bytes." << endl;
                return 1;
            }
            
            // Decrypt each block
            vector<uint8_t> decryptedBytes(inputBytes.size());
            for (size_t i = 0; i < inputBytes.size(); i += 16) {
                AES_Decrypt(&inputBytes[i], &decryptedBytes[i], expandedKey);
            }
            
            // Remove padding and convert to string
            try {
                vector<uint8_t> unpaddedOutput = removePKCS7Padding(decryptedBytes);
                string decryptedText(unpaddedOutput.begin(), unpaddedOutput.end());
                cout << "Decrypted: " << decryptedText << endl;
            } catch (const exception& e) {
                cout << "Error removing padding: " << e.what() << endl;
                return 1;
            }
        }
        else {
            cout << "Invalid operation. Please enter 'encrypt' or 'decrypt'." << endl;
            return 1;
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}