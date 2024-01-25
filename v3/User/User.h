//
// Created by Vc on 1/16/24.
//

#ifndef DOUBLER_USER_H
#define DOUBLER_USER_H

#include <iostream>

class Pool;
class Strategy;

class User{
public:
    User(int user_input_layer, double user_input_quantity, double user_input_price, int leverge, Strategy* s);

    void executeStrategy(Pool* p); // 执行策略
    double geUptvl(const double units);

private:
    int m_user_input_layer;
    double m_user_input_quantity;
    double m_user_input_price;
    int m_leverge;

private:
    Strategy* strategy;

};

#endif //DOUBLER_USER_H
