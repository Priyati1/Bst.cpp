#include<iostream>
#include<queue>
using namespace std;
class node{
public:
	int data;
	node*left;
	node*right;
	//constructor
	node(int d){
		data=d;
		left=NULL;
		right=NULL;
	}
};
node*insertion_in_BST(node*root,int data){
	//base case
	if(root==NULL){
		root=new node(data);
		return root;
	}
	//recursive case
	if(data<=root->data){
		root->left=insertion_in_BST(root->left,data);
	}
	else{
		root->right=insertion_in_BST(root->right,data);
	}
	return root;
}

node *build_BST(){
	node *root=NULL;
	int data;
	cin>>data;
	while(data!=-1){
		root=insertion_in_BST(root,data);
		cin>>data;
	}
	return root;
}


bool search_BST(node*root,int key){
	//base case
	if(root==NULL){
		return false;
	}
	//recursive case
	if(key==root->data){
		return true;
	}
	else if(key<root->data){
		return search_BST(root->left,key);
	}
	else{
		return search_BST(root->right,key);
	}
}

void print_range(node*root,int k1,int k2){
	//base case
	if(root==NULL){
		return ; 
	}
	//recursive case
	print_range(root->left,k1,k2);
	if(root->data>=k1 && root->data<=k2){
		cout<<root->data<<" ";
	}
	print_range(root->right,k1,k2);

}

bool isBST(node*root,int max=INT_MAX,int min=INT_MIN){
	//base case
	if(root==NULL){
		return false;
	}
	//recursive case
	if((root->data>=min && root->data<=max)&& isBST(root->left,root->data,min)&& isBST(root->right,max,root->data)){
		return true;
	}
	return false;
}


class Pair{
public:
	int height;
	bool bal;
	//constructor
	Pair(){
		height=0;
		bal=true;
	}
};
Pair in_balance(node*root){
	Pair p;
	//base case
	if(root==NULL){
		return p;
	}
	//recursive case
	Pair left=in_balance(root->left);
	Pair right=in_balance(root->right);
	p.height=max(left.height,right.height)+1;
	if((left.bal==true && right.bal==true) && (abs(left.height=right.bal)<=1)){
		p.bal=true;
	}
	else{
		p.bal=false;
	}
	return p;
}


//bst to ll
class linkedlist{
public:

	node *head;
	node*tail;
	//constructor
	linkedlist(){
		head=NULL;
		tail=NULL;
	}
};
linkedlist bst_to_ll(node*root){
	linkedlist l;
	//base case
	if(root==NULL){
		return l;
	}
	//recursive case
	//case1 when no children present
	if(root->left==NULL && root->right==NULL){
		l.head=root;
		l.tail=root;
		
	}
	//case 2 when only left subtree is present
	else if(root->left!=NULL && root->right==NULL){
		linkedlist Left=bst_to_ll(root->left);
		Left.tail->right=root;
		l.head=Left.head;
		l.tail=root;
		
	}
	//case 3 right subtree present 
	else if(root->left==NULL && root->right!=NULL){
		linkedlist Right=bst_to_ll(root->right);
		root->right=Right.head;
		l.head=root;
		l.tail=Right.tail;
		
	}
	//case 4 all subtree present
	else{
		linkedlist Left=bst_to_ll(root->left);
		linkedlist Right=bst_to_ll(root->right);
		Left.tail->right=root;
		root->right=Right.head;
		l.head=Left.head;
		l.tail=Right.tail;
		
	}
	return l;
}

void print_level_wise(node*root){
	queue<node*>q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		node*x=q.front();
		q.pop();
		if(x==NULL){
			cout<<endl;
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			cout<<x->data<<" ";
			if(x->left!=NULL){
				q.push(x->left);
			}
			if(x->right!=NULL){
				q.push(x->right);
			}
		}
	}
}

void print_ll(node*head){
	while(head!=NULL){
		cout<<head->data<<"->";
		head=head->right;
	}
	cout<<"NULL"<<endl;
}

node *create_bst_using_array(int *arr,int s,int e){
	//base case
	if(s>e){
		return NULL;
	}
	//recursive case
	int mid=(s+e)/2;
	node*root=new node(arr[mid]);
	root->left=create_bst_using_array(arr,s,mid-1);
	root->right=create_bst_using_array(arr,mid+1,e);
	return root;
}

node *delete_bst(node*root,int key){
	//case 1-->key lst
	if(root->data>key){
		root->left=delete_bst(root->left,key);
		return root;
	}
	else if(root->data<key){
		root->right=delete_bst(root->right,key);
		return root;
	}
	else{
		if(root->left==NULL && root->right==NULL){
			delete root;
			return NULL;
		}
		else if(root->left!=NULL&&root->right==NULL){
			node*temp=root->left;
			delete root;
			root=NULL;
			return temp;
		}
		else if(root->left==NULL&&root->right!=NULL){
			node*temp=root->right;
			delete root;
			root=NULL;
			return temp;
		}
		else{
			// /root 2 chidrem
			// node*replace=root->right;
			// while(replace->left!=NULL){
			// 	replace=replace->left;

			// }
			// swap(replace->data,root->data);
			// root->right=deleteinbst(root->right,key);
			// return root;

			node*replace=root->left;
			while(replace->right!=NULL){
				replace=replace->right;

			}
			swap(replace->data,root->data);
			root->left=delete_bst(root->left,key);
			return root;
		}

	}
	return root;
}
void right_view(node*root,int level,int &maxlttn){
	if(root==NULL){
		return;
	}
	// l 1 ml-->0 
	// l 2 ml-->1
	// l 3 ml-->2
	// l 4 ml-->3
	if(level>maxlttn){
		cout<<root->data<<" ";
		maxlttn++;//5
	}
	right_view(root->right,level+1,maxlttn);
	right_view(root->left,level+1,maxlttn);
}


void left_view(node*root,int level,int &maxlttn){
	if(root==NULL){
		return;
	}
	// l 1 ml-->0 
	// l 2 ml-->1
	// l 3 ml-->2
	// l 4 ml-->3
	if(level>maxlttn){
		cout<<root->data<<" ";
		maxlttn++;//5
	}
	left_view(root->left,level+1,maxlttn);
	left_view(root->right,level+1,maxlttn);
}
int main(){
	// int key;
	// cin>>key;
	node *root=build_BST();
	print_level_wise(root);
	// int k1,k2;
	// cin>>k1>>k2;
	// if(search_BST(root,key)){
	// 	cout<<"Key is present"<<endl;
	// }
	// else{
	// 	cout<<"key is not present"<<endl;
	// }

	// print_range(root,k1,k2);
	// if(isBST(root)){
	// 	cout<<"yes the tree is bst"<<endl; 
	// }
	// else{
	// 	cout<<"no the tree is not a bst"<<endl;
	// }

	// Pair x=in_balance(root);
	// if(x.bal==true){
	// 	cout<<"yes balanced"<<endl;
	// }
	// else{
	// 	cout<<"not balanced"<<endl;
	// }

	// linkedlist l=bst_to_ll(root);
	// print_ll(l.head);

	// int arr[]={1,2,3,4,8,9,10};
	// int n=sizeof(arr)/sizeof(int);
	// node*root2=create_bst_using_array(arr,0,n-1);
	// print_level_wise(root2);

	// delete_bst(root,5);
	// cout<<"after deleteing"<<endl;
	// print_level_wise(root);

	int x=0;
	right_view(root,1,x);
	print_level_wise(root);
	cout<<endl<<endl;
	left_view(root,1,x);
	print_level_wise(root);
	cout<<endl<<endl;


	return 0;
}
