//
// Created by Vc on 12/11/23.
//

#include <iostream>
#include <vector>
#include <map>

int main(int argc, char** argv)
{
    const double pool_dbr = 2060.53;
    const int layers = 3; //L3

    const double my_input = 1200;
    const double my_tvl = 1200 * 14.769;

    const double unit_size = 1;
    double user_dbr = 0;

    std::vector<double> pool_layer = {1266, 30410, 2732, 10331}; //层筹码
    std::vector<double> pool_price = {15.307, 15.1, 14.934, 14.805}; //层价
    std::map<double, double> pool_tvl;

    for (int i = 0; i < pool_layer.size(); i++) {
        pool_tvl.insert(std::make_pair(i, pool_price[i] * pool_layer[i]));
    }

    double downtvl = 0;
    for(int i = 0; i <pool_layer.size(); i++) {
        std::cout << pool_tvl[i] << std::endl;

        downtvl += pool_tvl[i] * (i + 1);
    }

    double uptvl = my_tvl * (layers + 1);
    std::cout << downtvl << std::endl;

    user_dbr = pool_dbr * uptvl / downtvl;
    std::cout << "user_dbr = " << user_dbr << std::endl;


    return 0;
}