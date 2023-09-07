#include <iostream>
#include <cstring>
using namespace std;

//characters
char arr[100000];
//their frequencies
int f[100000];
char a[100000];
//current size of heap
int heapsize=0;

//Huffmantree node
struct node {
    char data;
    int freq;
    node *left=NULL;
    node *right=NULL;
};

//2d array of nodes
node** rep=new node*();
node* first;
node* second;
node* root;
//recursive function to maintain the heap
void heapp(int parent){
           //we assume parent is the min since it's a min heap
           int min = parent;
           //index of right child = 2*(index of parent)+2
           int r = 2*parent+2;
           //if this parent has a left child
           if (2*parent+1 < heapsize){
               //if the left child's frequency is smaller than its parent
               if(rep[2*parent+1]->freq < rep[min]->freq){
                   //left child becomes the new min
                   min = 2*parent+1;
               }
           }
         
           if (r < heapsize){
               if(rep[r]->freq < rep[min]->freq)
                min = r;
           }
           //if min is not the parent we need to swap parent with min
           if (min!=parent) {
               node** n=&rep[min];
               node** m=&rep[parent];
               node* temp = *n;
               *n = *m;
               *m = temp;
               //now we do the same thing to min
               heapp(min);
           }
    }

void decode(int len){
      node* curr = root;
      for (int i=0;i<len;i++)
      {
          if (a[i] == '1')
             curr = curr->left;
          else
             curr = curr->right;
    
          //we reached the end ->leaf
          if (curr->left==NULL && curr->right==NULL)
          {
              cout<<curr->data;
              curr=root;
          }
      }
      return ;
}

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        cin>>f[i];
    }
    
    cin>>a;
    heapsize = n;
    
    //populating rep (the 2d array pointing to nodes) with the huffman tree nodes
      for (int i=0;i<heapsize;i++){
            node* a= new node();
            a->data = arr[i];
            a->freq = f[i];
            //add this node to the array of nodes
            rep[i] = a;
      }
    //we go through all the elements of the heap
    for(int i = heapsize-1;i>=0;i--){
        //if this particular element has a parent, we heapify it by comparing this element with its parent
        if(((i-1)/2)>=0)
            heapp((i-1)/2);
    }
    //continue until we have no 2 nodes left to add up
    while (heapsize>1) {
        //find the two nodes (first and second) with minimum frequencies

        //the min is rep[0] so we get it from the tree
        first = rep[0];
        //remove it from the leaves ( size-- )
        heapsize--;
        //in order to remove it we replace it with the last node in the tree ( rep[size-1] )
        rep[0] = rep[heapsize];
        //but now it's not a min heap anymore so we have to heapify the tree again
        heapp(0);
        
        //to find the second minimum we get the first element in min heap and repeat the same process
        second = rep[0];
        heapsize--;
        rep[0] = rep[heapsize];
        heapp(0);
        
        //create a new node with these two nodes as its children and its frquency equal to
        //sum of the two frquencies
        node* a= new node();
        a->freq = first->freq + second->freq;
        a->left = first;
        a->right = second;
        //add the node to heap
        heapsize++;
        //we insert the new node at the end of the heap
        int i = heapsize - 1;
        //we need to compare this node with its parent and swap if it is smaller
        //repeat this until we reach the root or it is smaller than its parent
        while(i>0){
            while(a->freq < rep[(i - 1) / 2]->freq){
                //swap the node with its parent
                rep[i] = rep[(i - 1) / 2];
                //now we need to compare the node to the parent of its parent
                i = (i - 1) / 2;
            }
            //if it the node is smaller than its parent, stop!
            break;
        }
        //this is where the node has to be placed
        rep[i] = a;
        }
        //root is the minimum in min heap -> rep[0]
      root = rep[0];
      heapsize--;
      rep[0] = rep[heapsize];
      heapp(0);
    
    int top = 0;
    decode((strlen(a)));
  
    return 0;
}
