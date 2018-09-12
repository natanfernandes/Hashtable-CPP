#include<iostream>
using namespace std;

//GENERIC TYPES FOR BUCKETS
template<typename K, typename V>

//BUCKET CLASS
class bucket{
    public:
    V value;
    K key;

    bucket(K key, V value){
        this->value = value;
        this->key = key;
    }
};

//GENERIC TYPE FOR HASH
template<typename K, typename V>

//HASH CLASS
class Hash{
    //USING BUCKET ARRAY
    bucket<K,V> **arr;
    int capacity;
    int size;

    //MARK DELETED BUCKETS
    bucket<K,V> *deleted;

    public:
    Hash(){

        capacity = 10;
        size=0;
        arr = new bucket<K,V>*[capacity];

        for(int i=0 ; i < capacity ; i++)
            arr[i] = NULL;

        deleted = new bucket<K,V>(-1, -1);
    }
    //RETURN THE INDEX OF HASH
    int idx(K key){
        return key % capacity;
    }

    //INSERT ELEMENTS
    void insertBucket(K key, V value){
        bucket<K,V> *temp = new bucket<K,V>(key, value);

        int hashIndex = idx(key);

        while(arr[hashIndex] != NULL && arr[hashIndex]->key != key
               && arr[hashIndex]->key != -1){
            hashIndex++;
            hashIndex %= capacity;
        }

        if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1){
            size++;
            cout << "Inseriu!"<<endl;
        }
        arr[hashIndex] = temp;
    }

    //DELETE A ELEMENT
    V deleteBucket(int key){
        int hashIndex = idx(key);

        while(arr[hashIndex] != NULL){
            if(arr[hashIndex]->key == key){
                bucket<K,V> *temp = arr[hashIndex];
                arr[hashIndex] = deleted;
                size--;
                cout << "Deletou!"<<endl;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }

    //SEARCH A ELEMENT BY THE KEY
    V searchBucket(int key){
        int hashIndex = idx(key);

        while(arr[hashIndex] != NULL){
            if(arr[hashIndex]->key == key){
                cout << "Achou o value = "<< arr[hashIndex]->value << " na key = " << key <<endl;
                return arr[hashIndex]->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        cout << "Não achado!" << endl;
        return NULL;
    }

    //RETURN SIZE
    int sizeOf(){
        return size;
    }

    //RETURN FALSE IF EMPTY OR TRUE IF NOT EMPTY
    bool isEmpty(){
        return size == 0;
    }

    //SHOW ELEMENTS OF THE HASH
    void showElements(){
        for(int i=0 ; i<capacity ; i++){
            if(arr[i] != NULL && arr[i]->key != -1){
                cout << "Key = " << arr[i]->key
                     <<" e Value = "<< arr[i]->value << endl;
            }
        }
    }
};

//APPLYING TESTS
int main(){
    Hash<int, int> *h = new Hash<int, int>;
    h->insertBucket(1,1);
    h->insertBucket(2,2);
    h->insertBucket(2,3);
    h->showElements();
    h->searchBucket(2);
    h->deleteBucket(2);
    h->searchBucket(2);


    return 0;
}
