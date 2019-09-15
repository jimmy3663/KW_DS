#include "BinarySearchTree.h"

void BinarySearchTree::insert(SoccerPlayerData &data){
	TreeNode *p = m_root, *pp = NULL;

	while(p){
		pp = p; 
		if(data.m_ability < p->m_data.m_ability) p = p->m_left;
		else p = p->m_right; 
	} 

	p = new TreeNode(data, NULL, NULL);
	if(m_root){
		if(p->m_data.m_ability < pp->m_data.m_ability) pp->m_left = p;
		else pp->m_right = p;
	}
	else m_root = p;
	

}

void BinarySearchTree::deletion(int ability){
	TreeNode *p = m_root, *pp = NULL;

	while(p && p->m_data.m_ability != ability){
		pp = p;
		if(ability < p->m_data.m_ability) p = p->m_left;
		else if(ability > p->m_data.m_ability) p = p->m_right; 
	}

	if(p == NULL) return;

	else if(p->m_left == NULL  && p->m_right == NULL){
		if(pp == NULL) m_root = NULL;
		else if(pp->m_right == p) pp->m_right = NULL;
		else pp->m_left = NULL;

		delete p;
	}

	else if(p->m_left == NULL){
		if(pp == NULL) m_root = p->m_right;
		else if(pp->m_left == p) pp->m_left = p->m_right;
		else pp->m_right = p->m_right;

		delete p;
	}

	else if(p->m_right == NULL){
		if(pp==NULL) m_root = p->m_left;
		else if(pp->m_left == p) pp->m_left = p->m_left;
		else pp->m_right = p->m_left;

		delete p;
	}

	else{
		TreeNode *prevprev = p, *prev = p->m_right, *curr = p->m_right->m_left;

		while(curr){
			prevprev = prev;
			prev = curr; 
			curr = curr->m_left;
		}

		p->m_data = prev->m_data;

		if(prevprev == p) prevprev->m_right = prev->m_right;
		else prevprev->m_left = prev->m_left; 

		delete prev; 
	}
}