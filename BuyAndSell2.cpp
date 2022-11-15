#include <bits/stdc++.h>
using namespace std;

// Structure to hold info needed about a particular stock - used in memoization
struct TradeInfo {
    string comb = "";
    int profit = 0;
    int sellDay = 0;
};

// Custom comparator to compare which path/ transactions yield best profit -> used in tpdown DP
TradeInfo compare(TradeInfo a, TradeInfo b)
    {
        // If values are the same then
        // return true
        if (a.profit >= b.profit) {
            return a;
        }
        return b;
    }  

// Custom comparator to compare which path/ transactions yield best profit -> used in brute force
TradeInfo stockCompare(TradeInfo a, TradeInfo b)
    {
        // If values are the same then
        // return true
        if (a.profit > b.profit) {
            return a;
        }
        return b;
    }  

void task2_dp_bottomup(vector<vector<int>> A, int k){


int days = A[0].size();
int stocks = A.size();

// vector<vector<vector<int>>> DP(m, vector<vector<int>> (k, vector<int> (n,0)));

  vector<vector<int>> dp(k+1, vector<int> (days+1,-1));
  vector<vector<int>> stockIndex(k+1, vector<int> (days+1,-1));
  vector<vector<int>> buyIndex(k+1, vector<int> (days+1,-1));
  vector<vector<int>> sellIndex(k+1, vector<int> (days+1,-1));

        for (int j = 0; j <= days; j++){
            dp[0][j] = 0;
        }

        for (int i = 0; i <= k; i++){
            dp[i][0] = 0;
        }    

        for (int i = 1; i <= k; i++) {

            for(int v = 0; v < stocks; v++) 
            {

                for (int j = 1; j < days; j++) {

                    int buy = 0;
                    int sell = 0;

                    int maxFactor = INT_MIN;

                    // k-1 transactions till before selling at jth index. Hence kth transaction at jth index
                    for (int prev = 0; prev < j; prev++){
                       if( maxFactor < (A[v][j] - A[v][prev] + dp[i - 1][prev])){
                            maxFactor = (A[v][j] - A[v][prev] + dp[i - 1][prev]);
                            buy = prev+1;
                            sell = j+1;
                       }
                    }
                  int temp =  maxFactor;
                  if (maxFactor < dp[i][j - 1]){
                    temp = dp[i][j - 1];
                    sell = j;
                  }

                  if (temp > dp[i][j]){
                    dp[i][j] = temp;
                    stockIndex[i][j] = v+1;
                    sellIndex[i][j] = sell;
                    buyIndex[i][j] = buy;
                  }
                }

            }
        }
        cout << dp[k][days-1] << endl;

        for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= days; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
        }

        cout<<"0------"<< endl;

for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= days; j++) {
            cout << stockIndex[i][j] << " ";
        }
        cout << endl;
        }

        cout<<"0------"<< endl;
         for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= days; j++) {
            cout << buyIndex[i][j] << " ";
        }
        cout << endl;
        }
    cout<<"0------" << endl;
         for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= days; j++) {
            cout << sellIndex[i][j] << " ";
        }
        cout << endl;
        }



        int x = k;
        int y = days-1;
        while(k>0 && y>0 && dp[x][y] >= 0){
            cout<< "K :"<<k<<" Y: "<<y<<endl;

            while(dp[x][y-1] == dp[x][y]){
                y--;  
            }
            int index = stockIndex[x][y];
            int start = buyIndex[x][y];
            int end = sellIndex[x][y];

            if(y == buyIndex[x-1][y])
                y--;    
   
            y = buyIndex[x][y];  

            if(index >0 && start>0 && end > 0 )  
            cout << index << " " << start << " " << end << " " << endl;
            k--;
            x = k;
             cout<<"second :"<< "K :"<<k<<" Y: "<<y<<endl;
        }
}

