#ifndef BINARYTREE_H
#define BINARYTREE_H

using namespace std;

class btree
{
private:

    struct node
    {
        node* left;
        node* right;
        int data;
    };
    node* root;

public:

    btree();
    bool isEmpty();

    void insert(int);
    void remove(int);

    void print_inorder();
    void print_preorder();
    void print_postorder();

    bool search(int);

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);

    bool search_element(node*, int);
};

btree::btree() {
  root = NULL;
}

bool btree::isEmpty()
{
  if (root == NULL)
    return true;
  else
    return false;
}

void btree::insert(int d)
{
  if (!search(d)) { // if 'd' is not in the tree.
    if (isEmpty()) {  // if 'd' is the first element of the tree
      root = new node;
      root->data = d;
      root->left = NULL;
      root->right = NULL;
    }
    else {
      // search for a place to insert 'd'
      node* current_node = root;

      while(true) {
        if (d < current_node->data) {
          if (current_node->left != NULL) {
            current_node = current_node->left;
          }
          else {
            current_node->left = new node;
            current_node->left->data = d;
            current_node->left->left = NULL;
            current_node->left->right = NULL;
            break;
          }
        }
        else if (d >= current_node->data) {
          if (current_node->right != NULL) {
            current_node = current_node->right;
          }
          else {
            current_node->right = new node;
            current_node->right->data = d;
            current_node->right->left = NULL;
            current_node->right->right = NULL;
            break;
          }
        }
      }
    }
  }
}

bool btree::search(int val)
{
  return search_element(root, val);
}

bool btree::search_element(node* p, int val)
{
  if (p != NULL) {
    if (val == p->data) {
      return true;
    }

    if (val > p->data) {
      return search_element(p->right, val);
    }
    else
      return search_element(p->left, val);
  }
  else {
    return false;
  }
}

void btree::remove(int d)
{
  bool found = false;
  node* predecessor;
  node* current_node = root;

  if (isEmpty()) {
    std::cout << "The tree is empty" << std::endl;
    return;
  }

  if (current_node->left == NULL && current_node->right == NULL) {
    root = NULL;
    return;
  }

  while (current_node != NULL) {
    if (current_node->data == d) {
      found = true;
      break;
    }
    else {
      predecessor = current_node;
      if (d < current_node->data) {
        current_node = current_node->left;
      }
      else {
        current_node = current_node->right;
      }
    }
  }

  if (!found) {
    cout << d << " not in the tree" << endl;
    return;
  }

  // Case 1: removing a node with single child
  if ((current_node->left == NULL and current_node->right != NULL)
      or (current_node->right == NULL and current_node->left != NULL)) {

     if (current_node->left == NULL and current_node->right != NULL) {
      if (predecessor->left == current_node) {
        predecessor->left = current_node->right;
        delete current_node;
        current_node = NULL;
        cout << d << "has been removed from the tree" << endl;
      }
      else {
        predecessor->right = current_node->right;
        delete current_node;
        current_node = NULL;
        cout << d << "has been removed from the tree" << endl;
      }
     }
     else {
      if (current_node->right == NULL and current_node->left != NULL) {
        if (predecessor->left == current_node) {
          predecessor->left = current_node->left;
          delete current_node;
          current_node = NULL;
          cout << d << "has been removed from the tree" << endl;
        }
        else {
          predecessor->right = current_node->left;
          delete current_node;
          current_node = NULL;
          cout << d << "has been removed from the tree" << endl;
        }
      }
     }
  }

  // Case 2: removing a leaf node
  if (current_node->left == NULL and current_node->right == NULL) {
    if (predecessor->left == current_node) {
      predecessor->left = NULL;
    }
    else {
      predecessor->right = NULL;
    }
  }

  // Case 3: removing a  node with two children
  if (current_node->left != NULL and current_node->right != NULL) {
    node* check=current_node->right;
    if((current_node->left==NULL)&&(current_node->right==NULL))
    {
      current_node=check;
      delete check;
      current_node->right = NULL;
      cout << d << " has been removed from the Tree." << endl;
    }
    else // Right child has children
    {
      // If the node's right child has a left child
      // Move all the way down left to locate smallest element
      if((current_node->right)->left != NULL)
      {
        node* leftCurrent;
        node* leftCurrentPred;
        leftCurrentPred=current_node->right;
        leftCurrent = (current_node->right)->left;
        while(leftCurrent->left != NULL)
        {
          leftCurrentPred=leftCurrent;
          leftCurrent=leftCurrent->left;
        }
        current_node->data=leftCurrent->data;
        delete leftCurrent;
        leftCurrentPred->left = NULL;
        cout << d << " has been removed from the Tree." << endl;
      }
      else
      {
        node* temp=current_node->right;
        current_node->data=temp->data;
        current_node->right=temp->right;
        delete temp;
        cout << d << " has been removed from the Tree." << endl;
      }
    }
    return;
  }
}

void btree::print_inorder()
{
  inorder(root);
}

void btree::inorder(node* p)
{
  if (p != NULL) {
    inorder(p->left);
    cout << p->data << " " ;
    inorder(p->right);
  }
}

void btree::print_preorder()
{
  preorder(root);
}

void btree::preorder(node* p)
{
  if (p != NULL)
  {
    cout << p->data << " " ;
    preorder(p->left);
    preorder(p->right);
  }
}

void btree::print_postorder()
{
  postorder(root);
}

void btree::postorder(node* p)
{
  if (p != NULL) {
    postorder(p->left);
    postorder(p->right);
    cout << p->data << " " ;
  }
}


#endif
