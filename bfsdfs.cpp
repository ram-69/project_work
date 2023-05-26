#include<iostream>
#include<omp.h>
#include<stack>
#include<queue>
double start,stop,start_p,stop_p;
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void pBFS(TreeNode* root){
    	 start=omp_get_wtime();
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
    stop=omp_get_wtime();	
}


void pDFS(TreeNode* root){
    start_p=omp_get_wtime();
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int ss = s.size();
        #pragma omp parallel for
        for(int i = 0; i < ss; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
                if(node->right) s.push(node->right);
                if(node->left) s.push(node->left);
            }
        }
    }
    stop_p=omp_get_wtime();	
}


int main(){
    // Construct Tree
    TreeNode* tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3); 
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->right = new TreeNode(7);

    /*
    Our Tree Looks like this:
                1
            2       3
        4     5   6    7
        
    */

    cout << "Parallel BFS: ";
    pBFS(tree);
    cout << "\n Time Parallel= " << stop-start;
    cout << "\n";
    cout << "Parallel DFS: ";
    pDFS(tree);
    cout << "\n Time Parallel= " << stop_p-start_p;
}