int main() {
    priority_queue<int> q;
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);
 
    //9 8 7 6 5 4 3 2 1 0
 
    priority_queue<int, vector<int>, greater<int> > q2;
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);
 
    //0 1 2 3 4 5 6 7 8 9
 
    auto cmp = [](int left, int right) { return (left % 3) < (right % 3);};
    priority_queue<int, vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);
 
    //8 5 2 4 1 7 0 3 6 9
 
}
