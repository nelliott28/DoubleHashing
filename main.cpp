#include <iostream>

using namespace std;

string Hash(string key){
    //MAIN VARIABLES
    string hashVal; //Final Hash Value Variable
    // !!! NOTE: 32-Bit MIN. REQUIRED !!! //
    const int BIT_HASH = 256; //Number of bits for hash output (CHANGE THIS DEPENDING ON DESIRED BIT OUTPUT) 
    int digitLength = BIT_HASH / 4; //Convert to num of characters in hash

    //SEED VALUE - Helps with creating large numbers
    string seedStr = key.substr(0, 3);
    unsigned long long int seedVal = 1;
    for (int i = 0; i < key.length(); i++){
        seedVal *= key[i];
    }
    
    //HASH ALGORITHM
    int count = 1;
    //While loop creates a key of (bit_size / 4) ^ 2 with seeded values where needed
    while (key.length() < digitLength * digitLength){
        count = key.length() + count;
        key.push_back(((seedVal * count) % 90) + 33);
        count++;
    }

    string tempKey;
    unsigned long long int tempVal = 1;
    //for loop breaks key up into sections and creates combined multiplicative hashes which are then assigned to a fix hash
    for (int i = 1; i < key.length() / digitLength; i++){
        tempKey = key.substr(key.length() % (digitLength * i), digitLength);
        for (int j = 0; j < tempKey.length(); j++){
            tempVal *= tempKey[j];
        }
        tempVal = tempVal * seedVal * tempKey[i] * key[key.length() % i];
        tempVal = (tempVal % 90) + 33;

        hashVal += tempVal;
    }
    //END HASH ALGORITHM

    return hashVal;
}

int main(){
    
    string sample = ""; //MAX 32 CHARACTERS
    cout << "ORIGINAL: " << sample << endl;
    cout << "HASH: " << Hash(sample) << endl;

    return 0;
}