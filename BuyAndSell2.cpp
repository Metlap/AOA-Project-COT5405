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

// void task2_dp_bottomup(vector<vector<int>> A, int k){


// int days = A[0].size();
// int stocks = A.size();

// // vector<vector<vector<int>>> DP(m, vector<vector<int>> (k, vector<int> (n,0)));

//   vector<vector<int>> dp(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> stockIndex(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> buyIndex(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> sellIndex(k+1, vector<int> (days+1,-1));

//         for (int j = 0; j <= days; j++){
//             dp[0][j] = 0;
//         }

//         for (int i = 0; i <= k; i++){
//             dp[i][0] = 0;
//         }    

//         for (int i = 1; i <= k; i++) {

//              for(int v = 0; v < stocks; v++) {

//                 for (int j = 1; j < days; j++) {

//                     int buy = 0;
//                     int sell = 0;

//                     int maxFactor = INT_MIN;

//                     // k-1 transactions till before selling at jth index. Hence kth transaction at jth index
//                     for (int prev = 0; prev < j; prev++){
//                        if( maxFactor < (A[v][j] - A[v][prev] + dp[i - 1][prev])){
//                             maxFactor = (A[v][j] - A[v][prev] + dp[i - 1][prev]);
//                             buy = prev+1;
//                             sell = j+1;
//                        }
//                     }
//                   int temp =  maxFactor;
//                   if (maxFactor < dp[i][j - 1]){
//                     temp = dp[i][j - 1];
//                     sell = j;
//                   }

//                   if (temp > dp[i][j]){
//                     dp[i][j] = temp;
//                     stockIndex[i][j] = v+1;
//                     sellIndex[i][j] = sell;
//                     buyIndex[i][j] = buy;
//                   }
//                 }

//                 for (int x = 0; x< A[v].size(); x++){

//                 }

//             }
//         }
//         cout << dp[k][days-1] << endl;

//         for (int i = 0; i <= k; i++) {
//         for (int j = 0; j <= days; j++) {
//             cout << dp[i][j] << " ";
//         }
//         cout << endl;
//         }

//         cout<<"0------"<< endl;

// for (int i = 0; i <= k; i++) {
//         for (int j = 0; j <= days; j++) {
//             cout << stockIndex[i][j] << " ";
//         }
//         cout << endl;
//         }

//         cout<<"0------"<< endl;
//          for (int i = 0; i <= k; i++) {
//         for (int j = 0; j <= days; j++) {
//             cout << buyIndex[i][j] << " ";
//         }
//         cout << endl;
//         }
//     cout<<"0------" << endl;
//          for (int i = 0; i <= k; i++) {
//         for (int j = 0; j <= days; j++) {
//             cout << sellIndex[i][j] << " ";
//         }
//         cout << endl;
//         }



//         int x = k;
//         int y = days-1;
//         while(x>0 && y>0 && dp[x][y] >= 0){
//             cout<< "X :"<<x<<" Y: "<<y<<endl;

//             while(dp[x][y-1] == dp[x][y]){
//                 y--;  
//             }

//             int index = stockIndex[x][y];
//             int start = buyIndex[x][y];
//             int end = sellIndex[x][y];

//             if(y >= buyIndex[x-1][y])
//                 y--;    
   
//             y = buyIndex[x][y];  

//             if(index >0 && start>0 && end > 0 )  
//             cout << index << " " << start << " " << end << " " << endl;
//             k--;
//             x = k;
//              cout<<"second :"<< "K :"<<k<<" Y: "<<y<<endl;
//         }
// }


