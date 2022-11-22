#include <bits/stdc++.h>
using namespace std;

// Problem-1 - TASK 1 - Brute force
void task1_bruteforce(vector<vector<int>> A){

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

// Problem - 1 - TASK 2 - Greedy solution
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
// cout << globalProfit << endl;
   cout << stockIndex  << " " << buyIndex+1 << " " << sellIndex+1;
}


// Problem 1 - TASK 3A - Top Down DP - Recursive Memoization
int getmax_profit(vector<vector<int>> &dp, vector<vector<int>> &A, int m, int n)
{
    if(dp[m][n] == -1)
    {
        dp[m][n] = max(getmax_profit(dp,A,m,n-1)+A[m][n]-A[m][n-1],0);
    }
    return dp[m][n];
}

void task1_topdown(vector<vector<int>> &A, int m, int n)
{
    int max_profit = 0;
    int stock_index = 0;
    int buy_day = 0;
    int sell_day = 0;
    int buy_index = 0;
    vector<vector<int>> dp(m, vector<int>(n, -1));
    for(int i = 0; i < m; i++)
    {
        dp[i][0]=0;
        int value = getmax_profit(dp, A, i, n-1);
    }
    
    for(int i = 0 ; i < m ; i++)
    {
        buy_index = 0;

        for( int j = 1; j < n; j++)
        {
            if(dp[i][j]==0)
            {
                buy_index = j;
            }
            if(dp[i][j]>max_profit)
            {

                max_profit = dp[i][j];
                stock_index = i;
                buy_day = buy_index;
                sell_day = j;
            }
            
        }
    }
    cout<<stock_index+1<<" "<<buy_day+1<<" "<<sell_day+1;
    //return max_profit;
}

// Problem 1 - TASK 3B - Bottom Up DP Solution
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
  //cout << globalProfit << endl;
  cout << stockIndex  << " " << buyIndex+1 << " " << sellIndex+1;
}

//####################################################################################################################################################

// PROBLEM -2


// Structure to hold info needed about a particular stock - used in memoization
struct TradeInfo {
    string comb = "";
    int profit = 0;
    int sellDay = 0;
};

// Custom comparator to compare which path/ transactions yield best profit
TradeInfo compare(TradeInfo a, TradeInfo b)
    {
        // If values are the same then
        // return true
        if (a.profit >= b.profit) {
            return a;
        }
        return b;
    }

// Problem -2 ALG-4 - Brute force - O(m * n^(2k))
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
                currProfit = compare(temp, currProfit);
            }
        }
        return currProfit;
    }

TradeInfo task2_bruteforce(vector<vector<int>> A, vector<vector<int>> &max, vector<vector<int>> &stockIndex, int k) {

        TradeInfo maxProfit;
        int n = A[0].size();

        //Looping over m days 
        for(int i = 0; i < A.size(); i++){
            maxProfit = compare(maxProfit, task2_bruteforce_recursive(A, max, stockIndex, n-1, k, i));
        }

        return maxProfit;

    }

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

                    int maxFactor = INT_MIN;

                    string currentTransactions = "";

                    //maintains index of buy day which yields maximum profit
                    int prevMaxIndex = -1;

                    //maintains transaction details for max profit incase of sell on jth day
                    string maxComb = "";

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
                    currentTransactions = tracker[i][j-1];
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


//PROBLEM -2 - TASK 6A - Topdown DP
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
                    pu = task2_dp_topdown(A, i, k, false, memo, stock + 1, -1,-1);
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



//  PROBLEM-2 - TASK 6B - Bottom Up DP of O(m*n*k) time complexity 
void task2_dp_bottomup_optimized(vector<vector<int>> A, int k){

int days = A[0].size();
int stocks = A.size();
  
  // 2D DP array -> k+1*n+1 size
  vector<vector<int>> dp(k+1, vector<int> (days+1,-1));

  //Array of k+1*n+1 size for storing the indices of stock, buy date and sell date
  //for the n days and at most k transactions
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


                  // k transactions till j-1th day. Hence no sell operation on jth day
                  //Comparing which is larger to fill DP array and set values for back tracking
                  int temp =  maxFactor + A[v][j];
                  if (temp < dp[i][j - 1]){
                    temp = dp[i][j - 1];
                    currentTransactions = tracker[i][j-1];
                  }

                  // Checking current profit with already filled value in DP. If greater fill with values corresponding to this transaction
                  if (temp > dp[i][j]){
                    dp[i][j] = temp;
                    tracker[i][j] = currentTransactions;
                  }
                }

            }
        }
        cout << tracker[k][days-1] << endl;

}


//###############################################################################################################################################################################


// PROBLEM 3 - ALG- 7 - O(m * 2^n) - Brute Force Solution
TradeInfo task3_brutefroce_recursive(bool brought, int i, int n, vector<int> A, int c, vector<TradeInfo> &optimal, int stock) {
        if(i >= n){
            TradeInfo a;
            return a;
        }

        TradeInfo profit = task3_brutefroce_recursive(brought, i+1, n, A, c, optimal, stock);
        if(brought) {
            TradeInfo temp = task3_brutefroce_recursive(false, i + c + 1, n, A, c, optimal, stock);

            temp.profit += A[i];
            temp.sellDay = i;
            profit = compare(profit, temp);
            return profit;
        }
        else {
            TradeInfo ps = task3_brutefroce_recursive(true, i + 1, n, A, c, optimal, stock);
            ps.profit = ps.profit - A[i];
            ps.comb = to_string(stock+1) +  " " + to_string(i+1) +  " " + to_string(ps.sellDay+1) + ((ps.comb != "")?("\n"+ps.comb):"");
            profit = compare(ps, profit);
        
        optimal[i] = compare(profit, optimal[i]);
        return optimal[i];

    }
}

    void task3_brutefroce(vector<vector<int>> A, int c) {
        vector<TradeInfo> optimal(A[0].size());
        // Initializing optimal array to store the TradeInfo Objects
        TradeInfo a;
        for(int i = 0; i < optimal.size(); i++){

            optimal[i] = a;
        }
        TradeInfo profit;

        //Each day buy/sell option for n days leads to 2^n time complexity
        for(int j = 0; j < 2; j++) {
            for (int i = 0; i < A.size(); i++)
                profit = compare(profit, task3_brutefroce_recursive(false, 0, A[0].size(), A[i], c, optimal, i));
        }
        // cout << profit.profit << endl;
        cout << profit.comb << endl;
    }


