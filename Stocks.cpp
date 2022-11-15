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
string task1_topdown(vector<vector<int>> A, int m, int n, int max_diff, int max_right, int stock_index, int buy_day, int sell_day, int days_count, int max_right_index){

// End of recurssion for one stock cases
    if(m<0)
    {
        if(max_diff >= 0)
            cout<<stock_index+1<<" "<<buy_day+1<<" "<<sell_day+1;
        else
            cout<<m+2<<" "<<m+2<<" "<<m+2;  // printing the first stock of first index     
       return "";     
    }
    else if(n<0)
    {
            return task1_topdown(A, m-1, days_count, max_diff, 0, stock_index, buy_day, sell_day, days_count, days_count-1);
    }
    else
    {
            if (A[m][n] > max_right)
            {
			    max_right = A[m][n];
                max_right_index = n;
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
                }
            }
       return task1_topdown(A, m, n-1, max_diff, max_right, stock_index, buy_day, sell_day, days_count, max_right_index);
    }
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
  cout << globalProfit << endl;
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

// Problem -2 ALG-5 - Brute force - O(m * n^2k)
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

        // Traversing the DP array to get the indices of stocks and buy and sell dates
        int x = k;
        int y = days-1;
        while(k>0 && y>0 && dp[x][y] >= 0){

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
        }
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



//  PROBLEM-2 - TASK 6B - Bottom Up DP of O(m*n*k) time complexity 
void task2_dp_bottomup_optimized(vector<vector<int>> A, int k){

int days = A[0].size();
int stocks = A.size();

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

    // Traversing the DP array to get the indices of stocks and buy and sell dates
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

        // Condn to skip checking the same subproblem again
            if(y == buyIndex[x-1][y])
                y--; 
 
            y = buyIndex[x][y];   
            if(index >0 && start>0 && end > 0 )  
            cout << index << " " << start << " " << end << " " << endl;
            k--;
            x = k;
        }
}


//###############################################################################################################################################################################

//PROBLEM 3 - ALG-8 - O(m * n^2 ) DP BottomUp Solution

int find(vector<vector<int>> dp,vector<vector<int>> A,int index, int sellTime, int c){

    //int sellVal = A[index][sellTime-1];
    //int profit = dp[2*index+1][sellTime];
    int buyTime = 0;
    for (int i = sellTime-1; i>=0; i--){
       if ( dp[2*index][i] == dp[2*index][sellTime]){
        buyTime = i;
        break;
       } 
    }

   while(dp[2*index][buyTime-1] == dp[2*index][buyTime]){
    buyTime = buyTime -1;
}

    return buyTime;
}

void task3_dp_bottomup(vector<vector<int>> A, int c){

    int days = A[0].size();
    int stocks = A.size();

    // Three possibilities on a particular day -> buy, sell or do nothing(cooldown) 
    //dp[1][i] -> already holds stock on day i -> so sell/ cooldown
    // dp[0][i] -> doesnt hold stock on day i -> so buy/ cooldown 
    vector<vector<int>> dp(2*stocks, vector<int> (days+1,-99999));
    vector<vector<int>> stockIndex(stocks+1, vector<int>(days+1,-1));
    vector<vector<int>> sellIndex(stocks+1, vector<int>(days+1,-1));

    for (int j = 0; j < stocks; j++){

        int buy = 1;
        int sell = 1;

        for(int i = 1; i<= days ; i++){

            int temp = INT_MIN;
            int sellTemp = INT_MIN;

            if(i == 1){

            // Buying on day 1
            if (dp[(2*j) + 0][1] < -A[j][0]){
                dp[(2*j) + 0][1] = -A[j][0];
            }
            dp[(2*j) + 1][1] = 0;
            
            }

            else {

                int buying = INT_MIN;

                //cooldown value
                temp =  dp[(2*j) + 0][i-1];

                if(i-c-1 > 0)
                    buying = dp[(2*j) + 1][i-c-1] - A[j][i-1];

                if(temp < buying) {
                    temp = buying;
                    buy = i;
                }

                if(temp > dp[(2*j) + 0][i]){
                    dp[(2*j) + 0][i] = temp;
                }

                int selling = INT_MIN;

                // selling cooldown
                sellTemp = dp[(2*j) + 1][i-1];
                
                if((i-1) >= 0)
                    selling = dp[(2*j) + 0][i-1] + A[j][i-1];
                
                if(sellTemp < selling) {
                    sellTemp = selling;
                    sell = i;
                }

                if(sellTemp > dp[(2*j) + 1][i]){
                    dp[(2*j) + 1][i] = sellTemp;
                }
            }

        }

    }

    // Traversing the DP array to find the stocks and buy and sell indices/dates
    int sellTime = days;
    int buyTime = days;
    int total =0;
    while (sellTime > 0 && buyTime > 0 ){
        int maxi = 0;
        int index  = 0;
        int y =sellTime;

        for (int i = 0; i< stocks; i++){
            if (dp[(2*i) +1][y] > maxi){
            maxi = dp[2*i +1][y];
            index = i;
            }
        }

        while(dp[2*index +1][y-1] == dp[2*index +1][y]){
            y = y-1;
        }

        total += maxi;
        sellTime = y;
        buyTime = find(dp, A,index,y, c);
        cout << index+1 << " " << buyTime << " " << sellTime << " "<<endl;
        sellTime = buyTime-c-1;
    }

    cout<< endl;
    cout<< "Total profit is : " << total;

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
    cout<<task1_topdown(A, m-1, n-1, -1, n-1, m-1, 0, 0, n-1, n-1);
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
    cout << sol3.comb << endl;
    cout << sol3.profit;
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
//    task3_bruteforce(A,c);
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
    task3_dp_bottomup(A,c);
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
//    task3_dp_topdown(A,c);
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
//    task3_dp_bottomup_optimized(A,c);
    auto stop = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << endl << "Time taken: "
         << timeTaken.count() << " microseconds" << endl;
    }

}