//Problem -2 ALG5 -Bottom Up DP solution of O(m * n^2 * k) time complexity
void task2_dp_bottomup(vector<vector<int>> A, int k){

int days = A[0].size();
int stocks = A.size();
  
  // 2D DP array -> k+1*n+1 size
  vector<vector<int>> dp(k+1, vector<int> (days+1,-1));
  //Array of k+1*n+1 size for storing the indices of stock, buy date and sell date
  //for the n days and at most k transactions
  // tracker to keep which transactions yield maximum profit
  vector<vector<string>> tracker(k+1, vector<string> (days + 1, ""));

        // Base case - for 0 transactions -> profit = 0
        for (int j = 0; j <= days; j++){
            dp[0][j] = 0;
            tracker[0][j] = "";
        }

        //For day 0 -> no profit possible
        for (int i = 0; i <= k; i++){
            dp[i][0] = 0;
            tracker[i][0] = "";
        }

        for (int i = 1; i <= k; i++) {

            for(int v = 0; v < stocks; v++) 
            {

                for (int j = 1; j < days; j++) {

                    
                    string currentTransactions = "";

                    //maintains index of buy day which yields maximum profit
                    int prevMaxIndex = -1;

                    //maintains transaction details for max profit incase of sell on jth day
                    string maxComb = "";

                    int maxFactor = INT_MIN;

                    // k-1 transactions till before selling at jth index. Hence kth transaction at jth index
                    for (int prev = 0; prev < j; prev++){
                       if( maxFactor < (- A[v][prev] + dp[i - 1][prev])){
                            maxFactor = (- A[v][prev] + dp[i - 1][prev]);
                            prevMaxIndex = prev;
                            maxComb = tracker[i-1][prev];
                       }
                    }

                    // Adding current max yielding profit transaction to already computed max transactions
                    currentTransactions = to_string(v+1) + " " +  to_string(prevMaxIndex+1)  + " " + to_string(j+1) + ((maxComb!="")?("\n"+maxComb):"") ;

                  // k transactions till j-1th day. Hence no sell operation on jth day
                  //Comparing which is larger to fill DP array and set values for back tracking
                  int temp =  maxFactor + A[v][j];

                  if (temp < dp[i][j - 1]){
                    temp = dp[i][j - 1];
                    currentTransactions = tracker[i][-1];
                  }

                  // Checking current profit with already filled value in DP. If greater fill with values corresponding to this transaction
                  if (temp > dp[i][j]){
                    dp[i][j] = temp;
                    tracker[i][j] = currentTransactions;
                  }
                }

            }
        }
        //Maximum profit possible
        cout << tracker[k][days-1] << endl;
}


void findBuyAndSellDays(int m, int n, int k, vector<vector<int> >& prices, vector<vector<int> >& memoization, vector<vector<int> >& kTransactionsList)
{
    int t=k, day = n-1;
    while(t>0)
    {
        if(memoization[t][day] == memoization[t-1][day])
        {
            t=t-1;
            continue;
        }
        else if(memoization[t][day] == memoization[t][day-1])
        {
            day = day-1;
            continue;
        }
        else
        {
            int transactionProfit = memoization[t][day] - memoization[t-1][day-1];
            for (int stockId = 0; stockId<m; stockId++)
            {
                for(int j = day-1; j>=0; j--)
                {
                    if(transactionProfit == prices[stockId][day] - prices[stockId][j])
                    {
                        kTransactionsList.push_back({stockId+1, j+1, day+1});
                        t = t-1;
                        day=day-1;
                        break;
                    }
                }
            }
        }
    }
}

// Problem-1 Algorith-6B Dynamic Programming Using Bottom-up
// int problem2_Alg6b(int m, int n, int k, vector<vector<int> >& A)
// {
//     int minimumPrice = -1;
//     int maxProfit = -1;
//     vector<vector<int> > memoization(k+1, vector<int> (n,0));
//     for (int t = 1; t < k+1; t++)
//     {
//         for(int day = 1; day < n; day++)
//         {
//             int maxVal = memoization[t][day-1];    
//             for(int stockId=0; stockId<m; stockId++)
//             {
//                 for(int j = day-1; j>=0; j--)
//                 {
//                     maxVal = maximum(maxVal, memoization[t-1][j]+A[stockId][day] - A[stockId][j]);
//                 }
//             }
//             memoization[t][day] = maxVal;
//         }
//     }

