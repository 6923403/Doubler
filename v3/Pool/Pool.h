//
// Created by Vc on 1/16/24.
//

#ifndef DOUBLER_POOL_H
#define DOUBLER_POOL_H

#include <list>

#include "../User/User.h"

namespace FEE{
    const double ECO_FEE = 0.2;
    const double WITHDRAW_FEE = 0.02;
    const double BORROW_FEE = 0.02;
}

class User;

class Pool {
public:
    Pool(double units, double fall_ratio, double profit_lock, double profit_rtatio, double re_share_ratio, double max_reward,
         double  spot_price, double pool_dbr, double pool_layer, bool pool_status,
         const std::vector<double> &layer_input, const std::vector<double> layer_price);
    void ca_layer_dbr(); //计算每层dbr

    void addUser(User* user);
    void distribute();
    void ca_pool_esreward();
    double getDowntvl();
    double getEsreward();
    double getLastLayerInput();
    double getLatestLayerPrice();

public:
    const double m_units;
    const double m_pool_dbr;
    double m_profit_price = 0;
    double m_avg_price = 0;
    double m_pool_tvl = 0;
    double m_es_reward = 0;
    double m_pool_input_count = 0;
    const double m_re_share_ratio;
    const double m_max_reward;

private:
    const double m_fall_ratio;
    const double m_profit_lock;
    const double m_profit_rtatio;

    const double m_spot_price;
    const int m_pool_layer;
    const bool m_pool_status;

    double m_downtvl;
    double m_uptvl;

private:
    std::vector<double> pool_layer_input;
    std::vector<double> pool_layer_price;
    std::list<std::pair<double, double>> pool_layer_tvl;

    std::vector<User*> m_users;
    std::vector<double> layer_dbr;
};


#endif //DOUBLER_POOL_H
