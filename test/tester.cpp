#include "tester.h"

void Tester::execute() {
    Mocker mocker;

    for (int j = 0; j < NUMBER_OF_TESTS; ++j) {
        unsigned int size = mocker.generateRandomInt(10);
        TraitsList<Integer> integers;
        TraitsList<Float> floats;

        for (int i = 0; i < size; ++i) {
            integers.insert(2 * i + 1);
            floats.insert(20.f / (i + 1.f) + 2.f);
        }

        ASSERT(isSorted(integers), "The integers list has problems");
        ASSERT(isSorted(floats), "The floats list has problems");

        for (int i = 0; i < 5; ++i) {
            integers.remove(2 * i + 1);
            floats.remove(20.f / (i + 1.f) + 2.f);
        }

        int newSize = size - 5;
        ASSERT(integers.size() == newSize, "The size function has problems");
        ASSERT(floats.size() == newSize, "The size function has problems");
        ASSERT(isSorted(integers), "The integers list has problems");
        ASSERT(isSorted(floats), "The floats list has problems");


        SelfList<int> list(SelfList<int>::Move);
        SelfList<int> list1(SelfList<int>::Count);
        SelfList<int> list2(SelfList<int>::Transpose);
        for(int i=0; i<size; ++i){
            list.insert(i);
        }
        ASSERT(list[0] == 0, "The insert function has problems");
        ASSERT(list.size() == size, "The size function has problems");
        list.remove(0);
        list.remove(1);
        list.remove(size-1);
        ASSERT(list[0] == 2, "The remove function has problems");
        ASSERT(list.size() == size-3, "The size function has problems");
        list1.merge(&list);
        list2.merge(&list);
        list.find(4);
        list.find(8);
        ASSERT(list[0] == 8, "The find function with Move method has problems");
        ASSERT(list[1] == 4, "The find function with Move method has problems");
        list1.find(4);
        list1.find(4);
        list1.find(3);
        list1.find(8);
        ASSERT(list1[0] == 4, "The find function with Count method has problems");
        ASSERT(list1[1] == 3, "The find function with Count method has problems");
        ASSERT(list1[2] == 8, "The find function with Count method has problems");
        list2.find(4);
        list2.find(8);
        ASSERT(list2[0] == 2, "The find function with Transpose method has problems");
        ASSERT(list2[1] == 4, "The find function with Transpose method has problems");
        ASSERT(list2[2] == 3, "The find function with Transpose method has problems");
        ASSERT(list2[5] == 8, "The find function with Transpose method has problems");
        ASSERT(list2[6] == 7, "The find function with Transpose method has problems");
        list2.find(4);
        ASSERT(list2[0] == 4, "The find function with Transpose method has problems");
        ASSERT(list2[1] == 2, "The find function with Transpose method has problems");
    }
}

template <typename T>
bool Tester::isSorted(TraitsList<T> &list) {
    for (int i = 1; i < list.size(); ++i) {
        if ((is_same<T, Integer>::value) && list[i - 1] > list[i]) {
            return false;
        } else if ((is_same<T, Float>::value) && list[i - 1] < list[i]) {
            return false;
        }
    }
    return true;
}