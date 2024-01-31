//
// Created by Vc on 1/28/24.
//

#include <iostream>

int main(int argc, char **argv)
{
    const double profit_ratio = 0.5;
    const double share_ratio = 0.1;
    const double eco_fee = 0.2;
    const double units = 1;
    double input = 10;
    double input_price = 13.728;
    double profit_price = 13.893;
    double tvl1 = input * input_price * units;
    double tvl_end = profit_price * input * units;
    double tvl_end_pro1 = (tvl_end - tvl1) * profit_ratio * (1- eco_fee); //生成奖池部分
    double tvl_end_pro2 = (tvl_end - tvl1) * profit_ratio; //归属于用户的盈利

    double count1 = tvl_end_pro1 / profit_price;
    double count2 = tvl_end_pro2 / profit_price;
    double end_with = input * input_price * units / profit_price + count2 + count1;


    std::cout << "tvl_end1 = " << tvl_end_pro1 << std::endl;
    std::cout << "tvl_end2 = " << tvl_end_pro2 << std::endl;

    std::cout << "count1 = " << count1 << " | count2 = " << count2 << std::endl;

    std::cout << "end_with = " << end_with << std::endl;
    return 0;
}
