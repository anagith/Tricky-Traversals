#include <iostream>
#include <stack>
using namespace std;
enum Mark {YES, NO};
enum Dir  {LEFT, RIGHT};
struct Node {
    char		info_;
    Node*		llink_;
    Node*		rlink_;
    Mark		mark_;
    Dir			dir_;

    Node() {}
    Node(char info, Node* llink = nullptr, Node* rlink = nullptr, Mark mark=NO, Dir dir=LEFT) :
            info_(info), llink_(llink), rlink_(rlink), mark_(mark), dir_(dir) {}
};

void
removeMarking(Node* tree)
{
    if (tree){
        tree->mark_ = NO; tree->dir_=LEFT;
        removeMarking(tree->llink_);
        removeMarking(tree->rlink_);
    }
}

void
trickyPreorder(Node* tree)
{
    Node* top = nullptr;
    Node* current = tree;
    Node* temp;

    while (current) {
        if (current->mark_ == NO){
            cout << current->info_ <<" ";
            current->mark_ = YES;
        }

        if (current->llink_ && current->llink_->mark_==NO) {
            temp = current->llink_;
            current->llink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (current->rlink_ && current->rlink_->mark_ == NO) {
            current->dir_ = RIGHT;
            temp = current->rlink_;
            current->rlink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (top == nullptr) return;

        temp = top;
        if (temp->dir_==LEFT) {
            top = top->llink_;
            temp->llink_ = current;
        }
        else {
            top = top->rlink_;
            temp->rlink_ = current;
        }
        current = temp;
    }
}


void
trickyInorder(Node* tree)
{
    Node* top = nullptr;
    Node* current = tree;
    Node* temp;

    while (current) {
        if (current->llink_ && current->llink_->mark_ == NO) {
            temp = current->llink_;
            current->llink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (current->mark_ == NO) {
            cout << current->info_ << " ";
            current->mark_ = YES;
        }

        if (current->rlink_ && current->rlink_->mark_ == NO) {
            current->dir_ = RIGHT;
            temp = current->rlink_;
            current->rlink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (top == nullptr) return;

        temp = top;
        if (temp->dir_ == LEFT) {
            top = top->llink_;
            temp->llink_ = current;
        }
        else {
            top = top->rlink_;
            temp->rlink_ = current;
        }
        current = temp;
    }
}


void
trickyPostorder(Node* tree)
{
    Node* top = nullptr;
    Node* current = tree;
    Node* temp;
    while (current)
    {
        if (current->llink_ && current->llink_->mark_ == NO)
        {
            temp = current->llink_;
            current->llink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (current->rlink_ && current->rlink_->mark_ == NO)
        {
            current->dir_ = RIGHT;
            temp = current->rlink_;
            current->rlink_ = top;
            top = current;
            current = temp;
            continue;
        }

        if (current->mark_ == NO)
        {
            cout << current->info_ << " ";
            current->mark_ = YES;
        }
        if (top == nullptr) return;
        temp = top;
        if (temp->dir_ == LEFT)
        {
            top = top->llink_;
            temp->llink_ = current;
        }
        else{
            top = top->rlink_;
            temp->rlink_ = current;
        }
        current = temp;
    }
}


int main(){
    Node* D = new Node('D');
    Node* G = new Node('G');
    Node* H = new Node('H');
    Node* I = new Node('I');

    Node* B = new Node('B', D);
    Node* E = new Node('E', nullptr, G);
    Node* F = new Node('F', H, I);

    Node* C = new Node('C', E, F);

    Node* tree = new Node('A', B, C);

/*
       A
      / \
      B  C
     /  / \
     D  E   F
         \ / \
         G H  I
*/
    cout << endl << "***** TRICKY PREORDER: *****" << endl;
    trickyPreorder(tree); removeMarking(tree);

    cout << endl << "***** TRICKY INORDER: *****" << endl;
    trickyInorder(tree); removeMarking(tree);

    cout << endl << "***** TRICKY POSTORDER: *****" << endl;
    trickyPostorder(tree);

    return 0;
}