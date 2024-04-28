#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

int main(){
    int n; //size of the array.
    int store; //for values of the array
    cout<<"Enter size: ";
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        cout<<"enter a value: ";
        cin>>store;
        arr.push_back(store);
    }
    cout<<n<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    //findin the mnpn
    //make frequency array of size n. where the mnpn is the minimum excluded
    //following the array size dependant mnpn finder.
    //any value greater than the size of the array is disregarded.
    int *frequency = new int[n+1];
    //populate frequency with 0;
    for(int i=0;i<n+1;i++){
        frequency[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(arr[i]<=n){
            frequency[arr[i]]++;
        }
    }
    //run the check for the frequency array.
    int mnpn;
    for(int i=0;i<n;i++){
        if(frequency[i] == 0){
            cout<<"MNPN IS: "<<i<<endl;
            mnpn = i;
            break;
        }
    }
    int seg[2][2];
    int trackCount = 0,segCount = 0; //used to track the mnpn values by indexing. if it reaches the size of the boolean array then it means the array is filled.
    if(mnpn == 0){
        //any range can be made the segment.
        seg[0][0] = 0;
        seg[0][1] = n/2;
        seg[1][0] = n/2+1;
        seg[1][1] = n-1;
        segCount = 2;
        goto skip;
    }
    //the boolean tracker.
    //contains the boolean trackers for all values less than the mnpn as they need to be in every possible found segment
   
    //segment making based on start and end indexes.
    //find first segment that satisfies mnpn segment should contains all values lesser than mnpn.
    int start,end;
    for(int i=0;i<n;i++){ //a loop that runs till n and returns -1 if no specific segments are found.
            if(segCount == 2){
                seg[1][1] = n-1;
                break;
            }
        if(arr[i] <= mnpn){
            
            trackCount++;
            if(trackCount == mnpn){
            trackCount = 0;
            seg[segCount][0] = start;
            seg[segCount][1] = end;
            start = i+1; //move to an index ahead of current end.
            end = i+1; //give start and end the same value.
            segCount++;
            }
        }
        end++;
    }
    skip:
    if(segCount != 2){
        cout<<"-1"<<endl;
    }
    else{
    cout<<"Segments: "<<2<<endl;
    cout<<seg[0][0]+1<<","<<seg[0][1]+1<<endl;
    cout<<seg[1][0]+1<<","<<seg[1][1]+1;
    }
    return 0;
}