//PROBLEM 3 - TASK 8 - BottomUp O(m * n^2)
int task3_bottom_up_mn2(vector<vector<int>> A, int c, vector<vector<int>> &maxi, vector<vector<string>> &store) {

        for(int s = 0; s < A.size(); ++s) {
            maxi[0][0] = 0;
            int t = A[s][1] - A[s][0];
            if (t > maxi[1][0]) {
                store[1][0] =  to_string(s) + " " + to_string(0) + " " + to_string(1);
            }

            maxi[1][0] = max(maxi[1][0], t);

            for(int i = 2; i < A[0].size(); ++i) {
                int temp = false;
                string comb = "";
                if (maxi[i - 1][0] > maxi[i][0]) {
                    store[i][0] = store[i - 1][0];
                }

                maxi[i][0] = max(maxi[i][0], maxi[i - 1][0]);

                for(int j = i - 1; j >= 0; --j) {
                    t = A[s][i] - A[s][j];
                    if (t > maxi[i][j]) {
                        comb = to_string(s+1) + " " + to_string(j+1) + " " + to_string(i+1);
                        store[i][j] = comb;
                    }

                    maxi[i][j] = max(t, maxi[i][j]);
                    int prevIndex = j - (c + 1);
                    if (maxi[i][j] + (prevIndex < 0 ? 0 : maxi[prevIndex][0]) > maxi[i][0]) {
                        store[i][0] = store[i][j] + (prevIndex < 0 ? "" : (store[prevIndex][0] != "" ? "\n" + store[prevIndex][0] : ""));
                    }

                    maxi[i][0] = max(maxi[i][j] + (prevIndex < 0 ? 0 : maxi[prevIndex][0]), maxi[i][0]);
                }
            }
        }
        return maxi[A[0].size() - 1][0];
    }


// PROBLEM 3 - TASK 9A - Memoization
TradeInfo task3_dp_topdown(vector<vector<int>> A, int i, int c, bool buy, unordered_map<string, TradeInfo> &memo, int stock, int buyIndex, int prevStock) {
       
        if (i >= A[0].size() || stock >= A.size() || stock < 0){
            TradeInfo a;
            return a;
        } 
        //Unique key that holds all path/transaction possibilities
        string key = to_string(i) + " " + to_string(buy) + " "+ to_string(stock);
        if(memo.find(key) == memo.end()) {
            TradeInfo profit = task3_dp_topdown(A, i + 1, c, buy, memo, stock, buyIndex,-1);
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
                    pu = task3_dp_topdown(A, i, c, false, memo, stock + 1, -1,-1);
                if(prevStock != stock - 1)
                    pd = task3_dp_topdown(A,i, c, false, memo, stock-1, -1, stock);

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

        //cout << dp[to_string(m-1) + " " + to_string(0) + " " + to_string(false)].profit << endl;
        cout << dp[to_string(m-1) + " " + to_string(0) + " " + to_string(false)].comb << endl;
}


int main(int argc, char **argv) {
    int m, n, k, c;
    string cmd;
  
  if(argv[1] != NULL)
    cmd = argv[1];

    if (cmd == "1"){
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task1_bruteforce(A);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "2"){
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task1_greedy(A);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    
    }

    if (cmd == "3a"){
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task1_topdown(A, m, n);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "3b"){
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task1_dp_bottomup(A);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "4"){
        cin >> k;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    
    vector<vector<int>> max(n, vector<int>(n));
    vector<vector<int>> stockIndex(n, vector<int>(n));
    TradeInfo sol3 = task2_bruteforce(A, max, stockIndex, k);
    cout << sol3.comb;
    cout << endl << sol3.profit;    

    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "5"){
        cin >> k;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task2_dp_bottomup(A, k);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "6a"){
        cin >> k;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    unordered_map<string, TradeInfo> memo; 
    TradeInfo sol3 = task2_dp_topdown(A, 0, k, false, memo, 0, 0,-1);
    cout << sol3.comb;
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "6b"){
        cin >> k;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task2_dp_bottomup_optimized(A,k);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "7"){
        cin >> c;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    // unordered_map<string, TradeInfo> memo; 
    // TradeInfo sol3 = task3_brutefroce(A, 0, c, false, memo, 0, 0,-1);
    // cout << sol3.comb;
    task3_brutefroce(A, c);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "8"){
        cin >> c;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> maxi(n, vector<int>(n));
    vector<vector<string>> store(n, vector<string>(n));
    int profit = task3_bottom_up_mn2(A, c, maxi, store);
    //cout << profit << endl;
    cout << store[A[0].size() - 1][0] << endl; 
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "9a"){
        cin >> c;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    unordered_map<string, TradeInfo> memo; 
    TradeInfo sol3 = task3_dp_topdown(A, 0, c, false, memo, 0, 0,-1);
    cout << sol3.comb;
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

    if (cmd == "9b"){
        cin >> c;
        cin >> m >> n;
        vector<vector<int>> A(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    task3_dp_bottomup_optimized(A,c);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

}