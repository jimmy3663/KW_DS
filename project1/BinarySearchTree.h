#pragma once

#include "TreeNode.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
class BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;
public:
	BinarySearchTree() { m_root = NULL; }
	BinarySearchTree(SoccerPlayerData& data){m_root = new TreeNode(data, NULL, NULL);}
	~BinarySearchTree(){Destroy(m_root);}

	void insert(SoccerPlayerData& data);
	void deletion(int ability); // ability = key
	void deleteNode(TreeNode *node){
		delete node;
		return;
	}
	void Destroy(TreeNode *node){
		if(node){
			Destroy(node->m_left);
			deleteNode(node);
			Destroy(node->m_right);		
		}
		return;
	}

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {
	// fill in your code to print in-order traversal of a binary search tree
		/*TreeNode *curr = tree.m_root;
		stack <TreeNode *> s; //= new stack<TreeNode>();
		
		while (curr != NULL || s.empty() == false) {
        	while (curr !=  NULL) { 
            	s.push(curr); 
            	curr = curr->m_left; 
        	} 

	        curr = s.top(); 
	        s.pop(); 
	  
	        os << curr->m_data << endl; 
	        curr = curr->m_right;
   		}*/
   		os<<tree.m_root;

		return os;
	}

};
