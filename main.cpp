#include <iostream>
#include <chrono>

using namespace std;

struct list {
    int data;
    list *head;
    list *tail;
};

list *createlist() {
    int key;
    cout << "Choose the type of creating list\n1 - Get random elements\n2 - Manual mode" << endl;
    while (!(cin >> key)) {
        cout << "Error!" << endl;
    }
    if (key == 1) {
        int length;
        cout << "Enter list size: " << endl;
        while (!(cin >> length)) {
            cout << "Error!" << endl;
        }
        auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        list *curr = 0, *next = 0;
        for (int i = 0; i < length; ++i) {
            curr = new list;
            curr->head = next;
            if (next) {
                next->tail = curr;
            }
            next = curr;
        }
        curr->tail = 0;
        list *beg = curr;
        while (beg) {
            beg->data = rand() % 100;
            beg = beg->head;
        }
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "\nDuration of creating list: " << end - start << "ns\n";
        return curr;
    }
    if (key == 2) {
        int value = 1;
        int length = 0;
        auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        list *curr = 0, *next = 0;
        while (value != 0) {
            cin >> value;
            if (value) {
                length += 1;
                curr = new list;
                curr->data = value;
                curr->tail = next;
                if (next) {
                    next->head = curr;
                }
                next = curr;
            }
        }
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "\nDuration of creating list: " << end - start << " nanoseconds1s\n";
        if (length){
            curr -> head = 0;
            while (curr->tail){
                curr = curr ->tail;
            }
            return curr;
        }
    } else {
        cout << "List is empty!" << endl;
        return 0;
    }
}

void printList(list *&beg) {
    list *curr = beg;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->head;
    }
}

int lenList(list *&beg){
    list *Curr = beg;
    int i = 0;
    while(Curr){
        ++i;
        Curr= Curr->head;
    }
    return i;
}

void delList ( list *&beg ){
    list *Next;
    while(beg)
    {
        Next = beg->head;
        delete beg;
        beg = Next;
    }
}

list *getId(list *&beg, int id){
    while (beg && (id--)) {
        beg = beg->head;
    }
    return beg;
}

void delValue (list *&beg){
    int id;
    list *curr = beg;
    cout << "Enter id of delete value:" << endl;
    while (!(cin >> id)){
        cout << "Invalid input" << endl;
    }
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    list *value;
    if (!id){
        value = beg -> head;
        delete beg;
        beg = value;
        beg -> tail = 0;
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Duration of deliting value: " << end - start << " nanoseconds" << endl;
        return;
    }
    value = getId(curr, id-1);
    curr = beg;
    list *dvalue = value -> head;
    if (dvalue -> head){
        value -> head = dvalue -> head;
        value -> head -> tail = value;
        delete dvalue;
    }
    else{
        value -> head = 0;
        delete dvalue;
    }
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "Duration of deliting value: " << end - start << " nanoseconds" << endl;
}

void getVal(list *&beg){
    int key;
    cout << "1 - get item by id\n2 - get item by value" << endl;
    while (!(cin >> key)){
        cout << "Invalid input" << endl;
    }
    if (key == 1){
        auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int id;
        cout << "Enter id: " << endl;
        while (!(cin >> id)){
            cout << "Invalid input" << endl;
        }
        list *curr = beg;
        cout << "The number at the given index: " << getId(curr, id) -> data << endl;
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Duration of search item: " << end - start << " nanoseconds" << endl;
    }
    if (key == 2){
        auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Enter value: " << endl;
        int value;
        while (!(cin >> value)){
            cout << "Invalid input" << endl;
        }
        list *curr = beg;
        bool correct = false;
        while (curr){
            if (curr -> data == value){
                cout << "The number at the given value: " << curr -> data << endl;
                correct = true;
            }
            curr = curr -> head;
        }
        if (!correct){
            cout <<"Item <<" << value << ">> wasn't founded";
        }
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Duration of search item: " << end - start << " nanoseconds" << endl;
    }
}

