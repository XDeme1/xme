CreateTest(aligned_data 20)
CreateTest(array_view 20)
CreateTest(array 20)
CreateTest(heap 20)
CreateTest(linked_list 20)
CreateTest(pair 20)
CreateTest(spsc 20)
CreateTest(tuple 20)

add_unittest(ContainerTest
    icontainer.cpp)