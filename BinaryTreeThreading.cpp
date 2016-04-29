#include"BT_Threading.h"

void Test()
{
	char array[] = { '1', '2', '3', '#', '#', '4', '#', '#', '5', '6', };
 	BinaryTree_Thd<char> t(array,10);
	//t.InOrder();
	//t.InOrderTreading();
	//t.InOrderThd();
	
	//t.PreOrderThreading();
	//t.PreOrderThd();

	t.PostOrderThreading();
	t.PostOrderThd();
}

int main()
{
	Test();
	system("pause");
	return 0;
}