//
// Created by Vc on 12/11/23.
//

#include <iostream>
#include <vector>
#include <map>

int main(int argc, char** argv)
{
    const double pool_dbr = 100;
    const double units = 0.2;
    double user_dbr = 0;
    const double user_input = 640;
    const double user_input_price = 268;
    const double user_layer = 2;

    std::vector<double> pool_layer_input = {160, 320, 640}; //层筹码
    std::vector<double> pool_price = {271.42, 269.35, 268, 55.5521, 54.2955, 54.0241, 53.754}; //层价
    std::unordered_map<double, double> pool_tvl;

    for (int i = 0; i < pool_layer_input.size(); i++) {
        pool_tvl.insert(std::make_pair(i, pool_price[i] * units * pool_layer_input[i]));
    }

    double downtvl = 0;
    for(int i = 0; i < pool_layer_input.size(); i++) {
//        std::cout << pool_tvl[i] << std::endl;

        downtvl += pool_tvl[i] * (i + 1);
    }
    for(int i = 0; i < pool_layer_input.size(); i++) {
        double uptvl = pool_tvl[i] * (i + 1);

        user_dbr = pool_dbr * uptvl / downtvl;
        std::cout << "layer_dbr = " << user_dbr << std::endl;
    }

    user_dbr = pool_dbr * (user_input * units * user_input_price) * (user_layer + 1) / downtvl;
    std::cout << "user_dbr = " << user_dbr << std::endl;

    return 0;
}