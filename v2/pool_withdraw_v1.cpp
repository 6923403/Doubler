//
// Created by Vc on 1/28/24.
//

#include <iostream>

int main(int argc, char **argv)
{
    const double profit_ratio = 0.5;
    const double share_ratio = 0.1;
    const double eco_fee = 0.2;
    double input = 10;
    double input_price = 13.728;
    double profit_price = 13.893;
    double tvl1 = input * input_price;
    double tvldown = profit_price * input;
    double tvldown_pro1 = (tvldown - tvl1) * profit_ratio * (1- eco_fee); //0.66 //奖池部分
    double tvldown_pro2 = (tvldown - tvl1) * profit_ratio; //0.825

    double count1 = tvldown_pro1 / profit_price;
    double count2 = tvldown_pro2 / profit_price;
    double end_with = input * input_price / profit_price + count2 + count1;


    std::cout << "tvldown1 = " << tvldown_pro1 << std::endl;
    std::cout << "tvldown2 = " << tvldown_pro2 << std::endl;

    std::cout << "count1 = " << count1 << " | count2 = " << count2 << std::endl;

    std::cout << "end_with = " << end_with << std::endl;
    return 0;
}
