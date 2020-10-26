#ifndef TREE_H
#define TREE_H
#include <cstdlib>

template <class N>
class Node 
{
	N value;
	Node<N> *left;
	Node<N> *right;
	public:
		Node(const N &anObject);//constructor for initialization
		bool member(const N &anObject);
		void insert(const N &anObject);		
};

template <class N>
Node<N>::Node(const N &anObject)//constructor
{
	value = anObject;
	left = NULL;
	right = NULL;
}

//manipulation methods
template <class N>
bool Node<N>::member(const N &anObject)
{
	if(anObject < value)
	{
		if(left == NULL)
			return false;
		else
			return left->member(anObject);
	}
	else if(anObject > value)
	{
		if(right == NULL)
			return false;
		else
			return right->member(anObject);
	}
	return true;
}
template <class N>
void Node<N>::insert(const N &anObject)
{
	if(anObject < value)
	{
		if(left == NULL)
			left = new Node<N>(anObject);
		else
			left->insert(anObject);
	}
	else if(anObject > value)
	{
		if(right == NULL)
			right = new Node<N>(anObject);
		else
			right->insert(anObject);
	}
}

template <class N>
class Tree
{
	Node<N> *root;
	public:
		bool member(const N &anObject);
		void insert(const N &anObject);
};

//manipulation methods
template <class N>
bool Tree<N>::member(const N &anObject)
{
	if(root == NULL)
		return false;
	else
		return root->member(anObject);
}
template <class N>
void Tree<N>::insert(const N &anObject)
{
	if(root == NULL)
		root = new Node<N>(anObject);
	else
		root->insert(anObject);
}					
		
#endif
