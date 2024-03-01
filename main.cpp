#include <iostream>
#include "entry/include/client.h"


int main(int argc, char *argv[]) {
    std::shared_ptr<bustub::Client> client =
            std::make_shared<bustub::Client>();
    client->recovery();
    std::string op;
    std::string key;
    std::string value;

//    处理命令
    while (std::cin >> op) {
        std::transform(op.begin(), op.end(), op.begin(), ::toupper);
        if (op == "EXIT") {
            break;
        }
        std::cin >> key;
        if (op == "SET") {
//            设置字符串
            std::cin >> value;
            client->set(key, value);
        } else if (op == "GET") {
//            获取字符串
            std::string res;
            client->get(key, res);
            if (res.empty()) {
                std::cout << "(null)" << std::endl;
            } else {
                std::cout << '"' << res << '"' << std::endl;
            }
        } else if (op == "REM") {
//            移除键
            client->del(key);
        } else if (op == "HSET") {
//            设置哈希字段
            std::string field_name;
            std::string field_value;
            std::cin >> field_name;
            std::cin >> field_value;
            client->setHash(key, field_name, field_value);
        } else if (op == "HGET") {
//            获取哈希字段
            std::string field_name;
            std::string field_value;
            std::cin >> field_name;
            client->getHash(key, field_name, field_value);
            if (field_value.empty()) {
                std::cout << "(null)" << std::endl;
            } else {
                std::cout << '"' << field_value << '"' << std::endl;
            }
        } else if (op == "HREM") {
            std::string field_name;
            std::cin >> field_name;
            client->remHash(key, field_name);
        } else {
            std::cerr << "Unknown operation: " << op << std::endl;
        }

        op.clear();
        key.clear();
        value.clear();
    }
    return 0;
}