void task2_dp_bottomup_optimized(vector<vector<int>> A, int k){


int days = A[0].size();
int stocks = A.size();

// vector<vector<vector<int>>> DP(m, vector<vector<int>> (k, vector<int> (n,0)));

  vector<vector<int>> dp(k+1, vector<int> (days+1,-1));
  vector<vector<int>> stockIndex(k+1, vector<int> (days+1,-1));
  vector<vector<int>> buyIndex(k+1, vector<int> (days+1,-1));
  vector<vector<int>> sellIndex(k+1, vector<int> (days+1,-1));

        for (int j = 0; j <= days; j++){
            dp[0][j] = 0;
        }

        for (int i = 0; i <= k; i++){
            dp[i][0] = 0;
        }    

        for (int i = 1; i <= k; i++) {

            for(int v = 0; v < stocks; v++) 
            {

                int maxFactor = INT_MIN;

                int buy = 0;
                int sell = 0;

                for (int j = 1; j < days; j++) {

                    // k-1 transactions till before selling at jth index. Hence kth transaction at jth index

                       if( maxFactor < ( - A[v][j-1] + dp[i - 1][j-1])){
                            maxFactor = ( - A[v][j-1] + dp[i - 1][j-1]);
                            buy = j;
                       }

                  int temp =  maxFactor + A[v][j];
                  if (temp < dp[i][j - 1]){
                    temp = dp[i][j - 1];
                    sell = j;
                  }
                  else {
                    sell = j+1;
                  }

                  if (temp > dp[i][j]){
                    dp[i][j] = temp;
                    stockIndex[i][j] = v+1;
                    sellIndex[i][j] = sell;
                    buyIndex[i][j] = buy;
                  }
                }

            }
        }
        cout << dp[k][days-1] << endl;


        int x = k;
        int y = days-1;
        while(k>0 && y>0 && dp[x][y] >= 0){

            // Max val upto k transactions on day i is same as max value of k transactions upto day i-1
            while(dp[x][y-1] == dp[x][y]){
                y--;  
            }

            int index = stockIndex[x][y];
            int start = buyIndex[x][y];
            int end = sellIndex[x][y];

        // Condition to skip checking the same subproblem again
            if(y == buyIndex[x-1][y])
                y--; 
 
            y = buyIndex[x][y];   
            if(index >0 && start>0 && end > 0 )  
            cout << index << " " << start << " " << end << " " << endl;
            k--;
            x = k;
        }
}


TradeInfo task2_dp_topdown(vector<vector<int>> A, int i, int k, bool buy, unordered_map<string, TradeInfo> &memo, int stock, int buyIndex, int prevStock) {
        if (i >= A[0].size()|| k == 0 || stock >= A.size() || stock < 0){
            TradeInfo a;
            return a;
        } 
        //Unique key that holds all path/transaction possibilities
        string key = to_string(i) + " " + to_string(k) + " " +to_string(buy) + " "+ to_string(stock);
        if(memo.find(key) == memo.end()) {
            TradeInfo profit = task2_dp_topdown(A, i + 1, k, buy, memo, stock, buyIndex,-1);
            // If already holding a stock    
            if (buy) {
                TradeInfo ps = task2_dp_topdown(A, i, k - 1, false, memo, stock, -1,-1);
                TradeInfo pu = task2_dp_topdown(A, i, k - 1, false, memo, stock + 1, -1,-1);
                TradeInfo pd = task2_dp_topdown(A, i, k - 1, false, memo, stock - 1, -1,-1);
                TradeInfo temp  = compare(compare(ps, pu), pd);
                temp.profit = temp.profit + A[stock][i];
                temp.sellDay = i ;
                profit = compare(profit, temp);
            
            // If we dont hold a stock
            } else {

                TradeInfo ps = task2_dp_topdown(A, i + 1, k, true, memo, stock, i,-1);
                TradeInfo pu;
                TradeInfo pd;
                if(prevStock != stock + 1)
                    pu = task2_dp_topdown(A, i, k, false, memo, stock + 1, -1,-1);;
                if(prevStock != stock - 1)
                    pd = task2_dp_topdown(A,i, k, false, memo, stock-1, -1, stock);

                ps.profit = ps.profit - A[stock][i];
                ps.comb = to_string(stock+1) + " " + to_string(i+1) + " " + to_string(ps.sellDay+1) 
                + ((ps.comb!="")?("\n"+ps.comb):"");
                profit = compare(profit, ps);
                profit = compare(profit, pu);
                profit = compare(profit, pd);
            }
            // Store the value in DP(map) that can be used for subsequent calls
            memo[key] = profit;
        }
        return memo[key];
    }

