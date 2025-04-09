#include <bits/stdc++.h>
using namespace std;

// Initial Permutation Table
int initial_perm[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int final_perm[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion D-box Table
int expansion_table[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Straight Permutation Table
int perm_tab[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// S-box Table
int sbox[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Parity bit drop table
int parity_drop[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Key Compression Table (56 bits to 48 bits)
int key_comp[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Number of key bits shifted per round
int shift_table[16] = {
    1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1
};

// Function to convert hexadecimal to binary
string hex2bin(string s) {
    unordered_map<char, string> mp;
    mp['0'] = "0000";
    mp['1'] = "0001";
    mp['2'] = "0010";
    mp['3'] = "0011";
    mp['4'] = "0100";
    mp['5'] = "0101";
    mp['6'] = "0110";
    mp['7'] = "0111";
    mp['8'] = "1000";
    mp['9'] = "1001";
    mp['A'] = "1010";
    mp['B'] = "1011";
    mp['C'] = "1100";
    mp['D'] = "1101";
    mp['E'] = "1110";
    mp['F'] = "1111";
    mp['a'] = "1010";
    mp['b'] = "1011";
    mp['c'] = "1100";
    mp['d'] = "1101";
    mp['e'] = "1110";
    mp['f'] = "1111";
    
    string bin = "";
    for (char c : s) {
        if (mp.find(c) != mp.end()) {
            bin += mp[c];
        } else {
            // Handle invalid character
            cout << "Invalid hexadecimal character: " << c << endl;
            return "";
        }
    }
    return bin;
}

// Function to convert binary to hexadecimal with proper padding
string bin2hex(string s) {
    // Make sure the binary string length is a multiple of 4
    while (s.length() % 4 != 0) {
        s = '0' + s;
    }
    
    unordered_map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    
    string hex = "";
    for (size_t i = 0; i < s.length(); i += 4) {
        string ch = s.substr(i, 4);
        hex += mp[ch];
    }
    
    // Ensure output is always 16 characters (64 bits) for a block
    if (hex.length() == 15) {
        hex = "0" + hex;  // Add leading zero if missing
    }
    return hex;
}

// Function to convert binary to decimal
int bin2dec(string s) {
    int dec = 0;
    for (int i = 0; i < s.length(); i++) {
        dec = dec * 2 + (s[i] - '0');
    }
    return dec;
}

// Function to convert decimal to binary with padding
string dec2bin(int n) {
    string bin = "";
    while (n > 0) {
        bin = (char)((n % 2) + '0') + bin;
        n /= 2;
    }
    // Padding to ensure 4 bits
    while (bin.length() < 4) {
        bin = '0' + bin;
    }
    return bin;
}

// Function to convert text to hexadecimal
string text2hex(string text) {
    stringstream ss;
    for (char c : text) {
        ss << setw(2) << setfill('0') << hex << (int)(unsigned char)c;
    }
    return ss.str();
}

// Function to convert hexadecimal to text
string hex2text(string hex) {
    string text = "";
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byte = hex.substr(i, 2);
        char c = (char)stoi(byte, nullptr, 16);
        text += c;
    }
    return text;
}

// Function to check if a string is valid hexadecimal
bool isValidHex(string s) {
    for (char c : s) {
        if (!isxdigit(c)) {
            return false;
        }
    }
    return true;
}

// Function to perform the permutation on the given string
string permute(string k, int* arr, int n) {
    string per = "";
    for (int i = 0; i < n; i++) {
        per += k[arr[i] - 1];
    }
    return per;
}

// Function to perform left circular shift on the key
string shift_left(string k, int shifts) {
    string s = "";
    for (int i = shifts; i < 28; i++) {
        s += k[i];
    }
    for (int i = 0; i < shifts; i++) {
        s += k[i];
    }
    return s;
}

// Function to perform XOR operation on two binary strings
string xor_operation(string a, string b) {
    string result = "";
    for (size_t i = 0; i < a.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to generate the 16 round keys
vector<string> generate_keys(string key) {
    // Convert key to binary
    key = hex2bin(key);
    
    // Parity bit drop, convert 64-bit key to 56-bit key
    string perm_key = permute(key, parity_drop, 56);
    
    // Split key into two halves
    string left = perm_key.substr(0, 28);
    string right = perm_key.substr(28, 28);
    
    vector<string> round_keys;
    
    // Generate 16 keys
    for (int i = 0; i < 16; i++) {
        // Left circular shift
        left = shift_left(left, shift_table[i]);
        right = shift_left(right, shift_table[i]);
        
        // Combine left and right halves
        string combined = left + right;
        
        // Key compression
        string round_key = permute(combined, key_comp, 48);
        
        round_keys.push_back(round_key);
    }
    
    return round_keys;
}

// DES encryption function
string encrypt(string plaintext, vector<string> round_keys) {
    // Convert plaintext from hex to binary
    plaintext = hex2bin(plaintext);
    
    // Ensure we have a 64-bit input
    while (plaintext.length() < 64) {
        plaintext = '0' + plaintext;
    }
    
    // Initial Permutation
    plaintext = permute(plaintext, initial_perm, 64);
    
    // Split text into two halves
    string left = plaintext.substr(0, 32);
    string right = plaintext.substr(32, 32);
    
    // 16 rounds of encryption
    for (int i = 0; i < 16; i++) {
        // Expansion: 32-bit to 48-bit
        string right_expanded = permute(right, expansion_table, 48);
        
        // XOR with round key
        string xor_result = xor_operation(right_expanded, round_keys[i]);
        
        // S-box substitution
        string s_box_output = "";
        for (int j = 0; j < 8; j++) {
            // Extract 6-bit group
            string row_str = "";
            row_str += xor_result[j * 6];
            row_str += xor_result[j * 6 + 5];
            int row = bin2dec(row_str);
            
            string col_str = xor_result.substr(j * 6 + 1, 4);
            int col = bin2dec(col_str);
            
            // Get value from S-box table
            int val = sbox[j][row][col];
            s_box_output += dec2bin(val);
        }
        
        // Straight D-box Permutation
        s_box_output = permute(s_box_output, perm_tab, 32);
        
        // XOR with left half
        string result = xor_operation(left, s_box_output);
        left = result;
        
        // Swap left and right for next round (except last round)
        if (i != 15) {
            swap(left, right);
        }
    }
    
    // Combine left and right for the final permutation
    string combined = left + right;
    
    // Final Permutation
    string ciphertext = permute(combined, final_perm, 64);
    
    // Convert from binary to hexadecimal
    return bin2hex(ciphertext);
}

// DES decryption function
string decrypt(string ciphertext, vector<string> round_keys) {
    // Create a copy of the round keys to avoid modifying the original
    vector<string> decryption_keys = round_keys;
    // For decryption, use keys in reverse order
    reverse(decryption_keys.begin(), decryption_keys.end());
    
    // Rest of the algorithm is the same as encryption
    return encrypt(ciphertext, decryption_keys);
}

// Function to pad the plaintext to 64-bit blocks
string pad_text(string text) {
    while (text.length() % 16 != 0) {
        text += '0';
    }
    return text;
}

// Function to process a longer message block by block
string process_message(string message, vector<string> round_keys, bool is_decrypt) {
    // Pad the message
    message = pad_text(message);
    
    string result = "";
    for (size_t i = 0; i < message.length(); i += 16) {
        string block = message.substr(i, 16);
        if (is_decrypt) {
            result += decrypt(block, round_keys);
        } else {
            result += encrypt(block, round_keys);
        }
    }
    
    return result;
}

int main() {
    string key, input;
    int input_type, operation, output_type;
    
    // Get key
    cout << "Enter the 64-bit key (16 hexadecimal characters): ";
    cin >> key;
    
    // Convert key to uppercase
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    
    // Validate key
    if (key.length() != 16 || !isValidHex(key)) {
        cout << "Invalid key! Key must be exactly 16 hexadecimal characters." << endl;
        return 1;
    }
    
    // Generate round keys
    vector<string> round_keys = generate_keys(key);
    
    // Select operation
    cout << "\nSelect operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice (1/2): ";
    cin >> operation;
    
    if (operation != 1 && operation != 2) {
        cout << "Invalid operation choice!" << endl;
        return 1;
    }
    
    // Select input type
    cout << "\nSelect input type:" << endl;
    cout << "1. Plain text (string)" << endl;
    cout << "2. Hexadecimal" << endl;
    cout << "Enter choice (1/2): ";
    cin >> input_type;
    
    if (input_type != 1 && input_type != 2) {
        cout << "Invalid input type choice!" << endl;
        return 1;
    }
    
    // Clear input buffer
    cin.ignore();
    
    // Get input
    cout << "\nEnter input";
    if (input_type == 1) {
        cout << " (text): ";
        getline(cin, input);
        
        // Convert text to hex
        input = text2hex(input);
        cout << "Input in hexadecimal: " << input << endl;
    } else {
        cout << " (hexadecimal): ";
        getline(cin, input);
        
        // Convert input to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        // Validate hex input
        if (!isValidHex(input)) {
            cout << "Invalid hexadecimal input!" << endl;
            return 1;
        }
    }
    
    // Select output type
    cout << "\nSelect output type:" << endl;
    cout << "1. Text (if possible)" << endl;
    cout << "2. Hexadecimal" << endl;
    cout << "Enter choice (1/2): ";
    cin >> output_type;
    
    if (output_type != 1 && output_type != 2) {
        cout << "Invalid output type choice!" << endl;
        return 1;
    }
    
    // Process the message
    string result = process_message(input, round_keys, operation == 2);
    
    // Display result
    cout << "\nResult in hexadecimal: " << result << endl;
    
    // If output type is text, try to convert hex to text
    if (output_type == 1) {
        try {
            string text_result = hex2text(result);
            cout << "Result as text: " << text_result << endl;
        } catch (const exception& e) {
            cout << "Cannot convert result to text (not valid ASCII)." << endl;
        }
    }
    
    return 0;
}