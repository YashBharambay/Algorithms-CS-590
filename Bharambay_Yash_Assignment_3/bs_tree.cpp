#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{ 
  T_nil = new bs_tree_node();
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;

/*
 * root of rb tree
 */
  T_root = T_nil;
} 

bs_tree::~bs_tree()
{ 
  // remove_all(T_root);
    delete T_nil;
} 

int counter = 0;

void bs_tree::insert(bs_tree_node* z, bs_tree_i_info& t_info)
{ 
  bs_tree_node* x;
  bs_tree_node* y;
  y = T_nil;
  x = T_root;

  while (x != T_nil)
    {
      y = x;

      if (z->key < x->key)
	x = x->left;
      else if (z->key > x->key)
	x = x->right;
      else{
  t_info.i_duplicate = t_info.i_duplicate + 1; 
  return;
      }
    }

  z->p = y;
  if (y == T_nil)
    T_root = z;
  else
    {
      if(z->key == y->key){
        t_info.i_duplicate = t_info.i_duplicate + 1;
        return;
      }
      else if (z->key < y->key)
	y->left = z;
      else
	y->right = z;
    }

  z->left = T_nil;
  z->right = T_nil;

}
void bs_tree::insert(int key, bs_tree_i_info& t_info)
{ 
  bs_tree_node* z = new bs_tree_node;
  z -> key = key;

  insert(z, t_info);
}



// TODO: modified inorder tree walk method to save the 
// sorted numbers in the first argument: int* array.
// question 2
void bs_tree::inorder_output(bs_tree_node* x, int level,int* array)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  if (x != T_nil)
    {
      inorder_output(x->left,level+1, array);
      // cout << "(" << x->key << "," << level << "," << endl;
      // cout << x->key <<" " ;
      array[counter] = x->key;
      counter += 1;
      inorder_output(x->right,level+1, array); 
    }
} 



int bs_tree::convert(int* array, int n)
{
  if(T_root != T_nil){
  inorder_output(T_root,1, array) ;
  }
  return counter;

}