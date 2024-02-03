//
// Created by Vc on 1/28/24.
//

#include <iostream>
#include <list>
#include <vector>

double to_coins(double profit_price, double tvl, double units)
{
    return tvl / profit_price;
}

double end_coins(double user_tvl, double profit_price)
{
    return user_tvl / profit_price;
}

int main(int argc, char **argv)
{
    //TMD 算的不对啊

    /*
     * 如果你是池子主
     * 收益的70%减去ecofee 然后减去分享的奖池，剩余归你，你自己筹码盈利的30%归你
     *
     * 如果你是winner
     * 收益70%减去ecofee 加分享的奖池处以分享的unit 自己盈利30%归属自己
     *
     * 如果你在中间层
     * 70%拿去做奖池 到手30%收益
     */
    const double profit_ratio = 0.7;
    const double reward_share_ratio = 0.1;
    const double eco_fee = 0.2;
    const double units = 1;
    double user_input = 10;
    double user_input_price = 13.728;
    double pool_profit_price = 13.893;
    double pool_input = 30;
    double pool_avg_price = 13.621;
    std::vector<double> pool_layer_input = {10, 20}; //层筹码
    std::vector<double> pool_price = {13.728, 13.567}; //层价
    std::list<std::pair<double, double>> layer_tvl;

    double pool_tvl = 0;
    //POOL_TVL = Layer_n_price * input * units
    for (int i = 0; i < pool_layer_input.size(); i++) {
        pool_tvl += pool_layer_input[i] * pool_price[i] * units;
    }

    int flag = 1;
    double user_tvl = user_input * user_input_price * units; //用户投入tvl
    double user_avg_tvl = user_input * pool_avg_price * units; //用户投入tvl
    std::cout << "user_tvl: " << user_avg_tvl << " | pool_tvl: " << pool_tvl <<std::endl;

    double pool_end_tvl = pool_input * pool_profit_price * units; //池子盈利后tvl
    double user_profit_tvl = user_input * pool_profit_price * units - user_avg_tvl; //用户盈利部分
    double pool_profit_tvl = (pool_end_tvl - pool_tvl) * profit_ratio; //奖池+creator部分
//    std::cout << "user_profit_tvl: " << user_profit_tvl << " | pool_profit_tvl: " << pool_profit_tvl << std::endl;
    pool_profit_tvl = pool_profit_tvl * (1 - eco_fee); //影响奖池+creator 扣除ecofee
//    std::cout << "pool_profit_tvl: " << pool_profit_tvl << std::endl;

    double winner_reward_tvl = pool_profit_tvl * reward_share_ratio; //大赢家分配--奖池
    double creator_reward_tvl = pool_profit_tvl * (1 - reward_share_ratio); //池子主分配
    std::cout << "winner_reward_tvl: " << winner_reward_tvl << " | creator_reward_tvl: " << creator_reward_tvl << std::endl;

    double final_user_profit_tvl = user_profit_tvl * (1 - profit_ratio); //用户自身筹码盈利，也是中间层所得
    std::cout << "final_user_profit_tvl: " << final_user_profit_tvl << std::endl;

    double profit_coins = 0;
    double with_end_coins = 0;
    switch (flag)
    {
        case 1: //creator
        {
            double cr_owner_tvl = final_user_profit_tvl + creator_reward_tvl;
            profit_coins = end_coins(cr_owner_tvl, pool_profit_price);
            std::cout << "profit_coins = " << profit_coins << std::endl;
            with_end_coins = end_coins(user_tvl, pool_profit_price) + profit_coins;
            std::cout << with_end_coins << std::endl;
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}
