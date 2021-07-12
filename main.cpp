#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
//note: The performance evalutation answers are at the bottom

class node{
public:
    long long int data;
    node* next;
    node(long long int item):data(item), next(nullptr){}

};

node* get_node(long long int item);

class hash_table{
private:
    node** hash_list;  //the array of hash table
    int num_buckets;
public:
    int hash_fun;  //1. Folding, 2.Truncation, 3.Middle Square
    hash_table(int N);
    void insert_key(long long int key);
    void delete_key(long long int key);
    bool search_key(long long int key);
    void print_list();
    Hash(long long int key);


};


int main()
{

    int op,N,fun,n2;
    long long int key;
    hash_table* tab;
        while(true){
             cout<<"Operations:\n1. Initialize Hash Table\n2. Load T.C. ID Numbers from file\n3. Add new T.C. ID Number\n4. Delete a T.C. ID Number\n5. Search for a T.C. ID Number\n6. Print out Hash Table\n7. Exit"<<endl;
            cin>>op;    //op holds the chosen operation
            switch(op){
                case 1:{
                    cout<<"Enter the size of the hash table:"<<endl;
                    cin>>N;
                    tab= new hash_table(N);            //create the hash table with the desired size
                    cout<<"Choose the hash function to be used:\n1. Folding\n2. Truncation\n3. Middle Square"<<endl;
                    cin>>fun;
                    tab->hash_fun=fun;               //set the hashing function based on the input
                    break;
                }
                case 2:{
                       cout<<"Enter the number of ID's to be added"<<endl;       //load ID2's from file as many as desired and add to the hash table
                       cin>>n2;
                        long long int x;
                        int cnt=0;
                        ifstream inFile;
                        inFile.open("hash_table_init.txt");
                        if (!inFile) {
                            cout << "Unable to open file";
                            exit(1); // terminate with error
                        }

                        while (inFile >> x&&cnt<n2) {
                            tab->insert_key(x);
                            cnt++;
                        }
                    break;}
                case 3:{
                    cout<<"Please enter the TC ID to be added"<<endl;
                    cin>>key;
                    tab->insert_key(key);
                    break;}
                case 4:{
                    cout<<"Please enter the TC ID to be deleted"<<endl;
                    cin>>key;
                    tab->delete_key(key);
                    break;}
                case 5:{
                    cout<<"Please enter the TC ID to be searched"<<endl;
                    cin>>key;
                    if(tab->search_key(key))
                        cout<<"The ID exists in the list"<<endl;
                    else
                        cout<<"The ID is not in the list"<<endl;
                    break;}
                case 6:{
                    cout<<"The hash table:"<< endl<<endl;
                    tab->print_list();
                    break;}
                case 7:{exit(1); break;}
                default:{
                    cout<<"Enter a valid number"<<endl;
                    break;}
            }
        }

    return 0;
}

hash_table::hash_table(int N){   //constrcutor of the hash table
    hash_list= new node*[N];      //construct the table with the desired size
    num_buckets=N;       //table size stored to ease some operations
    for(int i=0;i<N;i++)
        hash_list[i]=nullptr;     //set all the elements to null initially
}

void hash_table::insert_key(long long int key){
    if(search_key(key)){
        cout<<"The ID is already in the list and cannot be readded"<<endl;
        return;}
    int hash_value=Hash(key);               //get the corresponding hash value
    node* temp=get_node(key);
    if(hash_list[hash_value]==nullptr)  //if the bucket is empty, put the key in it
        hash_list[hash_value]=temp;
    else{
        temp->next=hash_list[hash_value];  //if the bucket is not empty insert the key to the linked list
        hash_list[hash_value]=temp;}


}

void hash_table::print_list(){ //prints the hash table in a readable form
    node* temp;         //pointer for linked list traversal
    for(int i=0;i<num_buckets;i++){
        if(hash_list[i]!=nullptr){
            temp=hash_list[i];
            cout<<i<<". ";
            while(temp!=nullptr){        //if there is an element print it and the next ones in the chain until the chain ends
                if(temp->data==15)     //data=15 is a mark for a bucket that has a key deleted before
                    cout<<"d ";      //write d if the bucket is marked as deleted
                else
                    cout<<temp->data<<" ";
                temp=temp->next;
            }
        }
        else
            cout<<i<<". e";          //write empty if the bucket is never written a key before
        cout<<endl;
    }
}

void hash_table::delete_key(long long int key){  //deletes a key from the table
    if(!search_key(key)){
        cout<<"Key is not in the hash table"<<endl;
        return;}

    int hash_value=Hash(key);                //get the corresponding hash value to find the key
    node *temp=hash_list[hash_value];       //pointers to help the deleting from the linked list
    node *prev;                             //
    if(temp->data==key&&temp->next==nullptr){ //mark the bucket as d after deletion if there is only one key inside
        hash_list[hash_value]->data=15;
        return;}

    while(temp!=nullptr){                          //remove the corresponding node from the linked list to delete the key
        if(temp->data==key&&temp==hash_list[hash_value]){
            hash_list[hash_value]=temp->next;
            return;}
        else if(temp->data==key){
            prev->next=temp->next;
            //delete temp
            return;}
        prev=temp;
        temp=temp->next;
    }

}

bool hash_table::search_key(long long int key){
    int hash_value=Hash(key);     //first obtain the hash value
    node* temp= hash_list[hash_value];  //traversal pointer
    while(temp!=nullptr){
        if(temp->data==key)    //return true if the key is found
            return true;
        else
            temp=temp->next;  //traverse thorugh the chain if the key is still not found
    }
    return false;
}

node* get_node(long long int item){   //returns a node pointer with desired properties
 node* new_node=new node(item);
 return new_node;
}

 int hash_table::Hash(long long int key){  //contains all three hash functions
    if(hash_fun==1){
        int p1,p2,p3,p4; //four partitions for a 11 digit number, p4 is 2 digits and the rest are 3 digits
        p1=key%100;
        p2=(key%100000-p1)/100;
        p3=(key%100000000-key%100000)/100000;
        p4=(key%100000000000-key%100000000)/100000000;
        return(p1+p2+p3+p4)%100;         //return the sum of partitions mode 100
    }
    if(hash_fun==2){
        int mid;
        mid=(key%10000000-key%10000)/10000; //obtain the middle value
        mid=mid*mid;
        return mid%100;
    }

    if(hash_fun==3)
    return key%100;
 }


 //Loading factor for all hash functions is lf=200/100=2
 //Number of collisions for folding is 115
 // Number of collisions for truncation is 178
 //Number of collisions for middle square is 113

 //Truncation is the worst hash function among the three. It causes a lot of accumulation in a bucket. It has a lot of collisions. Apparently it can't generate hash values with high variance
//Folding and middle square methods are both better than truncation, but show similar performance compared to each other.
