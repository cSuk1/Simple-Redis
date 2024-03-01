//
// Created by 65224 on 2024/2/29.
//

#include "include/client.h"

namespace bustub {

    void Client::set(const std::string &key, std::string value) {
        aof->append("set " + key + " " + value + "\n");
        trie_store->Put<std::string>(key, std::move(value));
    }

    void Client::setRe(const std::string &key, std::string value) {
        trie_store->Put<std::string>(key, std::move(value));
    }

    void Client::get(const std::string &key, std::string &value) {
        auto opt = trie_store->Get<std::string>(key);
        if (opt.has_value()) {
            value = **opt;
        } else {
            value.clear();
        }
    }

    void Client::del(const std::string &key) {
        aof->append("rem " + key + "\n");
        trie_store->Remove(key);
    }

    void Client::delRe(const std::string &key) {
        trie_store->Remove(key);
    }


    void Client::recovery() {
        std::fstream &fs = aof->readBack();
        std::string op;
        std::string key;
        std::string value;
        while (fs >> op >> key) {
            std::transform(op.begin(), op.end(), op.begin(), ::toupper);
            if (op == "SET") {
                fs >> value;
                setRe(key, value);
            } else if (op == "REM") {
                delRe(key);
            } else if (op == "HSET") {
//            设置哈希字段
                std::string field_name;
                std::string field_value;
                fs >> field_name;
                fs >> field_value;
                setHashRe(key, field_name, field_value);
            } else if (op == "HREM") {
                std::string field_name;
                fs >> field_name;
                remHashRe(key, field_name);
            } else {
                std::cerr << "Unknown operation: " << op << std::endl;
            }
        }
        fs.close();
    }

    void Client::getHash(const std::string &key, const std::string &field_name, std::string &field_value) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
        if (wrapper_ht.has_value()) {
            auto ht = **wrapper_ht;
            field_value = ht[field_name];
        } else {
            field_value.clear();
        }
    }

    void Client::setHash(const std::string &key, const std::string &field_name, const std::string &field_value) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
        aof->append("hset " + key + " " + field_name + " " + field_value + "\n");
        if (wrapper_ht.has_value()) {
            auto ht = **wrapper_ht;
            ht[field_name] = field_value;
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        } else {
            std::unordered_map<std::string, std::string> ht;
            ht[field_name] = field_value;
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        }
    }

    void Client::remHash(const std::string &key, const std::string &field_name) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
        if (wrapper_ht.has_value()) {
            aof->append("hrem " + key + " " + field_name + "\n");
            auto ht = **wrapper_ht;
            ht.erase(field_name);
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        }
    }

    void Client::addHash(const std::string &key, const std::string &field_name, std::string &field_value) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
        if (wrapper_ht.has_value()) {
            auto ht = **wrapper_ht;
            ht[field_name] = field_value;
        }
    }

    void Client::setHashRe(const std::string &key, const std::string &field_name, const std::string &field_value) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
//        aof->append("hset " + key + " " + field_name + " " + field_value + "\n");
        if (wrapper_ht.has_value()) {
            auto ht = **wrapper_ht;
            ht[field_name] = field_value;
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        } else {
            std::unordered_map<std::string, std::string> ht;
            ht[field_name] = field_value;
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        }
    }

    void Client::remHashRe(const std::string &key, const std::string &field_name) {
        auto wrapper_ht = trie_store->Get<std::unordered_map<std::string, std::string>>(key);
        if (wrapper_ht.has_value()) {
//            aof->append("hrem " + key + " " + field_name + "\n");
            auto ht = **wrapper_ht;
            ht.erase(field_name);
            trie_store->Put<std::unordered_map<std::string, std::string>>(key, ht);
        }
    }

}