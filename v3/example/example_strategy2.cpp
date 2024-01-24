// 奖池类
class POOL {
private:
    int total; // 奖池总金额
    vector<User*> users; // 参与的用户
public:
    POOL(int t) : total(t) {} // 构造函数，初始化奖池金额
    void addUser(User* u) { // 添加用户
        users.push_back(u);
    }
    // 分发奖励的函数
    void distribute() {
        // 遍历每个用户，执行策略
        for (auto user : users) {
            user->executeStrategy(this);
        }
        // 输出每个用户的奖励
        for (auto user : users) {
            cout << user->getName() << " 投入了 " << user->getCoins() << " 个硬币，获得了 " << user->getReward() << " 个奖励" << endl;
        }
    }
};

// 用户类
class User {
private:
    string name; // 用户名
    int coins; // 投入的硬币
    int reward; // 获得的奖励
    function<void(User*, POOL*)> strategy; // 策略函数
public:
    User(string n, int c, function<void(User*, POOL*)> s) : name(n), coins(c), strategy(s) {} // 构造函数，初始化用户名，硬币和策略
    string getName() { // 获取用户名
        return name;
    }
    int getCoins() { // 获取硬币
        return coins;
    }
    int getReward() { // 获取奖励
        return reward;
    }
    void setReward(int r) { // 设置奖励
        reward = r;
    }
    void executeStrategy(POOL* p) { // 执行策略
        strategy(this, p);
    }
};

// 策略函数，按照比例分发奖励
auto proportionStrategy =  {
        int totalCoins = 0; // 总共投入的硬币
        for (auto user : p->users) {
            totalCoins += user->getCoins();
        }
        // 奖励 = 用户投入的硬币 / 总共投入的硬币 * 奖池金额
        int reward = u->getCoins() * 1.0 / totalCoins * p->total;
        u->setReward(reward); // 设置奖励
};

// 策略函数，按照排名分发奖励
auto rankingStrategy =  {
        // 对用户按照投入的硬币降序排序
        sort(p->users.begin(), p->users.end(),  {
                return a->getCoins() > b->getCoins();
        });
        // 找到用户的排名
        int rank = 0;
        for (int i = 0; i < p->users.size(); i++) {
            if (p->users[i] == u) {
                rank = i + 1;
                break;
            }
        }
        // 奖励 = 奖池金额 / 排名
        int reward = p->total / rank;
        u->setReward(reward); // 设置奖励
};

// 测试代码
int main() {
    // 创建一个奖池，奖池金额为 100
    POOL* pool = new POOL(100);
    // 创建三个用户，分别使用不同的策略函数
    User* user1 = new User("Alice", 5, proportionStrategy);
    User* user2 = new User("Bob", 10, rankingStrategy);
    User* user3 = new User("Charlie", 20, proportionStrategy);
    // 将用户添加到奖池
    pool->addUser(user1);
    pool->addUser(user2);
    pool->addUser(user3);
    // 分发奖励
    pool->distribute();
    // 释放内存
    delete pool;
    delete user1;
    delete user2;
    delete user3;
    return 0;
}
