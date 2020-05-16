// File: test_Dlist.cpp
// Author: Juntao Wang & Nam Pham
// Data: April 19, 2018

#include "Dlist.h"
using namespace std;
#include <cassert>
void testCon()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  List<double> L2;
  List<string> L3;
  List<long> L4;
  List<int> L5(L1);
}

void testAdd()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);

}

void testSize()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  assert (L1.size() == 4);

  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");
  assert (list1.size() == 5); //test size


  List <double> list2;
  list2.add(0.44571);
  list2.add(-1.4451);
  list2.add(7884.4412);
  list2.add(-89.3354);
  list2.add(0);
  list2.add(-0.3347);
  assert (list2.size() == 6); //test size

}

void testFind()
{
  List<int> list;
  list.add(1);
  list.add(22);
  list.add(0);
  list.add(-32);
  assert (list.index(1)==0);
  assert (list.index(22)==1);
  assert (list.index(0)==2);
  assert (list.index(-32)==3);
  assert (list.index (3) == -1); //test for item not in list

  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");
  assert (list1.index("hello")==0);
  assert (list1.index("zzs")==1);
  assert (list1.index("default")==2);
  assert (list1.index("o")==3);
  assert (list1.index("1")==4);
  assert (list1.index("cs173") == -1);


  List <double> list2;
  list2.add(0.44571);
  list2.add(-1.4451);
  list2.add(7884.4412);
  list2.add(-89.3354);
  list2.add(0);
  list2.add(-0.3347);
  assert (list2.index(0.44571)==0);
  assert (list2.index(-1.4451)==1);
  assert (list2.index(7884.4412)==2);
  assert (list2.index(-89.3354)==3);
  assert (list2.index(0)==4);
  assert (list2.index(-0.3347)==5);
  assert (list2.index(-1)==-1);

}

void testInsertion()
{
  List<int> list;
  list.add(1);
  list.add(22);
  list.add(0);
  list.add(-32);

  list.insert(2,55);
  assert (list.index(55)==2); //insert at middle

  list.insert(0,83); //insert at head
  assert (list.index(83)==0);

  list.insert(5,71); //insert at tail
  assert (list.index(71)==5);

  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");

  list1.insert(3, "dog");
  assert (list1.index("dog") == 3);

  list1.insert(0, "cat");
  assert (list1.index("cat")==0);

  list1.insert(6, "cow");
  assert (list1.index("cow")==6);



  }

void testOperator()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  L1.add(9);
  L1.add(11);
  L1.add(13);
  L1.add(15);
  assert (L1[0]==1);
  assert (L1[7]==15);
  assert (L1[2]==5);
  assert (L1[5]==11); //test index
  List<int> L2;


  L2 = L2; //test assigment
  L2 = L1;
  assert ((L2[1] == L1[1]) && (L2[2] == L2[2]));
  //assert ()
  L2+=L2; //test +=
  cout << L2 << endl;
}

void testInsert()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  cout << L1 << endl;

  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");
  cout << list1 << endl;

}

void testRemove()
{
  List<int> L1;
  L1.add(1);
  L1.add(2);
  L1.add(3);
  L1.add(4);
  L1.add(5);
  L1.add(6);
  L1.add(7);
  L1.add(8);
  L1.remove(0);
  assert (L1.index(2) == 0);

  L1.remove(4);
  assert (L1.index(5)==3);

  L1.remove(5);
  assert (L1.index(7)==4);

  L1.remove(1);
  assert (L1.index(4)==1);

  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");

  list1.remove(0);
  assert (list1.index("zzs") == 0);

  L1.remove(1);
  assert (list1.index("default")==1);



}

void testDestruct()
{
  List<int> L1;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  L1.add(9);
  L1.add(11);
  L1.add(13);
  L1.add(15);
  L1.~List();
  cout << L1 << endl;
  assert(L1.size()==0);


  List<string> list1;
  list1.add("hello");
  list1.add("zzs");
  list1.add("default");
  list1.add("o");
  list1.add("1");
  list1.~List();
  assert(list1.size()==0);
  assert(L1.size()==0);
}

void testCopy()
{
  List<int> L1;
  List<int> L2;
  L1.add(1);
  L1.add(3);
  L1.add(5);
  L1.add(7);
  L1.add(9);
  L1.add(11);
  L1.add(13);
  L1.add(15);
  //L2.deepCopy(L1);
  cout << L2 << endl;
}

int main()
{
  testCon();
  testAdd();
  testSize();
  testFind();
  testInsertion();
  testOperator();
  testInsert();
  testRemove();
  testDestruct();
 return 0;
}
