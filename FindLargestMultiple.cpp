#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Node{
    struct Node * next;
    int data;
    Node(){}
};
//TODO in debug watch for hash collision handling and possible segfaults.

struct Map{
    int size; //same as the modulo we use for hashing.
    std::vector<Node> arr;
    bool lookup(int val){
    //REEEturns -1 for not found, index for is found.
        int hashedIndex = val%size;
        Node * head = &(arr.at(hashedIndex)); //We solve the header node for this lookup and receieve a chain starting at head.
        Node * current = head;
        while(current != NULL){
            if(val == current->data)
                return true;
            current = current->next;
        }
        return false;
    }
    bool insert(int val){
        int hashedIndex = val%size;
        Node* header = &(arr.at(hashedIndex));
        if(header == NULL){
            Node* createdHead = new Node();
            createdHead->next = NULL;
            arr[hashedIndex] = *createdHead;
        }
        if(header->next == NULL){ //Then we have no colission and also we have to create a header node here.
            Node* pointToAfterInsert = header->next;
            Node* newNode = new Node();
                newNode->data = val;
                newNode->next = NULL;
            header->next=newNode;
            return true;
        }
        //Reaching here implies hash collision because no NULL head.
        Node* pointToAfterInsert = header->next;
        Node* newNode = new Node();
            newNode->data = val;
            newNode->next = pointToAfterInsert;
        header->next=newNode;
        return false;
    }
};
//iterate nested across the map vector, for each multiply the values, hash the outcome, and lookup the result.  If we have it, store as new Largest.
//After nested for, print largest.
int main(){
ios::sync_with_stdio(false); //faster is better.
int mapCount;
std::cin>>mapCount; //Elements of hashmap
if(mapCount < 2){
    std::cout<<-1;
    return 0;
}
Map* map = new Map();
    map->size = mapCount;
    map->arr = std::vector<Node>(map->size);
//ONLY positive integers is specified in parameters.

int insertData;
for(int i=0; i<mapCount; i++){ //Populate the map.
    std::cin>>insertData;
    if(insertData <= 0){
        std::cout<<-1;
        return 0;
    }
    map->insert(insertData);
}
int largestValue = -1;
//TODO watch mapCount may differ from array size if we vary struct def.
for(int i=0; i<mapCount; i++){ //TODO watch null header nodes here.
    Node* comparator = &(map->arr.at(i));
    while(comparator != NULL){
        for(int j=0; j<mapCount; j++){ //Iterate nested across entire array.
                Node* current = &(map->arr.at(j));
                while(current != NULL){
                    int product = current->data * comparator->data;
                    if(product>largestValue && map->lookup(product)){ //Do lookup afterwards to save time.  product comparison is faster so don't waste time.
                            largestValue = product;
                    }
                    current = current->next;
                }
        }
        comparator = comparator->next;
    }
}
if(largestValue == 0){
    cout<<-1;
    return 0;
}
cout<<largestValue; //fin
}
