//
// Created by Vc on 1/16/24.
//

#include "Pool.h"

#include <vector>
#include <iostream>

Pool::Pool(double units, double fall_ratio, double profit_lock, double profit_rtatio, double re_share_ratio, double max_reward,
            double  spot_price, double pool_dbr, double pool_layer, bool pool_status,
           const std::vector<double> &layer_input, const std::vector<double> layer_price) :
     m_units(units), m_fall_ratio(fall_ratio), m_profit_lock(profit_lock), m_profit_rtatio(profit_rtatio), m_re_share_ratio(re_share_ratio), m_max_reward(max_reward),
     m_spot_price(spot_price), m_pool_dbr(pool_dbr), m_pool_layer(pool_layer), m_pool_status(pool_status), pool_layer_input(layer_input), pool_layer_price(layer_price)
{
//    std::cout << " m_units = " << m_units << "\n m_fall_ratio = " << m_fall_ratio << "\n m_profit_lock = " << m_profit_lock << "\n m_profit_rtatio = " << m_profit_rtatio <<
//    "\n m_re_share_ratio = " << m_re_share_ratio << "\n m_max_reward = " << m_max_reward << "\n m_spot_price = " << m_spot_price << "\n m_pool_dbr = " << m_pool_dbr << "\n m_pool_layer = " << m_pool_layer << "\n m_pool_status = " << m_pool_status << std::endl;

    for (int i = 0; i < pool_layer_input.size(); i++) {
        m_pool_input_count += pool_layer_input[i];
        m_pool_tvl += pool_layer_input[i] * pool_layer_price[i] * units;
        pool_layer_tvl.push_back(std::make_pair(i, pool_layer_input[i] * pool_layer_price[i] * m_units)); //Layer_tvl
    }


    for (auto it = pool_layer_tvl.begin(); it != pool_layer_tvl.end(); ++it) //Show Layer_tvl
    {
        std::cout << "Layer: " << it->first << ", TVL: " << it->second << std::endl;
    }
    std::cout << "ALL_POOL_TVL: " <<  m_pool_tvl << std::endl;

//    std::cout << "m_pool_input_count: " << m_pool_input_count << std::endl;
    //平均价
    for (auto it = pool_layer_tvl.begin(); it != pool_layer_tvl.end(); ++it) //Show Layer_tvl
    {
        m_avg_price = m_pool_tvl / m_pool_input_count / m_units;
    }
    std::cout << "Avg_price: " << m_avg_price << std::endl;

    //止盈价
    m_profit_price = m_avg_price + m_avg_price * m_profit_lock;
    std::cout << "Profit_price: " << m_profit_price << std::endl;

}

void Pool::ca_layer_dbr() //downtvl/uptvl/dbr
{
    for (auto it = pool_layer_tvl.begin(); it != pool_layer_tvl.end(); ++it) {
        m_downtvl += it->second * (it->first + 1);
    }

    double t_layer_dbr = 0;
    for (auto it = pool_layer_tvl.begin(); it != pool_layer_tvl.end(); ++it){
        m_uptvl = it->second * (it->first + 1);
        t_layer_dbr = m_pool_dbr * m_uptvl / m_downtvl;
        std::cout << "Layer: " << it->first << "，DBR = "  << t_layer_dbr << std::endl;
        layer_dbr.push_back(t_layer_dbr);
    }
}

//根据池子筹码，参数计算奖池奖金
void Pool::ca_pool_esreward()
{
    double es_r1 = m_profit_price - m_avg_price;
    double es_r2 = es_r1 * (1 - FEE::ECO_FEE);
    m_es_reward = es_r2 / m_profit_price * m_pool_input_count * m_profit_rtatio * m_units;
    std::cout << "Estimated Rewards: " << m_es_reward << std::endl;
}

void Pool::addUser(User* user){
    m_users.push_back(user);
}

void Pool::distribute() {
    // 遍历每个用户，执行策略
    for (auto user : m_users) {
        user->executeStrategy(this);
    }
}

double Pool::getDowntvl()
{
    return m_downtvl;
}

double Pool::getEsreward()
{
    return m_es_reward;
}

double Pool::getLastLayerInput()
{
//    pool_layer_input
    return pool_layer_input.back();
}

double Pool::getLatestLayerPrice()
{
//    pool_layer_price
    return pool_layer_price.back();
}