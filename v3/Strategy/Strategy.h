//
// Created by Vc on 1/24/24.
//

#ifndef OMNISCIENT_STRATEGY_H
#define OMNISCIENT_STRATEGY_H

class User;
class Pool;

// 策略接口
class Strategy {
private:
public:
    virtual ~Strategy() {} 
    virtual void calculateReward(User* u, Pool* p) = 0; //计算DBR
};

// DBR奖励分配
class Strategy_DBR : public Strategy {
public:
    void calculateReward(User* u, Pool* p) override;

private:
    double m_user_dbr;
};

//赢家奖池分配
class Strategy_RewardPool_Dis : public Strategy {
public:
    void calculateReward(User* u, Pool* p) override;

};



#endif //OMNISCIENT_STRATEGY_H
