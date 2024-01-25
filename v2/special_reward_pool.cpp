//
// Created by Vc on 1/22/24.
//

#include <iostream>
#include <vector>
#include <list>


namespace FEE{
    const double ECO_FEE = 0.2;
    const double WITHDRAW_FEE = 0.02;
    const double BORROW_FEE = 0.02;
}
int main(int argc, char** argv) {
    double profit_price = 0;
    double avg_price = 0;
    double pool_tvl = 0; //POOL_TVL

    //POOL
    const double units = 1;
    const double profit_share_ratio = 0.15;
    const double reward_share_ratio = 0.8;
    const double profit_lock = 0.04;
    const double spot_price = 0.0831;
    const double pool_layer = 4; //L0
    const bool pool_status = false; //true = on, flase = off

    //USER
    const double user_input_quantity = 5;
    const double user_input_price = 313.35;
    const double user_layer = 1;
    double pool_input_count = 0;

//    std::vector<double> pool_layer_input = {5, 10}; //层筹码
//    std::vector<double> pool_price = {318.17, 313.35, 310.21}; //层价
    std::vector<double> pool_layer_input = {0, 56}; //层筹码
    std::vector<double> pool_price = {0.0906, 0.0858, 0.0841}; //层价
    std::list<std::pair<double, double>> layer_tvl;


    const double last_layer_input = 1347;
    const double last_layer_price = 0.0836;
    const double last_layer_tvl = last_layer_price * last_layer_input * units;

    //POOL_TVL = Layer_n_price * input * units
    for (int i = 0; i < pool_layer_input.size(); i++) {
        pool_tvl += pool_layer_input[i] * pool_price[i] * units;
        layer_tvl.push_back(std::make_pair(i, pool_layer_input[i] * pool_price[i] * units)); //Layer_tvl
    }

    std::cout << "POOL_TVL: " <<  pool_tvl << std::endl;
    std::cout << "Last_layer_tvl: " << last_layer_tvl << std::endl;

    for (auto it = layer_tvl.begin(); it != layer_tvl.end(); ++it) //Show Layer_tvl
    {
        std::cout << "Layer: " << it->first << ", TVL: " << it->second << std::endl;
    }

    avg_price = (last_layer_tvl - pool_tvl) / last_layer_input / units;
    std::cout << "Avg_price: " << avg_price << std::endl;

    profit_price = avg_price + avg_price * profit_lock;
    std::cout << "Profit_price: " << profit_price << std::endl; //0.0831 实际0.0832


    return 0;
}