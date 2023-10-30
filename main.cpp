#include <iostream>
#include <random>

using namespace std;

//Linked List Structure
struct Node{
    string data;
    Node *node;
};
class linkedList{
    Node* head;

    public:
        linkedList(){
            head = NULL;
        }
        void insert(string val){
            Node* newNode = new Node;
            newNode->data = val;
            newNode->node = NULL;

            if (head == NULL){
                head = newNode;
            }
            else{
                newNode->node = head;
                head = newNode;
            }
        }
        void display(){
            Node* tempHead = head;
            while(tempHead != NULL){
                cout << tempHead->data << endl;
                tempHead = tempHead->node;
            }
        }
        bool search(string n){
            Node* tempHead = head;
            bool isFound = false;

            while(tempHead != NULL){
                if (tempHead->data == n){
                    isFound = true;
                    break;
                }
                tempHead = tempHead->node;
            }

            return isFound;
        }
        void erase(string val){
            if (head->data == val){
                delete head;
                head = head->node;
                return;
            }
            else if (head->node == NULL){
                if (head->data == val){
                    delete head;
                    head = NULL;
                    return;
                }

                cout << "Couldn't find data." << endl;
            }
            else{
                Node* temp = head;
                while(temp->node != NULL){
                    if (temp->node->data == val){
                        Node* tempPtr = temp->node->node;
                        delete temp->node;
                        temp->node = tempPtr;
                        return;
                    }
                    temp = temp->node;
                }
            }
        }
        linkedList merge(linkedList B){
            linkedList tempList;
            Node* tempA = head; Node* tempB = B.head;
            while (tempB != NULL){
                tempList.insert(tempB->data);
                tempB = tempB->node;
            }
            while (tempA != NULL){
                tempList.insert(tempA->data);
                tempA = tempA->node;
            }
            *this = tempList;
            return *this;
        }
};

//HASH FUNC.
string DoubleHash(string key, bool isDHash){
    //MAIN VARIABLES
    string hashVal; //Final Hash Value Variable
    // !!! NOTE: 32-Bit MIN. REQUIRED !!! //
    const int BIT_HASH = 64; //Number of bits for hash output (CHANGE THIS DEPENDING ON DESIRED BIT OUTPUT) 
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

    //Check for Double Hash
    if (isDHash == true){
        return DoubleHash(key + hashVal, false);
    }

    return hashVal;
}

int main(){

    linkedList hashTable[100];
    string strArray[20] = {
        "Hello123",
        "World456",
        "Random789",
        "CPlusPlus",
        "Hardcoded1",
        "Example2",
        "OpenAI123",
        "Array456",
        "Programming",
        "RandomString",
        "Demo678",
        "GPT-3.5",
        "LanguageModel",
        "Coding101",
        "StringArray",
        "Generate987",
        "ThisIsFun",
        "LearningC++",
        "ArrayOfStrings",
        "StackOverflow"
    };

    for (int i = 0; i < sizeof(strArray) / sizeof(strArray[0]); i++){
        hashTable->insert(DoubleHash(strArray[i], true));
    }
    cout << "----- HASH TABLE -----" << endl;
    hashTable->display();

    return 0;
}