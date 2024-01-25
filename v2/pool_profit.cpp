//
// Created by Vc on 12/11/23.
//

#include <iostream>
#include <vector>
#include <list>

namespace FEE{
    const double ECO_FEE = 0.2;
    const double WITHDRAW_FEE = 0.02;
    const double BORROW_FEE = 0.02;
}

double withdraw_quantity(bool status, double input_count, double input_price, double profit_price, double avg_price, double units)
{
    /*
     * status
     * true is ON
     * false is OFF
     */
    double on1 = 0;
    double on2 = 0;
    double off1 = 0;
    double off2 = 0;

    if(status == true)
    {
        //ON
        if(input_price >= avg_price)
        {
            on1 = input_price * input_count * units;
            on1 = on1 * (1 - FEE::WITHDRAW_FEE);
            return on1;
        }
        else if(input_price < avg_price)
        {
            on2 = input_price * input_count * units / avg_price;
            on2 -= on2 * (1 - FEE::WITHDRAW_FEE);
            return on2;
        }
        else{
        }
    }
    else
    {
        //OFF
        if(input_price >= profit_price)
        {
            off1 = input_price * input_count * units;
            off1 = off1 * (1 - FEE::WITHDRAW_FEE);
            return off1;

        }
        else if(input_price < profit_price)
        {
            off2 = input_price * input_count * units / profit_price;
            off2 = off2 * (1 - FEE::WITHDRAW_FEE);
            return off2;
        }
        else
        {

        }
    }

    return 0;

}

int main(int argc, char** argv) {
    double profit_price = 0;
    double avg_price = 0;
    double pool_tvl = 0; //POOL_TVL

    //POOL
    const double units = 150;
    const double profit_share_ratio = 0.15;
    const double reward_share_ratio = 0.8;
    const double profit_lock = 0.01;
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
    std::vector<double> pool_layer_input = {1, 8}; //层筹码
    std::vector<double> pool_price = {2243.75, 2213.46, 0.0841, 0.0836}; //层价
    std::list<std::pair<double, double>> layer_tvl;

    //POOL_TVL = Layer_n_price * input * units
    for (int i = 0; i < pool_layer_input.size(); i++) {
        pool_tvl += pool_layer_input[i] * pool_price[i] * units;
        layer_tvl.push_back(std::make_pair(i, pool_layer_input[i] * pool_price[i] * units)); //Layer_tvl
    }

    std::cout << "POOL_TVL: " <<  pool_tvl << std::endl;

    for (auto it = layer_tvl.begin(); it != layer_tvl.end(); ++it) //Show Layer_tvl
    {
        std::cout << "Layer: " << it->first << ", TVL: " << it->second << std::endl;
    }

    //Avg_price = Pool_TVL / P_Count
    for(auto &s : pool_layer_input)
    {
        pool_input_count += s;
        avg_price = pool_tvl / pool_input_count / units;
    }
    std::cout << "Avg_price: " << avg_price << std::endl;

    profit_price = avg_price + avg_price * profit_lock;
    std::cout << "Profit_price: " << profit_price << std::endl;

    //pool_estimated_reward
    double es_r1 = profit_price - avg_price;
    double es_r2 = es_r1 * (1 - FEE::ECO_FEE);
    double es_rewards = es_r2 / spot_price * pool_input_count * profit_share_ratio * reward_share_ratio * units;
    std::cout << "Estimated Rewards: " << es_rewards << std::endl;

    //end_pool user withdrar quantity
    double es_r3 = es_r2 / spot_price * pool_input_count * profit_share_ratio * (1 -reward_share_ratio);
    double end_withdraw_eth = user_input_price * user_input_quantity / profit_price + es_r3;
//    std::cout << "end_withdraw_eth: " << end_withdraw_eth << std::endl;
//
//    double input_with = withdraw_quantity(pool_status, user_input_quantity, user_input_price, profit_price, avg_price, units);
//    std::cout << "input_with: " << input_with << std::endl;

    return 0;
}

/*
38060.4
92059.3
45995.7
*/