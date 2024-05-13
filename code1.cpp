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
			if(DP->dp[DP->maxes[0][1].x][0] > DP->dp[DP->maxes[0][0].x][0]){
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
			if(j != DP->maxes[i-1][0].x){//if previous column row max value is not consecutive to this current value then add value to dp and update current column max vals.
				//adding row constraints here.
				if(rows == 2){ //check for 2 rows that also checks for a better available option one column back.
					if(i-2 >= 0){
						int value = std::max(matrix[j][i] + DP->dp[DP->maxes[i-1][0].x][i-1],matrix[j][i] + DP->dp[DP->maxes[i-2][0].x][i-2]);
						DP->dp[j][i] = value;
						
					}
					else //else case does the normal addition and moves on.
					 goto twoRowNormal;
				}
				else{
					twoRowNormal:
				DP->dp[j][i] = matrix[j][i] + DP->dp[DP->maxes[i-1][0].x][i-1];
				
				}
			}
			else{
				//add the second max value
				//adding row constraints here.
				if(rows == 2){
					if(i-2 >=0){
						int value = std::max(matrix[j][i] + DP->dp[DP->maxes[i-1][1].x][i-1],matrix[j][i] + DP->dp[DP->maxes[i-2][0].x][i-2]);
						DP->dp[j][i] = value;
						
					}
					else
					goto twoRowNormal2;
				}
				else{
					twoRowNormal2:
				DP->dp[j][i] = matrix[j][i] + DP->dp[DP->maxes[i-1][1].x][i-1];
				
				}
			}
			if(DP->dp[DP->maxes[i][1].x][i] < DP->dp[j][i] || DP->maxes[i][1].x == DP->maxes[i][0].x){
			      DP->maxes[i][1].x = j;
				  cout<<j<<endl;
			if(DP->dp[DP->maxes[i][1].x][i] > DP->dp[DP->maxes[i][0].x][i]){
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
	 cout<<endl;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<DP->dp[i][j]<<" ";
		}
		cout<<endl;
	}
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
	// vector<vector<int>> matrix = {{70, 70, 70, 70, 1},
	// 							{1, 1, 1, 68, 69},
	// 							{2, 2, 2, 2, 68},
	// 							{3, 3, 3, 3, 67},
	// 							{70, 2, 2, 2, 66}} ;
	vector<vector<int>> matrix = {{1136, 1906, 4541, 1139, 4940, 1307, 249, 1530, 1960, 1314, 3391, 3008, 3756, 614, 251}, 
{511, 2032, 806, 140 ,1878, 4858 ,2817, 8, 2296, 4666, 1647, 3449, 1121, 700, 2317}, 
{3894, 1120, 606, 1063, 949, 442, 531, 214, 4655, 2124, 4847, 4092, 4861, 3491, 2460}, 
{2134, 2882, 4087, 3316, 602, 1392, 205, 3768, 592, 4728, 4044, 2888, 1486, 84, 3770}, 
{1076, 1014, 1184, 1608, 2418, 2715, 2560, 2763, 4473, 3452, 147, 4005, 2558, 1424, 3369}, 
{235, 341, 3403, 1120, 2968, 2834, 4848, 4693, 115, 2512, 647, 3778, 3052, 1266, 3440}, 
{4315, 644, 2752, 2721, 317, 557, 2405, 2469, 1816, 1208, 4574, 3022, 524, 2806, 229}, 
{20, 1971, 569, 4679, 3006, 710, 3116, 2058, 88, 1370 ,280, 499, 806, 4732, 408}, 
{3032, 1544, 4467 ,4951 ,993 ,998, 2733, 1841, 2676, 2270, 4469, 4479, 146, 1412, 979}, 
{2303, 4188, 4001, 2036, 3580, 4793, 15, 1555, 241, 348, 275, 1064, 4972, 1946, 988}, 
{3168, 880, 3769, 4468, 4414, 499, 3104, 964, 1801, 242, 3770, 2541, 4045, 4650, 4772}, 
{4364, 4166, 1025, 4274, 4358, 4939, 27, 2669, 2293, 3255, 1505, 3880, 697, 2262, 2991}} ;
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
  
