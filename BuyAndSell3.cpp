#include <bits/stdc++.h>
using namespace std;

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
    // vector<int> buyIndex(days+1,INT_MIN);
    vector<vector<int>> sellIndex(stocks+1, vector<int>(days+1,-1));

// vector<vector<int>> sellIndex[stocks+1];
// vector<vector<int>> stockIndex[stocks+1];

    if (days < 2) {
        cout << "No transaction yields profit greater than 0: ";
        //return;
    }

    // dp[0][0] = INT_MIN;
    // dp[1][0] = INT_MIN;
//    dp[0][1] = -A[0][0];
    //buyIndex[1] = 1;
//    stockIndex[1] = 1;

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
                //buyIndex[i] = buy;
//                stockIndex[j][i] = j+1;
            }
            dp[(2*j) + 1][1] = 0;
            }
            else{

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
                //    stockIndex[i]= j+1;
                //    buyIndex[i] = buy;
                //     if( dp[0][i] > dp[0][i-1]){
                //     stockIndex[i]= j+1;
                //     buyIndex[i] = buy;
                // }
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
                 //   stockIndex[i]= j+1;
                 //   sellIndex[i] = sell;
                    // if ( (dp[(2*j) + 1][i] > dp[(2*j) + 1][i-1]) && ((i+1) <= days) && !(dp[(2*j) + 1][i] < dp[(2*j) + 1][i+1]))
                    // {
                    //     stockIndex[j][i]= j+1;
                    //     sellIndex[j][i] = sell;
                    // }
                 
                }
            }

        }

    }


// cout<< dp[1][days] << endl;
// cout<< dp[3][days] << endl;


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
if(buyTime > 0 && sellTime > 0)
cout << index+1 << " " << buyTime << " " << sellTime << " "<<endl;
sellTime = buyTime-c-1;
}
cout<< endl;
cout<< total;




// int maxi = 0;
// int index  = 0;
// int sellTime = 0;
// int buyTime = 0;
// int y =days;
// int x = stocks;
// for (int i = 0; i< stocks+1; i++){
//     if (dp[2*i +1][y] > maxi){
//         maxi = dp[2*i +1][y];
//         index = i;
//     }
// }

// while(dp[2*index +1][y-1] < dp[2*index +1][y]){
//     y = y-1;
// }

// sellTime = y;
// buyTime = find(dp, A,index,sellTime, c);

// cout << index << " " << buyTime << " " << sellTime << " "<<endl;


//--------------------------------------------------------------------------------------------


// int sellTime = days;
// int buyTime = days;
// while (sellTime > 0 && buyTime > 0 ){
// int maxi = 0;
// int index  = 0;
// int y =sellTime;
// for (int i = 0; i< stocks; i++){
//     if (dp[(2*i) +1][y] > maxi){
//         maxi = dp[2*i +1][y];
//         index = i;
//     }
// }

// while(dp[2*index +1][y-1] == dp[2*index +1][y]){
//     y = y-1;
// }

// sellTime = y;
// buyTime = find(dp, A,index,sellTime, c);

// cout << index << " " << buyTime << " " << sellTime << " "<<endl;
// }

// for (int i = 0; i<= days; i++){
//     cout << dp[0][i] << " ";
// }
// cout<< endl;
// for (int i = 0; i<= days; i++){
//     cout << dp[1][i] << " ";
// }
// cout<< endl;
// for (int j = 0; j<= stocks; j++){
// for (int i = 0; i<= days; i++){
//     cout << stockIndex[j][i] << " ";
// }
// cout<< endl;
// }
// // cout<< endl;
// // for (int i = 0; i<= days; i++){
// //     cout << buyIndex[i] << " ";
// // }
// cout<< endl;
// for (int j = 0; j<= stocks; j++){
// for (int i = 0; i<= days; i++){
//     cout << sellIndex[j][i] << " ";
// }
// cout<< endl;
// }
// cout<< endl;
}


void task3_dp_bottomup_optimized(vector<vector<int>> A, int c){

    int days = A[0].size();
    int stocks = A.size();

    // Three possibilities on a particular day -> buy, sell or do nothing(cooldown) 
    //dp[1][i] -> already holds stock on day i -> so sell/ cooldown
    // dp[0][i] -> doesnt hold stock on day i -> so buy/ cooldown 
    vector<vector<int>> dp(2*stocks, vector<int> (days+1,-99999));

    vector<vector<int>> sellIndex(stocks);
    vector<vector<int>> buyIndex(stocks);

// vector<vector<int>> sellIndex[stocks+1];
// vector<vector<int>> stockIndex[stocks+1];

    if (days < 2) {
        cout << "No transaction yields profit greater than 0: ";
        //return;
    }

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
            else{

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

                     if( dp[2*j][i] > dp[2*j][i-1]){

                        int size = buyIndex[j].size();
                        if(size == 0){
                            buyIndex[j].push_back(dp[(2*j)][i]);
                        }
                        else {
                        int lastElem = sellIndex[j].back();
                        if (lastElem ==  dp[(2*j) + 1][i-1])
                            {
                                sellIndex[j].back() = dp[(2*j) + 1][i];
                            }
                        else {
                            sellIndex[j].push_back(dp[(2*j) + 1][i]);
                        }
                        }
                   buyIndex[j].push_back(i);
                 }
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

                    if ( dp[(2*j) + 1][i] > dp[(2*j) + 1][i-1] ){
                        int size = sellIndex[j].size();
                        if(size == 0){
                            sellIndex[j].push_back(dp[(2*j) + 1][i]);
                        }
                        else {
                        int lastElem = sellIndex[j].back();
                        if (lastElem ==  dp[(2*j) + 1][i-1])
                            {
                                sellIndex[j].back() = dp[(2*j) + 1][i];
                            }
                        else {
                            sellIndex[j].push_back(dp[(2*j) + 1][i]);
                        }
                        }
                    }
                 
                }
            }

        }
    }

// cout<< dp[1][days] << endl;
// cout<< dp[3][days] << endl;


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
cout<< total;
}


int main(int argc, char **argv) {
    // Here c is the cooldown period after a Sell operation
    int m, n, c;
    // cout << "Enter c:"; 
    // cin >> c;
    // cout<< "Enter m and n:";
    // cin >> m >> n;       
    m = 2;
    n =10;
    c =0;
    vector<vector<int>> A(m, vector<int>(n));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cin >> A[i][j];
    //     }
    // }

//     A = {
// {100, 30, 15, 10, 8, 25, 80, 65},
// {125, 115, 100, 10, 85, 75, 65, 55},
// {10 ,22, 5 ,75 ,65 ,80 ,90, 102},
// {12, 14, 17, 10, 14, 13, 12, 15}};



// A = {{12, 14, 10, 9},   
// {100, 30, 15, 10},
// {125, 115, 100, 10},
// {100 ,22, 15, 9}};
// A= { {1,2,3,0,2}, {5,4,3,2,10}};

A = {{14, 10, 10, 6, 2, 12, 11, 4, 5, 9},
                               {14, 13, 14, 2, 8, 8,  4, 14, 6, 5}};

    // int cmd = stoi(argv[1]);
    // switch (cmd) {
    //     case 1:
         //   task3_dp_bottomup_optimized(A, c);
            // break;
        // case 2:
             task3_dp_bottomup(A, c);
        //     break;
        // case 3:
        //     task1_dp_topdown(A);
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