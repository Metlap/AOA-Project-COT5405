#include <bits/stdc++.h>
using namespace std;

//Bruteforce

// Greedy algorithm
void task1_greedy(vector<vector<int>> A){

int n = A[0].size();
int m = A.size();

int globalProfit = INT_MIN;
int buyIndex, sellIndex = 0;
int stockIndex = 0;

for(int j = 0; j<m ; j++){

    vector<int> dayOne = A[j];
    int max_profit = 0;
    int buy = A[j][0];
    int sell = A[j][0];

    for (int i = 1; i < n; i++) {
 
        // Checking for lower buy value
        if (buy > dayOne[i])
            buy = dayOne[i];
 
        // Checking for higher profit
        else if (dayOne[i] - buy > max_profit){
            max_profit = dayOne[i] - buy;
            sell = i;
        }
    
        }

        if(globalProfit < max_profit){

        globalProfit = max_profit;
        sellIndex = sell;
        stockIndex = j+1; 
        std::vector<int>::iterator it;
        it = std::find (dayOne.begin(), dayOne.end(), (dayOne[sell] - max_profit));
        if (it != dayOne.end())
            {
            buyIndex = it - dayOne.begin();
            }
        }


}
   cout << globalProfit << endl;
   cout << stockIndex  << " " << buyIndex+1 << " " << sellIndex+1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void task1_dp_bottomup(vector<vector<int>> A){


int n = A[0].size();
int m = A.size();

vector<vector<int>> DP(m, vector<int> (n, 0));

int globalProfit = INT_MIN;
int buyIndex, sellIndex = 0;
int stockIndex = 0;

for(int j = 0; j<m ; j++){

    DP[j][0] = 0;
    vector<int> dayOne = A[j];
    int max_profit = 0;
    int buy = A[j][0];
    int sell = A[j][0];

    for(int i = 1; i < n; i++) {
 
        DP[j][i] = max(DP[j][i-1] + A[j][i] - A[j][i-1], 0 );
        if(DP[j][i] > max_profit) {
            max_profit = DP[j][i]; 
            sell = i;
        }
    }

    if(globalProfit < max_profit){

        globalProfit = max_profit;
        sellIndex = sell;
        stockIndex = j+1; 
        std::vector<int>::iterator it;
        it = std::find (dayOne.begin(), dayOne.end(), (dayOne[sell] - max_profit));
        if (it != dayOne.end())
            {
            buyIndex = it - dayOne.begin();
            }
        }

}
 // cout << globalProfit << endl;
  cout << stockIndex  << " " << buyIndex+1 << " " << sellIndex+1;
}

void bruteforce(vector<vector<int>> A){

int n = A[0].size();
int m = A.size();
int stock_index = 0, buy_day = 0, sell_day = 0;
int i,j,k;
int max_diff = -1;

 for (i = 0; i < m; i++) 
    {
        for (j = 0; j < n; j++) 
        {   
            for (k = j+1; k < n; k++) 
            {
               if (A[i][k] - A[i][j] > max_diff)
                {
                    max_diff = A[i][k]  - A[i][j] ;
                    stock_index = i;
                    buy_day = j;
                    sell_day = k;
                }
            }
        }
}

if(max_diff == -1)
{
    cout<<m<<" "<<A[m-1][m-1]<<" "<<A[m-1][m-1];
}
else
{
cout<<stock_index+1<<" "<<buy_day+1<<" "<<sell_day+1;
}

}

string recursive_memoization(vector<vector<int>> A, int m, int n, int max_diff, int max_right, int stock_index, int buy_day, int sell_day, int days_count, int max_right_index){

    if(m<0)
    {
        if(max_diff >= 0)
            cout<<stock_index+1<<" "<<buy_day+1<<" "<<sell_day+1;//<<" "<<max_diff<<endl;
        else
            cout<<m+2<<" "<<m+2<<" "<<m+2;  // printing the first stock of first index     
       return "";     
    }
    else if(n<0)
    {
           // cout<<"m :"<<m<<" "<<stock_index+1<<" "<<buy_day+1<<" "<<sell_day+1<<" "<<max_diff<<endl;
            return recursive_memoization(A, m-1, days_count, max_diff, 0, stock_index, buy_day, sell_day, days_count, days_count-1);
    }
    else
    {
            if (A[m][n] > max_right)
            {
			    max_right = A[m][n];
                max_right_index = n;
              // cout<<" max_right : "<<max_right<<" sell_day : "<<sell_day<<" m: "<<m<<" n: "<<n<<endl;
            }
            else
	    	{
    			int diff = max_right - A[m][n];

    			if(diff > max_diff)
                {
                    max_diff = diff;
                    stock_index = m;
                    buy_day = n;
                    sell_day =  max_right_index;
                   // cout<<stock_index<<" "<<buy_day<<" "<<sell_day<<" max_diff : "<<max_diff<<" m: "<<m<<" n: "<<n<<endl;
                }
            }
       //cout<<"m : "<<m<<" n : "<<n<<endl;
       return recursive_memoization(A, m, n-1, max_diff, max_right, stock_index, buy_day, sell_day, days_count, max_right_index);
    }
}


int main(int argc, char **argv) {
    int m, n;
 //   cin >>m>>n;
  m =4;
  n =8;

  vector<vector<int>> A(m, vector<int>(n));

  A = {{12, 14, 10, 9},   
{100, 30, 15, 10},
{125, 115, 100, 10},
{100 ,22, 15, 9}};

//       A = {{12, 14, 17, 10, 14, 13, 12, 15},   
// {100, 30, 15, 10, 8, 25, 80, 65},
// {125, 115, 100, 10, 85, 75, 65, 55},
// {10 ,22, 5 ,75 ,65 ,80 ,90, 102}};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    // int cmd = stoi(argv[1]);
    // switch (cmd) {
    //     case 1:
        //    task1_greedy(A);
        //     break;
        // case 2:
             task1_dp_bottomup(A);
            // cout<<recursive_memoization(A, m-1, n-1, -1, n-1, m-1, 0, 0, n-1, n-1);
        //    break;
        // case 3:
        //     task1_bruteforce(A);
        //     break;
        // case 4:
        //     task4_smart(p, m, n, h);
        //     break;
        // case 5:
        //     task5_smart(p, m, n, h);
        //     break;
    //     default:
    //         break;
    // }

}