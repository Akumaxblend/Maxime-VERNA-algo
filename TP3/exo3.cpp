#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        // init initial node without children
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

	void insertNumber(int value) {
        // create a new node and insert it in right or left child

        
            if(this->left){

                if(!(this->right)){

                    this->right = new SearchTreeNode(value);
                    return;
                }

                else this->left->insertNumber(value);
            }

            else {
                
                this->left = new SearchTreeNode(value);
                return;   
            }     
    }

	uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        
        uint lh = 0;
        uint rh = 0;

        if(this->get_left_child() == nullptr && this->get_right_child() == nullptr){

            return 1;
        }


        if(this->get_left_child()){

            lh = this->get_left_child()->height();
            
        }

        if(this->get_right_child()){

            
            rh = this->get_right_child()->height();

        }
        
        if(lh > rh){

            return lh + 1;
        }

        else return rh +1;

        



    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1

        if(this->left == nullptr && this->right == nullptr){

            return 1;
        }

        if(this->left && this->right){

            return this->left->nodesCount() + this->right->nodesCount() + 1;
        }

        if(this->left){

            return this->left->nodesCount() + 1;
        }
        if(this->right){

            return this->right->nodesCount() + 1;
        }

	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)

        if(!(this->left) && !(this->right)){

            return true;
        }
        else return false;
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree

        if(this->isLeaf()){

            leaves[leavesCount] = this;
            leavesCount ++;
        }

        if(this->left && this->right){

            this->left->allLeaves(leaves, leavesCount);
            this->right->allLeaves(leaves, leavesCount);
        }

        else if(this->left){

            this->left->allLeaves(leaves, leavesCount);
        }
        else if(this->right){

            this->right->allLeaves(leaves, leavesCount);
        }
        
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel

        if(this->left){

            this->left->inorderTravel(nodes, nodesCount);
        }
        nodes[nodesCount] = this;
        nodesCount++;

        if(this->right){

            this->right->inorderTravel(nodes, nodesCount);
        }

	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel

        nodes[nodesCount] = this;
        nodesCount ++;

        if(this->left){

            this->left->preorderTravel(nodes, nodesCount);
        }

        if(this->right){

            this->right->preorderTravel(nodes, nodesCount);
        }
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel

        // if(this->left && this->right){

        //     this->left->inorderTravel(nodes, nodesCount);
        //     this->right->inorderTravel(nodes, nodesCount);
        // }

        if(this->left){

            this->left->postorderTravel(nodes, nodesCount);

        }

        if(this->right){

            this->right->postorderTravel(nodes, nodesCount);
        }

        // if(this->right){

        //     this->right->inorderTravel(nodes, nodesCount);
        // }

        nodes[nodesCount] = this;
        nodesCount++;

	}

	Node* find(int value) {
        // find the node containing value
		
        if(this->value == value){

            return this;
        }

        else{

            if(this->left){

                this->left->find(value);
            }

            else if(this->right){

                this->right->find(value);
            }
        }

	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
