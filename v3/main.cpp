#include "Config/config.h"
#include "Pool/Pool.h"
#include "Strategy/Strategy.h"

#include <memory>
#include <utility>

using namespace OPT;

int main(int argc, char** argv)
{
    //策略模式 奖励分配计算
    config_pool();
    Pool pool(pools.units, pools.fall_ratio, pools.profit_lock, pools.profit_share_ratio,pools.reward_share_ratio,
                 pools.max_reward_units, pools.spot_price, pools.pool_dbr, pools.layers, pools.pool_status,
                 pools.pool_layer_input, pools.pool_layer_price);
    pool.ca_layer_dbr(); //层分配DBR
    pool.ca_pool_esreward(); //计算奖池

//    std::shared_ptr<Strategy> ST_dbr = std::make_shared<Strategy_pool_dbr>();
    Strategy* ST_dbr = new Strategy_DBR();

    User* user1 = new User(users.user_input_layer, users.input_quantity, users.input_price, users.leverge, ST_dbr);
//    User* user2 = new User(users.user_input_layer, users.input_quantity, users.input_price, users.leverge, ST_dbr);
    pool.addUser(user1);


    pool.distribute();

    delete user1;
    delete ST_dbr;

    return 0;
}




