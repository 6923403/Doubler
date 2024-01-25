//
// Created by Vc on 1/24/24.
//

#include "Strategy.h"

#include "../Pool/Pool.h"

void Strategy_DBR::calculateReward(User* u, Pool* p)
{
    double down_tvl = p->getDowntvl();
    std::cout << "down_tvl: " << down_tvl << std::endl;
    double up_tvl = u->geUptvl(p->m_units);
    m_user_dbr = p->m_pool_dbr * up_tvl / down_tvl;
    std::cout << "user_dbr = " << m_user_dbr << std::endl;
}