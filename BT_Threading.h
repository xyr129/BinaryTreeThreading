# include<iostream>
using namespace std;

enum PointerTag { THREAD, LINK };


template <class T>
struct BinaryTreeNode_Thd
{
	T _data;                         // ����
	BinaryTreeNode_Thd<T >* _left;   // ����
	BinaryTreeNode_Thd<T >* _right;  // �Һ���
	PointerTag   _leftTag;          // ����������־
	PointerTag   _rightTag;         // �Һ���������־

	BinaryTreeNode_Thd(const T x)
		:_data(x)
		,_left(NULL)
		, _right(NULL)
		, _rightTag(LINK)
		, _leftTag(LINK)
	{}
};

template<class T>
class BinaryTree_Thd
{
public:
	BinaryTree_Thd()
		:_root(NULL)
	{}
	BinaryTree_Thd(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _Creat(a, size, index);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void InOrderTreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_InOrderThreading(_root, prev);
	}
	void InOrderThd()
	{
		_InOrderThd(_root);
	}

	void PreOrderThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PreOrderThreading(_root, prev);
	}
	void PreOrderThd()
	{
		_PreOrderThd(_root);
	}

	void PostOrderThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PostOrderThreading(_root, prev);
	}
	void PostOrderThd()
	{
		_PostOrderThd(_root);
	}

protected:
	BinaryTreeNode_Thd<T>* _Creat(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode_Thd<T>* root = NULL;
		if (index < size&&a[index] != '#')
		{
			root = new BinaryTreeNode_Thd<T>(a[index]);
			root->_left = _Creat(a, size, ++index);
			root->_right = _Creat(a, size, ++index);
		}
		return root;
	}
	void _InOrder(BinaryTreeNode_Thd<T>* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void _InOrderThreading(BinaryTreeNode_Thd<T>* root, BinaryTreeNode_Thd<T>*& prev)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrderThreading(root->_left, prev);

		//������
		if (NULL == root->_left)
		{
			root->_leftTag = THREAD;
			root->_left = prev;
		}
		
		if (prev && NULL == prev->_right) //�Һ����ڷ�������һ������������
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
		}
		prev = root;

		_InOrderThreading(root->_right, prev);

	}

	void _InOrderThd(BinaryTreeNode_Thd<T>* root)
	{
		BinaryTreeNode_Thd<T>* cur = root;
		while (cur)
		{
			//������
			while (cur && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout << cur->_data << " ";

			//���������ĺ�̽��
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			//��������������(cur->_rightTag==LINK)  �����Ϊlink��������
			cur = cur->_right;

		}
		cout << endl;
	}

	void _PreOrderThreading(BinaryTreeNode_Thd<T>* root, BinaryTreeNode_Thd<T>*& prev)
	{
		if (NULL == root)
		{
			return;
		}
		if (NULL == root->_left)
		{
			root->_leftTag = THREAD;
			root->_left = prev;
		}
		if (prev && NULL == prev->_right)
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
		}
		prev = root;

		//��ֹ�ظ�������
		if (root->_leftTag == LINK)
		{
			_PreOrderThreading(root->_left, prev);
		}
		if (root->_rightTag == LINK)
		{
			_PreOrderThreading(root->_right, prev);
		}
	}
	void _PreOrderThd(BinaryTreeNode_Thd<T>* root)
	{
		BinaryTreeNode_Thd<T>* cur = root;
		while (cur)
		{
			while (cur && cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
		
			//���������ĺ�̽��
			while (cur->_rightTag == THREAD)        //cur=cur->_right;
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			//��������������(cur->_rightTag==LINK)  �����Ϊlink��������
			cur = cur->_right;
		}
		cout << endl;
	}
	
	void _PostOrderThreading(BinaryTreeNode_Thd<T>* root, BinaryTreeNode_Thd<T>*& prev)
	{
		if (NULL == root)
		{
			return;
		}
		_PostOrderThreading(root->_left, prev);
		_PostOrderThreading(root->_right, prev);

		if (NULL == root->_left)
		{
			root->_leftTag = THREAD;
			root->_left = prev;
		}
		if (prev && NULL == prev->_right)
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
		}
		prev = root;
	}
	void _PostOrderThd(BinaryTreeNode_Thd<T>* root)
	{
		BinaryTreeNode_Thd<T>* cur = root;
		BinaryTreeNode_Thd<T>* prev = NULL;
		while (cur)
		{
			if (cur->_right!=NULL)
			{
				cur = cur->_right;
			}
			if (cur->_leftTag == THREAD)
			{
				cout << cur->_data << " ";
			}
			else
			{
				cur = cur->_left;
			}
			
		}
	}
private:
	BinaryTreeNode_Thd<T>* _root;
};
