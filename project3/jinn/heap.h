#ifndef __HEAP_H__
#define __HEAP_H__

      
class TreeNode {
    public:
    int value;
    int key;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode* parent;
    
    TreeNode(int key = 0, int value  = 0) {
        this->key = key;
        this->value = value;
        leftChild = NULL;
        rightChild = NULL;
	parent = NULL;
    }
    
    /*
     * @Overload operator
     */
    bool operator < (const TreeNode& anotherNode);
    
    /*
     * @Overload operator
     */
    bool operator > (const TreeNode& anotherNode);
    
};


class BinaryHeap {
    private:
    bool isMaxHeap;
    TreeNode * root;
    int heap_size;
    public:
    /*
    * If isMaxHeap == true, initialize as a MaxHeap.
    * Else, initialize as a MinHeap.
    */
    BinaryHeap(bool isMaxHeap);
    
    /*
    * Given an array of TreeNode elements, create the heap.
    * Assume the heap is empty, when this is called.
    */
    void heapify(int size, TreeNode * nodes);
    
    /*
    * insert the node into the heap.
    * return false, in case of failure.
    * return true for success.
    */
    bool insert(TreeNode * node);
    
    /*
     * Return the minimum element of the min-heap [max element of max-heap]
     */
    TreeNode * extract();
    
    /*
     * Return the current size of the Heap.
     */
    int size();
    TreeNode * peak();
};

void heapSort(int size, TreeNode * elements, bool isReverseOrder);

#endif
