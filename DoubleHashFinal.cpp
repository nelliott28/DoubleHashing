#include<iostream>
#include<list>

using namespace std;

class UserList{
    private:
        static const int memory = 20;
        string listing[memory][2];
        int listingLen = sizeof(listing)/sizeof(listing[0]);

    public:
        //HASH FUNCTIONS
        int ProdAddHash(string key){
            int hashVal = 0;
            for (int i = 1; i < key.length() + 1; i++){
                hashVal += key[i] * i;
            }
            return hashVal;
        }
        int ComplexHash(string key, int mod, int add){
            //MAIN VARIABLES
            string hashVal; //Final Hash Value Variable
            // !!! NOTE: 32-Bit MIN. REQUIRED !!! //
            const int BIT_HASH = 32; //Number of bits for hash output (CHANGE THIS DEPENDING ON DESIRED BIT OUTPUT) 
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
                key.push_back(((seedVal * count) % mod) + add);
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
                tempVal = (tempVal % mod) + add;

                hashVal += tempVal;
            }
            //END HASH ALGORITHM

            return (stoi(hashVal) + ProdAddHash(key)) % memory;
        }

        void addContact(string username, string name){
            int hashVal = ComplexHash(username, 10, 48);

            for (int i = 0; i < listingLen - hashVal; i++){
                auto cell = listing[hashVal];
                if (cell[0] != ""){
                    hashVal = hashVal + 1;
                    continue;
                }
                else{
                    listing[hashVal][0] = username;
                    listing[hashVal][1] = name;
                    break;
                }
            }
        }

        void deleteContact(string username){
            int hashVal = ComplexHash(username, 10, 48);
            bool isNameExists = false;

            for (int i = 0; i < listingLen - hashVal; i++){
                auto cell = listing[hashVal];
                if (cell[0] != username){
                    hashVal = hashVal + 1;
                    continue;
                }
                else{
                    listing[hashVal][0] = "";
                    listing[hashVal][1] = "";
                    cout << "Contact \"" << username << "\" Removed" << endl;
                    return;
                }
            }
            if (!isNameExists){
                cout << "Contact \"" << username << "\" Not Found" << endl;
                return;
            }
        }

        void displayPhonebook(){
            for(int i = 0; i < listingLen; i++){
                if (listing[i][0] != ""){
                    cout << i << ". USERNAME: " << listing[i][0] << " - " << "\t NAME: " << listing[i][1] << endl;
                }
            }
        }

        void searchContact(string username) {
            int hashVal = ComplexHash(username, 10, 48);
            bool isNameExists = false;

            for (int i = 0; i < listingLen; i++){
                auto cell = listing[hashVal];
                if (cell[0] != username){
                    hashVal = hashVal + 1;
                    continue;
                }
                else{
                    isNameExists = true;
                    cout << "USER FOUND: " << listing[hashVal][1] << " registered as " << listing[hashVal][0] << endl;
                    return;
                }
            }
            if (!isNameExists){
                cout << "User Not Found - Please Try Again" << endl;
            }
        }

        bool isEmpty() {
            for (int i = 0; i < listingLen; i++) {
                if (listing[i][0] != "") {
                    return false;
                }
            }
            return true;
        }
};

using namespace std;

int main(){

    UserList Users;

    Users.addContact("happycamper123", "Nicholas");
    Users.addContact("jollyfello111", "Grayson");
    Users.addContact("timothy101", "James");
    Users.addContact("jackrabbit69", "Samantha");
    Users.addContact("hokeypokey669", "Brady");
    Users.addContact("goldtrigger432", "Julia");
    Users.addContact("tinyMouse33", "Grace");
    Users.addContact("maggiemachineMnM", "Kate");
    Users.addContact("partyhard1", "Blake");
    Users.addContact("tnt4nowrockU", "Tim");

    Users.displayPhonebook();

    Users.deleteContact("goldtrigger432");
    Users.deleteContact("grasshopper432");

    Users.displayPhonebook();
    Users.searchContact("random101er");
    Users.searchContact("jollyfello111");

    cout << "IS EMPTY?: " << Users.isEmpty() << endl;

    return 0;
}