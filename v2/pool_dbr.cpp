//
// Created by Vc on 12/11/23.
//

#include <iostream>
#include <vector>
#include <map>

int main(int argc, char** argv)
{
    const double pool_dbr = 100;
    const double units = 1;
    double user_dbr = 0;
    const double user_input = 5;
    const double user_input_price = 318.17;
    const double user_layer = 0;

    std::vector<double> pool_layer_input = {5, 10, 20}; //层筹码
    std::vector<double> pool_price = {318.17, 313.35, 309.04}; //层价
    std::unordered_map<double, double> pool_tvl;

    for (int i = 0; i < pool_layer_input.size(); i++) {
        pool_tvl.insert(std::make_pair(i, pool_price[i] * units * pool_layer_input[i]));
    }

    double downtvl = 0;
    for(int i = 0; i < pool_layer_input.size(); i++) {

        downtvl += pool_tvl[i] * (i + 1);
    }
    for(int i = 0; i < pool_layer_input.size(); i++) {
        double uptvl = pool_tvl[i] * (i + 1);

        user_dbr = pool_dbr * uptvl / downtvl;
        std::cout << "layer" << i << "_dbr = "  << user_dbr << std::endl;
    }

    user_dbr = pool_dbr * (user_input * units * user_input_price) * (user_layer + 1) / downtvl;
    std::cout << "user_dbr = " << user_dbr << std::endl;

    return 0;
}

//layer0_dbr = 6.02589
//layer1_dbr = 23.7384
//layer2_dbr = 70.2357
