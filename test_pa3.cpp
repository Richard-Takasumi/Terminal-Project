#include <iostream>
#include "file_sys.h"

using namespace std;

struct node {
    int data;
    node* next = nullptr;
};


void fun(bool z) {
    if (z == true) {
        cout << "hi" << endl;
    }
    
}

int main () {
    int x = 0;
    fun(x == 0);

}