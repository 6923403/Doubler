//
// Created by Vc on 1/18/24.
//

#ifndef DOUBLER_CONFIG_H
#define DOUBLER_CONFIG_H

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

#include "yaml-cpp/yaml.h"

namespace OPT{
struct Pool_con{
    int pool_id;
    double units;
    double fall_ratio;
    double profit_lock;
    double profit_share_ratio;
    double reward_share_ratio;
    double max_reward_units;
    double spot_price;
    double pool_dbr;
    int layers;
    bool pool_status;
    std::vector<double> pool_layer_price;
    std::vector<double> pool_layer_input;
};

struct User_con{
    int user_input_layer;
    double input_quantity;
    double input_price;
    int leverge;
    double gas_usdt;
};
}
OPT::Pool_con pools;
OPT::User_con users;

void config_pool()
{

    try{
        YAML::Node config = YAML::LoadFile("../pool.yaml");
        pools.units = config["POOL"]["unit_size"].as<double>();
        pools.pool_id = config["POOL"]["pool_id"].as<int>();
        pools.pool_status = config["POOL"]["status"].as<bool>();
        pools.fall_ratio = config["POOL"]["fall_ratio"].as<double>();
        pools.profit_lock = config["POOL"]["profit_lock"].as<double>();
        pools.profit_share_ratio = config["POOL"]["profit_share_ratio"].as<double>();
        pools.reward_share_ratio = config["POOL"]["reward_share_ratio"].as<double>();
        pools.max_reward_units = config["POOL"]["max_reward_units"].as<double>();
        pools.spot_price = config["POOL"]["spot_price"].as<double>();
        pools.pool_dbr = config["POOL"]["pool_dbr"].as<double>();
        pools.layers = config["LAYER"]["layers"].as<int>();

        users.user_input_layer = config["USER"]["user_input_layer"].as<int>();
        users.input_quantity = config["USER"]["input_quantity"].as<double>();
        users.input_price = config["USER"]["input_price"].as<double>();
        users.leverge = config["USER"]["leverge"].as<double>();
        users.gas_usdt = config["USER"]["gas_usdt"].as<double>();
        YAML::Node layer_p = config["LAYER"]["layer_price"];

        for (int i = 0; i < layer_p.size(); ++i) {
            // 假设数组内部是string
            double value = layer_p[i].as<double>();
            pools.pool_layer_price.push_back(layer_p[i].as<double>());
//            std::cout << value << "\n";
        }

        YAML::Node layer_in = config["LAYER"]["layer_input"];

        for (int i = 0; i < layer_in.size(); ++i) {
            // 假设数组内部是string
            double value = layer_in[i].as<double>();
            pools.pool_layer_input.push_back(layer_in[i].as<double>());
        }

//        for(auto &s : pools.pool_layer_input)
//        {
//            std::cout << "s = " << s << std::endl;
//        }

        std::cout << "SUCCESS, return pool config" << std::endl;

    }
    catch (...)
    {
        std::cout << "YAML ERROR" << std::endl;
        sleep(1000);
    }
}
#endif //DOUBLER_CONFIG_H
