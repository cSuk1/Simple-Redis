//
// Created by 65224 on 2024/3/1.
//

#include "include/hash_type.h"

namespace bustub {
    void HashType::addField(const std::string &field_name, std::string field_value) {
        table[field_name] = std::move(field_value);
    }

    void HashType::removeField(const std::string &field_name) {
        table.erase(field_name);
    }

    std::string HashType::getField(const std::string &field_name) const {
        return table.at(field_name);
    }

    std::string HashType::getAllFields() {
        std::string res;
        for (auto &[key, value]: table) {
            res += key;
            res += ": ";
            res += value;
        }
        return res;
    }
}
