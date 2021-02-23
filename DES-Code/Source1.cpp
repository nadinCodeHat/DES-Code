#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <unordered_map>
using namespace std;

//Plain Text
string plain_text;
// Array to hold 16 keys
string round_keys[16];

//Convert Hexadecimal to Binary
string hex_to_binary(string hexa) {
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
    string binary_string = "";
    for (int i = 0; i < hexa.size(); i++) {
        binary_string += mp[hexa[i]];
    }
    return binary_string;
}

//Convert Decimal to Binary
string Decimal_To_Binary(int decimal)
{
	string binary;
	while (decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary;
		decimal = decimal / 2;
	}
	while (binary.length() < 4) {
		binary = "0" + binary;
	}
	return binary;
}
//Convert Binary to Decimal
int Binary_To_Decimal(string binary)
{
	int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for (int i = size - 1; i >= 0; i--)
	{
		if (binary[i] == '1') {
			decimal += pow(2, counter);
		}
		counter++;
	}
	return decimal;
}
// Left circular shift by 2
string shift_left_twice(string key_chunk, int shifts) {
    string shifted = "";
    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < 28; j++) {
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk = shifted;
        shifted = "";
    }
    return key_chunk;
}

//Compute xor between two strings
string Xor(string a, string b) {
    string result = "";
    int size = b.size();
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            result += "1";
        }
        else {
            result += "0";
        }
    }
    return result;
}

string permute(string k, int* arr, int n)
{
	string per = "";
	for (int i = 0; i < n; i++) {
		per += k[arr[i] - 1];
	}
	return per;
}

//DES Encryption
string perfromEncryption() {
	//Initial Permutation Table 
	int initial_permutation[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
	};
	//Expansion D-box Table
	int expansion_table[48] = {
	32,1,2,3,4,5,4,5,
	6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,
	28,29,28,29,30,31,32,1
	};
	//Subition Box(S-Box) Table
	int substition_boxes[8][4][16] =
	{ {
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	},
	{
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	},
	{
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
	},
	{
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
	},
	{
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
	},
	{
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
	},
	{
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
	},
	{
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
	} };
	//Straight Permutation Table
	int straight_permutation[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};
	//Inverse Permutation or Final Permutation table
	int inverse_permutation[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};

	//Initial Permutation
	plain_text = permute(plain_text, initial_permutation, 64);

	//Split into two equal halves
	string left = plain_text.substr(0, 32);
	string right = plain_text.substr(32, 32);

	//Plain text encrypted 16 times
	for (int i = 0; i < 16; i++) {
		string right_expanded = "";
		//right half expanded(Expansion D-Box Table)
		right_expanded = permute(right, expansion_table, 48);

		//Result is xored with a key
		string xored = Xor(round_keys[i], right_expanded);
		string res = "";
		//Divide result to 8 equal parts and pass through 8 subtitution boxes.
		for (int i = 0; i < 8; i++) {
			string row1 = xored.substr(i * 6, 1) + xored.substr(i * 6 + 5, 1);
			int row = Binary_To_Decimal(row1);
			string col1 = xored.substr(i * 6 + 1, 1) + xored.substr(i * 6 + 2, 1) + xored.substr(i * 6 + 3, 1) + xored.substr(i * 6 + 4, 1);;
			int col = Binary_To_Decimal(col1);
			int val = substition_boxes[i][row][col];
			res += Decimal_To_Binary(val);
		}
		//2nd permutation
		string perm2 = "";
		perm2 = permute(res, straight_permutation, 32);

		//Result is xored with the left half
		xored = Xor(perm2, left);
		left = xored;
		if (i < 15) {
			swap(left, right);
		}
	}
	//Combine plain text halves
	string combined_text = left + right;
	string ciphertext = "";
	//Inverse Permutation or Final Permutation table
	ciphertext = permute(combined_text, inverse_permutation, 64);
	return ciphertext;
}

//Generate 16 keys using the 64-bit key
void generate_keys(string key) {
    //Permuted Choice 1 table
    //To generate 56-bit key from 64-bit
    int pc1Table[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
    };
    //Permuted Choice 2 table
    //To generate 48-bit 16 subkeys each
    // The PC2 table
    int pc2Table[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
    };
    // Number of bit shifts 
    int shift_table[16] = 
    { 1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1 
    };

    //Compress key to 56-bit using Permutes Choice 1 table (56)
    string perm_key = "";
	perm_key = permute(key, pc1Table, 56);

    //Spllit the keys to equal halves
    string left = perm_key.substr(0, 28);
    string right = perm_key.substr(28, 28);

    for (int i = 0; i < 16; i++) {
		
		//Shift
		left = shift_left_twice(left,shift_table[i]);
		right = shift_left_twice(right, shift_table[i]);

		// Combining the two chunks
		string combined_key = left + right;
		string round_key = "";
		// Finally, using the Permuted Choice 2 table to transpose the key bits
		round_key = permute(combined_key, pc2Table, 48);

		round_keys[i] = round_key;
	}
}

int main(){
    //64-bit block of plain text in hexadecimal
	plain_text = "0123456789ABCDEF"; 

    //Convert 64-bit hexadecimal plain text to binary
    plain_text = hex_to_binary(plain_text);

	//64-bit key in hexadecimal
    string key = "AABB09182736CCDD";

    //Convert 64-bit hexadecimal key to binary
    key = hex_to_binary(key);

    //Generate 16 keys using the 64-bit key
    generate_keys(key);

	cout << "Plain Text: " + plain_text << endl;
	//Encrypt
	string cipher_text = perfromEncryption();
	cout << "Cipher Text: " + cipher_text << endl;
}