//     for (int j=0; j < memoization.size(); j++)
//         {
//             for (int j1=0; j1<memoization[j].size(); j1++)
//             {
//                 cout<<memoization[j][j1]<<" ";
//             }
//             cout<<endl;
//         }
//     vector<vector<int> > kTransactionsList;
//     findBuyAndSellDays(m, n, k, A, memoization, kTransactionsList);
//     for (int j=0; j < kTransactionsList.size(); j++)
//         {
//             for (int j1=0; j1<kTransactionsList[j].size(); j1++)
//             {
//                 cout<<kTransactionsList[j][j1]<<" ";
//             }
//             cout<<endl;
//         }
//     return maxProfit;
// }

// void task2_dp_bottomup_optimized(vector<vector<int>> A, int k){


// int days = A[0].size();
// int stocks = A.size();

// // vector<vector<vector<int>>> DP(m, vector<vector<int>> (k, vector<int> (n,0)));

//   vector<vector<int>> dp(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> stockIndex(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> buyIndex(k+1, vector<int> (days+1,-1));
//   vector<vector<int>> sellIndex(k+1, vector<int> (days+1,-1));


//   vector<vector<string>> tracker(k+1, vector<string> (days + 1, ""));

//         for (int j = 0; j <= days; j++){
//             dp[0][j] = 0;
//         }

//         for (int i = 0; i <= k; i++){
//             dp[i][0] = 0;
//         }    

//         for (int i = 1; i <= k; i++) {

//             for(int v = 0; v < stocks; v++) 
//             {

//                 int maxFactor = INT_MIN;

//                 for (int j = 1; j < days; j++) {

//                     int buy = 0;
//                     int sell = 0;

//                     // k-1 transactions till before selling at jth index. Hence kth transaction at jth index

//                        if( maxFactor < ( - A[v][j-1] + dp[i - 1][j-1])){
//                             maxFactor = ( - A[v][j-1] + dp[i - 1][j-1]);
//                             buy = j;
//                        }

//                   int temp =  maxFactor + A[v][j];
//                   if (temp < dp[i][j - 1]){
//                     temp = dp[i][j - 1];
//                     sell = j;
//                   }
//                   else {
//                     sell = j+1;
//                   }

//                   if (temp > dp[i][j]){
//                     dp[i][j] = temp;
//                     stockIndex[i][j] = v+1;
//                     sellIndex[i][j] = sell;
//                     buyIndex[i][j] = buy;
//                   }
//                 }

//             }
//         }
//         cout << dp[k][days-1] << endl;


//         int x = k;
//         int y = days-1;
//         while(k>0 && y>0 && dp[x][y] >= 0){

//             // Max val upto k transactions on day i is same as max value of k transactions upto day i-1
//             while(dp[x][y-1] == dp[x][y]){
//                 y--;  
//             }

//             int index = stockIndex[x][y];
//             int start = buyIndex[x][y];
//             int end = sellIndex[x][y];

//         // Condition to skip checking the same subproblem again
//             if(y >= buyIndex[x-1][y])
//                 y--; 
 
//             y = buyIndex[x][y];   
//             if(index >0 && start>0 && end > 0 )  
//             cout << index << " " << start << " " << end << " " << endl;
//             k--;
//             x = k;
//         }
// }