void insertVal (list *&beg){
    list *curr = beg;
    int value, id;
    cout << "Enter value to insert: " << endl;
    while (!(cin >> value)){
        cout << "Invalid input" << endl;
    }
    cout << "Choose position for <<" << value << ">>" << endl;
    while (!(cin >> id)){
        cout << "Invalid input" << endl;
    }
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    list *item = new list;
    item->data = value;
    curr = beg;
    if (id == 1){
        beg -> tail = item;
        item -> tail = 0;
        item -> head = beg;
        beg = item;
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Duration of insert item: " << end - start << " nanoseconds" << endl;
        return;
    }
    if (id == lenList(curr)){
        item -> head = 0;
        list *litem = getId (curr, id - 1);
        item -> tail = litem;
        litem -> head = item;
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "Duration of insert item: " << end - start << " nanoseconds" << endl;
        return;
    }
    list* litem = getId(curr, id - 2);
    item -> tail = litem;
    item -> head = litem -> head;
    item -> head -> tail = item;
    litem -> head = item;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "Duration of insert item: " << end - start << " nanoseconds" << endl;
    return;
}

void swapItem (list *&beg){
    int leftid, rightid;
    cout << "Enter left id to swap item:" << endl;
    while (!(cin >> leftid)){
        cout << "Invalid input" << endl;
    }
    cout << "Enter right id to swap item:" << endl;
    while (!(cin >> rightid)){
        cout << "Invalid input" << endl;
    }
    list *curr = beg;
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    list *leftitem = getId(curr, leftid);
    curr = beg;
    list *rightitem = getId(curr, rightid);
    curr = beg;
    if (leftitem -> tail){
        leftitem -> tail -> head = rightitem;
    }
    else {beg = rightitem;}
    if (rightid-leftid!=1){
        leftitem -> head -> tail = rightitem;
        rightitem -> tail -> head = leftitem;
    }
    if (rightitem -> head) {
        rightitem -> head -> tail = leftitem;
    }
    if (rightid-leftid == 1){
        rightitem -> tail = leftitem -> tail;
        leftitem -> tail = rightitem;
        leftitem -> head = rightitem -> head;
        rightitem -> head = leftitem;
        return;
    }
    list *buffer  = leftitem -> tail;
    leftitem -> tail = rightitem -> tail;
    rightitem -> tail = buffer;
    buffer = leftitem -> head;
    leftitem -> head = rightitem -> head;
    rightitem -> head = buffer;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "Duration of insert item: " << end - start << " nanoseconds" << endl;
}

int* createArray(){
    int size;
    cout << "\nEnter size of array for comparsion:";
    cin >> size;
    int  *arr = (int *)malloc(size * sizeof(int));
    for (int *i = arr; i < arr + size;i++){
        *i = rand()%100;
    }
    return arr;
}
void printArray(int* arr,int size){
    for (int *i = arr; i < arr + size;i++){
        cout << *i << " ";
    }
}

/*void IDZ(list *&beg, int*arr,int size){
    int value;
    cout << "Enter value for any even-numbered item:" << endl;
    while(!(cin >> value)){
        cout << "\nInvalid input\n";
    }
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    for (int *i = arr,g=0; i < arr + size; i++, g++){
        if (g%2==0){
            *i -= value;
        }
        else{
            *i -=
        }
    }
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "\nDuration of operation in dynamic array: " << end - start << " nanoseconds" << endl;
    printArray(arr,size);
    list *curr = beg;
    int i = 0;
    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(curr){
        if(i%2==0){
            curr->data -= value;
        }

        i++;
    }
    curr = beg;
    printList(curr);
    delete [] arr;
    delList(beg);
}*/

int main() {
    int key;
    list *List = 0;
    list *curr = List;
    list *beg = List;
    while (true) {
        cout << "\nChoose the command:\n1 - Create list\n2 - Print list\n3 - Add new item\n4 - Get item\n5 - Swap items\n6 - Delete item\n0 - Exit\n";
        cin >> key;
        if (!key){
            delList(curr);
            return 0;
        }
        if (key == 1){
            List = createlist();
            curr = List;
            printList(curr);
        }
        else if (List) {
            switch(key){
                case 2:
                    printList(curr);
                    break;
                case 3:
                    insertVal(curr);
                    printList(curr);
                    break;
                case 4:
                    getVal(curr);
                    break;
                case 5:
                    swapItem(curr);
                    printList(curr);
                    break;
                case 6:
                    delValue(curr);
                    printList(curr);
                    break;
                /*case 7:
                    int *arr = createArray();
                    list *Llist = 0;
                    Llist = createlist();
                    list *Curr = Llist;
                    list *Beg = Llist;
                    printArray(arr, lenList(beg));
                    beg = Llist;
                    printList(curr);
                    IDZ(Curr, arr, lenList(Beg));
                    Beg = Llist;
                    break;*/
            }
        }
        else {
            cout << "Error, the list is empty!" << endl;
        }
    }
}