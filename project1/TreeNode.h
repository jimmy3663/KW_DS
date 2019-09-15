#pragma once

#include "SoccerPlayerData.h"
#include <iostream>

using namespace std; 

class TreeNode
{
	friend class BinarySearchTree;
	friend class TransferWindowManager;
private:
	SoccerPlayerData m_data;
	TreeNode* m_left;
	TreeNode* m_right;
public:
	TreeNode() :m_left(NULL), m_right(NULL) {}
	~TreeNode() { }
	TreeNode(SoccerPlayerData & data, TreeNode* left = NULL, TreeNode* right = NULL)
	{
		this->m_data = data;
		this->m_left = left;
		this->m_right = right;
	}

	friend ostream& operator<<(ostream& os, const TreeNode* node)
	{
		// fill in your code to print in-order traversal of a binary search tree
		if(node){
			operator<<(os,node->m_left);
			os<<node->m_data<<endl;
			operator<<(os,node->m_right);
		}
		return os;
	}
};