//  PROBLEM-2 - TASK 6B - Bottom Up DP of O(m*n*k) time complexity 
void task2_dp_bottomup_optimized(vector<vector<int>> A, int k){

int days = A[0].size();
int stocks = A.size();

  vector<vector<int>> dp(k+1, vector<int> (days+1,-1));

  // tracker to keep which transactions yield maximum profit
  vector<vector<string>> tracker(k+1, vector<string> (days + 1, ""));

        for (int j = 0; j <= days; j++){
            dp[0][j] = 0;
            tracker[0][j] = "";
        }

        for (int i = 0; i <= k; i++){
            dp[i][0] = 0;
            tracker[i][0] = "";
        }    

        for (int i = 1; i <= k; i++) {

            for(int v = 0; v < stocks; v++) 
            {
                int maxFactor = INT_MIN;

                string currentTransactions = "";

                //maintains index of buy day which yields maximum profit
                int prevMaxIndex = -1;

                //maintains transaction details for max profit incase of sell on jth day
                string maxComb = "";

                for (int j = 1; j < days; j++) {

                    // k-1 transactions till before selling at jth index. Hence kth transaction at jth index

                       if( maxFactor < ( - A[v][j-1] + dp[i - 1][j-1])){
                            maxFactor = ( - A[v][j-1] + dp[i - 1][j-1]);
                            prevMaxIndex = j-1;
                            maxComb = tracker[i-1][j-1];
                       }

                       // Adding current max yielding profit transaction to already computed max transactions
                       currentTransactions = to_string(v+1) + " " +  to_string(prevMaxIndex+1)  + " " + to_string(j+1) + ((maxComb!="")?("\n"+maxComb):"") ;

                  int temp =  maxFactor + A[v][j];
                  if (temp < dp[i][j - 1]){
                    temp = dp[i][j - 1];
                    currentTransactions = tracker[i][j-1];
                  }
                 
                  if (temp > dp[i][j]){
                    dp[i][j] = temp;
                    tracker[i][j] = currentTransactions; 
                  }
                }

            }
        }
        cout << tracker[k][days-1] << endl;
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



TradeInfo task3_dp_topdown(vector<vector<int>> A, int i, int c, bool buy, unordered_map<string, TradeInfo> &memo, int stock, int buyIndex, int prevStock) {
        if (i >= A[0].size() || stock >= A.size() || stock < 0){
            TradeInfo a;
            return a;
        } 
        //Unique key that holds all path/transaction possibilities
        string key = to_string(i) + " " +to_string(buy) + " "+ to_string(stock);
        if(memo.find(key) == memo.end()) {
            TradeInfo profit = task2_dp_topdown(A, i + 1, c, buy, memo, stock, buyIndex,-1);
            // If already holding a stock    
            if (buy) {
                TradeInfo ps = task3_dp_topdown(A, i+c+1, c, false, memo, stock, -1,-1);
                TradeInfo pu = task3_dp_topdown(A, i+c+1, c, false, memo, stock + 1, -1,-1);
                TradeInfo pd = task3_dp_topdown(A, i+c+1, c, false, memo, stock - 1, -1,-1);
                TradeInfo temp  = compare(compare(ps, pu), pd);
                temp.profit = temp.profit + A[stock][i];
                temp.sellDay = i ;
                profit = compare(profit, temp);
            
            // If we dont hold a stock
            } else {

                TradeInfo ps = task3_dp_topdown(A, i + 1, c, true, memo, stock, i,-1);
                TradeInfo pu;
                TradeInfo pd;
                if(prevStock != stock + 1)
                    pu = task2_dp_topdown(A, i, c, false, memo, stock + 1, -1,-1);;
                if(prevStock != stock - 1)
                    pd = task2_dp_topdown(A,i, c, false, memo, stock-1, -1, stock);

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

// Problem -3 - TASK 9B - BottomUp 
void task3_dp_bottomup_optimized(vector<vector<int>> A, int c) {
        unordered_map<string, TradeInfo> dp;

        int m = A.size() ;
        int n = A[0].size() ;
        for(int i = n-1; i>=0; i--){
            for(int v = 0; v<m; v++){
                string bK = to_string(v) + " " +  to_string(i) + " " +  to_string(true);
                string sK = to_string(v) + " " +  to_string(i) + " " +  to_string(false);
                TradeInfo a;
                TradeInfo skip = (dp.find(to_string(v) + " " +  to_string(i+1) + " " +  to_string(true)) != dp.end())?dp[to_string(v) + " " +  to_string(i+1) + " " +  to_string(true)]: a;
                TradeInfo pu = (dp.find(to_string(v+1) + " " +  to_string(i+c+1) + " " +  to_string(false)) != dp.end())?dp[to_string(v+1) + " " +  to_string(i+c+1) + " " +  to_string(false)]: a;
                TradeInfo ps = (dp.find(to_string(v) + " " +  to_string(i+c+1) + " " +  to_string(false)) != dp.end())?dp[to_string(v) + " " +  to_string(i+c+1) + " " +  to_string(false)]: a;
                TradeInfo pd = (dp.find(to_string(v-1) + " " +  to_string(i+c+1) + " " +  to_string(false)) != dp.end())?dp[to_string(v-1) + " " +  to_string(i+c+1) + " " +  to_string(false)]: a;
                TradeInfo temp = compare(compare(ps, pd), pu);
                temp.sellDay = i;
                temp.profit += A[v][i];
                dp[bK] = compare(temp, skip);

                skip = (dp.find(to_string(v) + " " +  to_string(i+1) + " " +  to_string(false)) != dp.end())?dp[to_string(v) + " " +  to_string(i+1) + " " +  to_string(false)]: a;
                ps = (dp.find(to_string(v) + " " +  to_string(i) + " " +  to_string(true)) != dp.end())?dp[to_string(v) + " " +  to_string(i) + " " +  to_string(true)]: a;
                ps.profit += (-A[v][i]);
                if(ps.sellDay != i)
                ps.comb = to_string(v+1) + " " +  to_string(i+1) + " " +  to_string(ps.sellDay+1) + ((ps.comb != "")?("\n"+ps.comb):"");

                pd = (dp.find(to_string(v-1) + " " +  to_string(i) + " " +  to_string(false)) != dp.end())?dp[to_string(v-1) + " " +  to_string(i) + " " +  to_string(false)]: a;
                dp[sK] = compare(skip, compare(ps, pd));

            }
        }

        cout << dp[to_string(m-1) + " " + to_string(0) + " " + to_string(false)].profit << endl;
        cout << dp[to_string(m-1) + " " + to_string(0) + " " + to_string(false)].comb << endl;
}

int main(int argc, char **argv) {
    int m, n, k;
    // cout << "Enter k:"; 
    // cin >> k;
    // cout<< "Enter m and n:";
    // cin >> m >> n;       
    m = 4;
    n =8;
    k =1;
    vector<vector<int>> A(m, vector<int>(n));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cin >> A[i][j];
    //     }
    // }


 A = { {12, 14, 17, 10, 14, 13, 12, 15},   
{100, 30, 15, 10, 8, 25, 80, 65},
{125, 115, 100, 10, 85, 75, 65, 55},
{10 ,22, 5 ,75 ,65 ,80 ,90, 102}};

    // A = {{12, 14, 17, 10, 14, 13, 12, 15}};
// };

// A = {{1,4,8} , {3,2,6}};

// A = {{12, 14, 10, 9},
// {100, 30, 15, 10},
// {125, 115, 100, 10},
// {100 ,22, 20, 21}};

// A = {{91, 27, 68, 22, 45, 24, 59, 97, 71},
// {16, 28, 40, 75, 66, 41, 90, 47, 79},
// {40, 77, 49, 25, 22, 47, 64, 46, 59},
// {64, 27, 30, 63, 17, 22, 64, 35, 7},
// {16, 61, 71, 12, 49, 85, 82, 7, 23},
// {38, 54, 22, 54, 93, 27, 33, 49 ,44 }};

    // int cmd = stoi(argv[1]);
    // switch (cmd) {
    //     case 1:
            task3_dp_bottomup_optimized(A, k);
            //  cout << "hhhhh";
            // break;
        // case 2:
           // task2_dp_bottomup(A, k);
        //     break;
        // case 3:

            // unordered_map<string, TradeInfo> memo; 
            //     TradeInfo sol3 = task2_dp_topdown(A, 0, k, false, memo, 0, 0,-1);
            //     cout << sol3.comb << endl;
            //     cout << sol3.profit;
         //   break;
        // case 4:
                // vector<vector<int>> max(n, vector<int>(n));
                // vector<vector<int>> stockIndex(n, vector<int>(n));
                // TradeInfo sol3 = task2_bruteforce(A, max, stockIndex, k);
                // cout << sol3.comb;
                // cout << endl << sol3.profit;

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