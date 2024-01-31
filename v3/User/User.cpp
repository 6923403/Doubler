//
// Created by Vc on 1/16/24.
//

#include "User.h"

#include "../Strategy/Strategy.h"

User::User(int user_input_layer, double user_input_quantity, double user_input_price, int leverge, double gas_u, Strategy* s) :
        m_user_input_layer(user_input_layer), m_user_input_quantity(user_input_quantity), m_user_input_price(user_input_price), m_gas_usdt(gas_u), m_leverge(leverge), strategy(s)

{
    ;
//    std::cout << "m_user_input_layer = " << m_user_input_layer << " \nm_user_input_quantity = " << m_user_input_quantity << " \nm_user_input_price = " << m_user_input_price << " \nm_leverge = " << m_leverge << std::endl;
}

void User::executeStrategy(Pool* p)
{
    if (strategy != nullptr){
        strategy->calculateReward(this, p);
    }
}

double User::geUptvl(const double units)
{
    //后面根据价格判断哪一层
    return m_user_input_price * m_user_input_quantity * (m_user_input_layer + 1) * units;
}
