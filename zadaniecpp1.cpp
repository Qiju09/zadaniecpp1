#include <iostream>
#include <new>

using namespace std;

void swap(void* el1,void* el2, size_t size) {
	try {
		char* temp = new char[size];
		memcpy(temp, el1, size);
		memcpy(el1, el2, size);
		memcpy(el2, temp, size);
		delete[] temp;
	}
	catch (const bad_alloc& e) {
		cerr << "Memory allocation failed: " << e.what() << endl;
	}
}

void my_qsort(void* base, size_t count, size_t size, int(*comp)(void* el1, void* el2)) {
    if (count < 2)return;
    char* b = static_cast<char*>(base);
    size_t current = 0;
    for (size_t i{ 1 };i < count;i++) {
        if (*(b + i * size) < *b) {
			swap(b + i * size, b+(++current)*size, size);
        }
    }
	swap(b, b+current*size, size);
    if (current > 0) {
		my_qsort(b, current, size, comp);
    }
    if (count > current) {
        my_qsort(b + (current+1)*size, count - current - 1 , size, comp);
    }

}

int f_sortint(void* el1, void* el2) {
    return static_cast<int*>(el1) - static_cast<int*>(el2);
}

int main()
{
    int num[7]{ 3,4,22,5,15,9,0 };
    for (int el : num) {
        cout << el << ' ';
    }
    cout << endl;
    my_qsort(&num, size(num), sizeof(int), f_sortint);
    for (int el : num) {
        cout << el << ' ';
    }
}