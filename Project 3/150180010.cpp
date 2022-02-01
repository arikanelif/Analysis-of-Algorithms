//Elif ARIKAN
//150180010

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include <vector>
#include <time.h> // for calculate the time
//#include <bits/stdc++.h>

using namespace std;
enum COLOR { RED, BLACK };

struct Node
{
	//string name;
    //string platform;
    int yearOfRelease;
    string publisher;  //as a key value for node
    double NA_sales;
    double EU_sales;
    double Other_sales;
    bool color;
    Node *left, *right ,*parent;
	// Constructor
	Node()
	{
		EU_sales=0;    
        NA_sales=0;
        Other_sales=0;
        left = right = parent = NULL;
        this->color = RED;
	}
};
// Class to represent Red-Black Tree
class RBTree
{
private:
	double max_NA;
	double max_EU;
	double max_Other;
	string NA_publisher;
	string EU_publisher;
	string Other_publisher;
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor
	RBTree() { root = NULL; 
				double max_NA=0;
				double max_EU=0;
				double max_Other=0;}
	void insertion(Node*);  //const string, const double, const double, const double 
	void preorder();
	void find_max_sales(Node*);
	string getNA_publisher(){return NA_publisher;}
	string getEU_publisher(){return EU_publisher;}
	string getOther_publisher(){return Other_publisher;}
	double getMax_NA(){return max_NA;}
	double getMax_EU(){return max_EU;}
	double getMAx_Other(){return max_Other;}
};
// A recursive function to do inorder traversal
void PreOrderTraversal(Node *root, int height)
{
	if (root == NULL){
		return;
	}
	else
	{
		for(int i = 0; i < height; i++)cout << "-";
		cout << "(";
		if(root->color==RED)
			cout<< "RED";
		else
			cout << "BLACK";
		cout << ") "<< root->publisher << endl;  //firtly roots key value
		
		PreOrderTraversal(root->left, height + 1);   //secondly left childs key value
		
		PreOrderTraversal(root->right, height + 1);  //finally right childs key value
	}

    

}

/* A utility function to insert
	a new node with given key
in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL){
        return pt;
    }
	/* Otherwise, recur down the tree */
 	if (pt->publisher.compare(root->publisher)<0)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->publisher.compare(root->publisher)>0)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}
    else if (pt->publisher.compare(root->publisher)==0)
    {
        pt->NA_sales += root->NA_sales;
        pt->EU_sales += root->EU_sales;
        pt->Other_sales += root->Other_sales;
		pt->left=root->left;
		pt->right=root->right;
		pt->color=root->color;
		root=pt;
    }
	/* return the (unchanged) node pointer */
	return root;
}


// Function to insert a new node with given data
void RBTree::insertion(Node* pt) //const string name, const double EU, const double NA, const double Other
{
	//Node *pt = new Node(node); //name,EU,NA,Other
	// Do a normal BST insert
	this->root = BSTInsert(this->root, pt);
	// fix Red Black Tree violations
	fixViolation(root, pt);
    
}

// Function to do inorder and level order traversals
void RBTree::preorder(){ 
    PreOrderTraversal(root,0);
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;
	while ((pt->publisher != root->publisher) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/* if Parent of pt is left child
			of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child
		of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color ==
													RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color,
						grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}
	root->color = BLACK;
}

Node* search( Node* root, string key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->publisher == key)
       return root;
   
    // Key is greater than root's key
    if (root->publisher < key)
       return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

void RBTree::find_max_sales(Node *pt)
{
	if(this->max_NA < pt->NA_sales)
	{
		this->max_NA = pt->NA_sales;
		this->NA_publisher = pt->publisher;
	}
	if(this->max_EU < pt->EU_sales)
	{
		this->max_EU=pt->EU_sales;
		this->EU_publisher=pt->publisher;
	}
	if(this->max_Other < pt->Other_sales)
	{
		this->max_Other=pt->Other_sales;
		this->Other_publisher=pt->publisher;
	}
}
void bestPublisherPrint(int year, RBTree tree){
	cout <<"End of the "<< year <<" Year" <<endl;
	cout << "Best seller in North America: "<< tree.getNA_publisher() <<" - " ;
	printf("%.2lf million\n", tree.getMax_NA() ) ;
	cout << "Best seller in Europe: " << tree.getEU_publisher() <<" - ";
	printf("%.2lf million\n", tree.getMax_EU() ) ;
	cout <<"Best seller rest of the World: " <<tree.getOther_publisher() <<" - ";
	printf("%.2lf million\n", tree.getMAx_Other() ) ;
}
int main(int argc, char *argv[]){
    string inputfile = (argv[1]); //input file name includes videogames data.
	RBTree *videoGames =new RBTree;
	//RBTree tree;
    int x;
    double y;
    string line;
    ifstream file(inputfile);  // opens the file to read.
	if (!file){ // checks whether the file has been opened.
		cerr << "File cannot be opened!";  //error message 
		exit(1);
	}
	int lastYear;
	int endofdecade=1991;
    getline(file, line);  //this is the header line
	while(getline(file, line,',')) // read from file and assign data to tree
	{      
		Node *new_node=new Node;         
		//getline(file, line, ','); //tweet id(string)
        //new_node->name= line;
        
        getline(file, line, ','); //platform (string)
        //new_node->platform = line;

		getline(file, line, ','); //year of release (int)
        stringstream ss(line); // convert string to integer 
        ss >> x;
        new_node->yearOfRelease = x;
        
        getline(file, line, ','); //publisher name (string)
        new_node->publisher = line;

		getline(file, line, ','); //NA sales (double)
        stringstream sss(line); // convert string to double 
        sss >> y;
        new_node->NA_sales = y;

        getline(file, line, ','); //EU sales (double)
        stringstream ssss(line); // convert string to double 
        ssss >> y;
        new_node->EU_sales = y;

        getline(file, line, '\n'); //Other sales from rest of world (double)
        stringstream sssss(line); // convert string to double 
        sssss >> y;
        new_node->Other_sales = y;

		lastYear=new_node->yearOfRelease;
		if(lastYear == endofdecade )
		{
			bestPublisherPrint(lastYear-1,*videoGames);
			endofdecade+=10;
		}
        videoGames->insertion(new_node);
		videoGames->find_max_sales(new_node);
		
	}
	bestPublisherPrint(lastYear,*videoGames);

	videoGames->preorder();

	return 0;
}