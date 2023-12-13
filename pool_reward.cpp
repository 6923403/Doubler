//
// Created by Vc on 12/9/23.
//

#include <iostream>

// Use inline function and register variable
double creator_re(double pro_ward, double reward_ratio)
{
    double creator_reward_ratio = 1 - reward_ratio;

    double final_reward = pro_ward * creator_reward_ratio;

    return final_reward;
}

double fee_zero(double reward, double input_btc)
{
    double all_btc = reward + input_btc;
    double final_withdraw = all_btc - all_btc * 0.002;
    return final_withdraw;
}

int main(int argc, char** argv)
{
    const double reward = 19000;
    double fee = 0.2;
    double profit_ratio = 0.2;
    double reward_ratio = 0.8;
    double creator_input_btc = 100;
    double winner_input_btc = 100;

    const double m_reward = reward - reward * fee;

    double pro_reward = m_reward * profit_ratio;

    double creator_reward = creator_re(pro_reward, reward_ratio);

    double winner_reward = pro_reward * reward_ratio;

    std::cout << "creator_reward = " << creator_reward << std::endl;

    std::cout << "winner_reward = " << winner_reward << std::endl;

    std::cout << "千2 creator_reward = " << fee_zero(creator_reward, creator_input_btc) << std::endl;
    std::cout << "千2 winner_reward = " << fee_zero(winner_reward, winner_input_btc) << std::endl;
    return 0;
}