TradeInfo task2_bruteforce_recursive(vector<vector<int>> A, vector<vector<int>> &max, vector<vector<int>> &stockIndex, int n, int k, int currStock)  {

        if(k == 0)
            {
                TradeInfo a;
                a.comb = "";
                return a ;
            }

        TradeInfo currProfit;
        for(int i = 1; i <= n; i++) {
            string pathTraversal = "";
            for (int j = i - 1; j >= 0; j--) {
                TradeInfo temp;
                // checking for sell price - buy price for kth transaction
                int t = A[currStock][i] - A[currStock][j];
                if (t > max[j][i]) {
                    max[j][i] = t;
                    stockIndex[j][i] = currStock;
                }

                if(max[j][i] > 0)
                    pathTraversal = to_string(stockIndex[j][i]+1) + " " + to_string(j+1) + " " + to_string(i+1);

                // Problem solved from index j till i for kth transaction (for each j and i iteratively for each stock) - left with k-1 transactions
                TradeInfo nextSubProb = task2_bruteforce_recursive(A, max, stockIndex, j, k - 1, currStock);
                temp.profit += nextSubProb.profit + max[j][i];

                // temp.comb = comb + ((sub.comb != "")?( ((comb == "")?"":",") + sub.comb):"");
                if(pathTraversal == "" && nextSubProb.comb == ""){
                    temp.comb = "";
                }
                else if(pathTraversal == "" && nextSubProb.comb != ""){
                    temp.comb = nextSubProb.comb ;
                }
                else if(pathTraversal != "" && nextSubProb.comb == ""){
                    temp.comb = pathTraversal;
                }
                else {
                    temp.comb = pathTraversal + "\n" + nextSubProb.comb;
                }
                //temp.comb = pathTraversal + ((nextSubProb.comb != "")?(","+nextSubProb.comb):"");
                //temp.comb = pathTraversal + ((nextSubProb.comb != "")?( ((pathTraversal  == "" ) ? "": ",") + nextSubProb.comb):"");
                currProfit = compare(temp, currProfit);
                // cout << "t is :: " << temp.comb << endl;
            }
        }
        return currProfit;
    }

TradeInfo task2_bruteforce(vector<vector<int>> A, vector<vector<int>> &max, vector<vector<int>> &stockIndex, int k) {

        TradeInfo maxProfit;
       // int[][] mToS = new int[prices[0].length][prices[0].length];
       int n = A[0].size();

        //Looping over m days 
        for(int i = 0; i < A.size(); i++){
            maxProfit = compare(maxProfit, task2_bruteforce_recursive(A, max, stockIndex, n-1, k, i));
        }

        return maxProfit;

    }


// void task3_bottomup_optimized(vector<vector<int>> A )  {

//      vector<int> dp(n+1,0);

//      int n = A[0].size();
//      int m = A.size();

//      for(int i = 0 ; i < m; i++){
//         for(int j = 0; j <)
//      }
// }

int main(int argc, char **argv) {
    int m, n, k;
    // cout << "Enter k:"; 
    // cin >> k;
    // cout<< "Enter m and n:";
    // cin >> m >> n;       
    m = 4;
    n =8;
    k =2;
    vector<vector<int>> A(m, vector<int>(n));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cin >> A[i][j];
    //     }
    // }

    A = {{12, 14, 17, 10, 14, 13, 12, 15},   
{100, 30, 15, 10, 8, 25, 80, 65},
{125, 115, 100, 10, 85, 75, 65, 55},
{10 ,22, 5 ,75 ,65 ,80 ,90, 102}};

// A = {{1,4,8} , {3,2,6}};

// A = {{12, 14, 10, 9},
// {100, 30, 15, 10},
// {125, 115, 100, 10},
// {100 ,22, 20, 21}};

    // int cmd = stoi(argv[1]);
    // switch (cmd) {
    //     case 1:
            //task2_dp_bottomup_optimized(A, k);
            // break;
        // case 2:
           // task2_dp_bottomup(A, k);
        //     break;
        // case 3:

            // unordered_map<string, TradeInfo> memo; 
            //     TradeInfo sol3 = task2_dp_topdown(A, 0, k, false, memo, 0, 0,-1);
            //     cout << sol3.comb;
         //   break;
        // case 4:
                vector<vector<int>> max(n, vector<int>(n));
                vector<vector<int>> stockIndex(n, vector<int>(n));
                TradeInfo sol3 = task2_bruteforce(A, max, stockIndex, k);
                cout << sol3.comb;
                cout << endl << sol3.profit;

        //         System.out.println(profit.profit);
        // System.out.println(string.join("\n", profit.comb.split(",")));
        //     break;
        // case 5:
        //     task5_smart(p, m, n, h);
        //     break;
    //     default:
    //         break;
    // }

}