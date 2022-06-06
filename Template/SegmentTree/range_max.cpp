class SegTreeNode
{
    public:
    SegTreeNode* left = NULL;
    SegTreeNode* right = NULL;
    int start, end;
    int info;  // the max height of the range
    bool tag; 
        
    SegTreeNode(int a, int b, int val)  // init for range [a,b]
    {                 
        tag = 0;
        start = a, end = b;
        if (a==b)
        {
            info = val;
            return;
        }        
        int mid = (a+b)/2;
        if (left==NULL)
        {
            left = new SegTreeNode(a, mid, val);
            right = new SegTreeNode(mid+1, b, val);            
            info = max(left->info, right->info);  // write your own logic
        }        
    }    
    
    void pushDown()
    {
        if (tag==1 && left)
        {
            left->info = info;
            right->info = info;
            left->tag = 1;
            right->tag = 1;
            tag = 0;
        }        
    } 
    
    void updateRange(int a, int b, int val)
    {        
        if (b < start || a > end ) // no intersection
            return;
        
        if (a <= start && end <=b)
        {
            info = val;
            tag = 1;
            return;
        }

        if (left)
        {
            pushDown();        
            left->updateRange(a, b, val);
            right->updateRange(a, b, val);
            info = max(left->info, right->info);  // write your own logic            
        }        
    }
    
    int queryRange(int a, int b)
    {
        if (b < start || a > end )
        {
            return 0;  // write your own logic
        }
        if (a <= start && end <=b)
        {
            return info;  // write your own logic
        }          
        
        if (left)
        {
            pushDown();     
            int ret = max(left->queryRange(a, b), right->queryRange(a, b));        
            info = max(left->info, right->info);
            return ret;
        }
        
        return info;          
    }  

};

int main()
{
    SegTreeNode* root = new SegTreeNode(0, length-1);
  
    for (auto& update: updates)
    {
        int start = update[0], end = update[1], val = update[2];
        root->updateRange(start, end ,val); // set the range [start, end] with val 
    }
  
    vector<int>rets(length);
    for (int i=0; i<length; i++)
        rets[i] = root->queryRange(i, i); // get single node val
    return rets;
}