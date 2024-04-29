#include <vector>
#include<iostream>
#include <algorithm>
#include<cmath>
using namespace std;

//using dynamic programming to store values of previously known maxes.
struct max{
	int x = 0;
};
struct Table{
	vector<vector<int>> dp; //dynamic 2d array for the profit table.
	struct max **maxes; //each column has its own 2 max values.
};
int MaxPower(vector<vector<int>> &matrix,int rows,int cols){
	//initialize the dp through a table object
	struct Table *DP = new struct Table;
    int max = 0;
    if(rows==1){
        //valid to only find one maximum value.
        for(int i=0;i<cols;i++){
            if(max <= matrix[0][i]){
                max = matrix[0][i];
            }
        }
        return max;
    }
	DP->dp.resize(rows);
	for(int i=0;i<rows;i++){
		DP->dp[i].resize(cols);
	}
	//initialize the max values.
	DP->maxes = new struct max*[cols];
	for(int i=0;i<cols;i++){
		DP->maxes[i] = new struct max[2];
	}
	//fill the dp table with first column values of the matrix.
	//also set the first col max values at the same time which at max can be 2
	 for(int i=0;i<rows;i++){
		DP->dp[i][0] = matrix[i][0];
		//second max value now becomes the max value
		if(DP->dp[DP->maxes[0][1].x][0] <= DP->dp[i][0] || DP->maxes[0][1].x == DP->maxes[0][0].x ){
			DP->maxes[0][1].x = i;
			if(DP->dp[DP->maxes[0][1].x][0] >= DP->dp[DP->maxes[0][0].x][0]){
				//swap the two values.
				int temp;
				temp = DP->maxes[0][1].x;
				DP->maxes[0][1].x = DP->maxes[0][0].x;
				DP->maxes[0][0].x = temp;
			}
		}
	 }
	 //extra checks if rows = 2
	 if(rows == 2){
		if(DP->maxes[0][0].x == 1){
			DP->maxes[0][1].x = 0;
		}
		else
		DP->maxes[0][1].x = 1;
	 }
	 for(int i=1;i<cols;i++){ //starting from second col.
		for(int j=0;j<rows;j++){ //starting from zeroth row.
			//for profit of each value
			//filling DP table
			cout<<j<<","<<i<<" ";
			if(j != DP->maxes[i-1][0].x){//if previous column row max value is not consecutive to this current value then add value to dp and update current column max vals.
				//adding row constraints here.
				if(rows == 2){ //check for 2 rows that also checks for a better available option one column back.
					if(i-2 >= 0){
						int value = std::max(matrix[j][i] + DP->dp[DP->maxes[i-1][0].x][i-1],matrix[j][i] + DP->dp[DP->maxes[i-2][0].x][i-2]);
						DP->dp[j][i] = value;
						cout<<value<<" this was added through the condition."<<endl;
					}
					else //else case does the normal addition and moves on.
					 goto twoRowNormal;
				}
				else{
					twoRowNormal:
				DP->dp[j][i] = matrix[j][i] + DP->dp[DP->maxes[i-1][0].x][i-1];
				cout<<matrix[j][i]<<" . "<<DP->dp[DP->maxes[i-1][0].x][i-1]<<endl;
				cout<<"value at: "<<j<<","<<i<<" "<<DP->dp[j][i]<<endl;
				}
			}
			else{
				//add the second max value
				//adding row constraints here.
				if(rows == 2){
					if(i-2 >=0){
						int value = std::max(matrix[j][i] + DP->dp[DP->maxes[i-1][1].x][i-1],matrix[j][i] + DP->dp[DP->maxes[i-2][0].x][i-2]);
						DP->dp[j][i] = value;
						cout<<value<<" this was added through the condition."<<endl;
					}
					else
					goto twoRowNormal2;
				}
				else{
					twoRowNormal2:
				DP->dp[j][i] = matrix[j][i] + DP->dp[DP->maxes[i-1][1].x][i-1];
				cout<<matrix[j][i]<<" . "<<DP->dp[DP->maxes[i-1][1].x][i-1]<<endl;
				cout<<"value at: "<<j<<","<<i<<" "<<DP->dp[j][i]<<endl;
				}
			}
			if(DP->dp[DP->maxes[i][1].x][i] <= DP->dp[j][i] || DP->maxes[0][1].x == DP->maxes[0][0].x){
			      DP->maxes[i][1].x = j;
			if(DP->dp[DP->maxes[i][1].x][i] >= DP->dp[DP->maxes[i][0].x][i]){
				//swap the two values.
				int temp;
				temp = DP->maxes[i][1].x;
				DP->maxes[i][1].x = DP->maxes[i][0].x;
				DP->maxes[i][0].x = temp;
				}
			}
	 	}
		//for current column before column updation.
		if(rows == 2){
		if(DP->maxes[i][0].x == 1){
			DP->maxes[i][1].x = 0;
		}
		else
		DP->maxes[i][1].x = 1;
	 }
	 }
	 
	//  for(int i=0;i<rows;i++){
	// 	if(DP->dp[i][cols-1] >= max){
	// 		max = DP->dp[i][cols-1];
	// 	}
	//  }
	max = DP->dp[DP->maxes[cols-1][0].x][cols-1];
	 ///delete[] DP->maxes;
	 delete DP->maxes;
	 DP->maxes = nullptr;
	return max;
}
int main() {
   int rows,cols;
   cout<<"Enter number of rows: ";
   cin >> rows;
   cout<<"Enter number of columns: ";
   cin >> cols;
   //vector<vector<int>> matrix = {{1,2,3,4,5},{1,12,4,12,12},{12,7,70,5,6},{0,0,0,11,0},{1,2,9,2,0}};
	//vector<vector<int>> matrix = {{1,2,3,4,5,6,6,7,6}};
	//vector<vector<int>> matrix = {{1,1},{2,2},{35,35},{7,7},{0,0}};
	//vector<vector<int>> matrix = {{11,5,7,9,5},{7,10,3,6,7}};
	//vector<vector<int>> matrix = {{1,10,35},{10,3,11}};
	vector<vector<int>> matrix = {{25,41,37},{20,12,9},{1,10,34},{3,15,39},{10,25,42}};
//    matrix.resize(rows);
//    for(int i=0;i<rows;i++){
// 		matrix[i].resize(cols);
//    }
   //input values.
//    for(int i=0;i<rows;i++){
// 	for(int j=0;j<cols;j++){
// 		cout<<"Enter value of power: ";
// 		cin>>matrix[i][j];
// 	}
//    }
   cout<<MaxPower(matrix,rows,cols);
	return 0;
}
  
