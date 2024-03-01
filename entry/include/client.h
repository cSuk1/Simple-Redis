//
// Created by 65224 on 2024/2/29.
//

#ifndef KVENGINE_CLIENT_H
#define KVENGINE_CLIENT_H

#include "../../trie/include/trie_store.h"
#include "../../persistence/include/aof.h"
#include "../../type/include/hash_type.h"

namespace bustub {

    class Client {
    public:
        Client() {
            trie_store = bustub::TrieStore::getInstance();
            aof = bustub::AOF::getInstance();
//            创建一个后台线程进行恢复
            recovery_thread = std::thread(&Client::recovery, this);
        }

        ~Client() {
//            等待持久化线程结束
            recovery_thread.join();
//            std::cout << "Client destructed" << std::endl;
//              写回
            aof->writeBack();
        }

        /**
         * set k-v
         * @param key
         * @param value
         */
        void set(const std::string &key, std::string value);

        /**
         * 重建时set k-v
         * @param key
         * @param value
         */
        void setRe(const std::string &key, std::string value);

        /**
         * get v
         * @param key
         * @param value
         */
        void get(const std::string &key, std::string &value);

        /**
         * 删除k-v
         * @param key
         */
        void del(const std::string &key);

        /**
         * 重建时删除k-v
         * @param key
         */
        void delRe(const std::string &key);

        /**
         * 添加哈希
         * @param key
         * @param field_name
         * @param field_value
         */
        void setHash(const std::string &key, const std::string &field_name, const std::string &field_value);

        /**
         * 移除哈希字段
         * @param key
         * @param field_name
         */
        void remHash(const std::string &key, const std::string &field_name);

        /**
         *  重建时添加哈希
         * @param key
         * @param field_name
         * @param field_value
         */
        void setHashRe(const std::string &key, const std::string &field_name, const std::string &field_value);

        /**
         *  重建时移除哈希字段
         * @param key
         * @param field_name
         */
        void remHashRe(const std::string &key, const std::string &field_name);

        void addHash(const std::string &key, const std::string &field_name, std::string &field_value);

        /**
         *  获取哈希
         * @param key
         * @param field_name
         * @param value
         */
        void getHash(const std::string &key, const std::string &field_name, std::string &value);

        /**
         * 持久化恢复
         */
        void recovery();

    private:
        std::shared_ptr<bustub::TrieStore> trie_store;
        std::shared_ptr<AOF> aof;
        std::thread recovery_thread;
    };
}


#endif //KVENGINE_CLIENT_H
