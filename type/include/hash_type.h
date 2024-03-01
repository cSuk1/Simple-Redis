//
// Created by 65224 on 2024/3/1.
//

#ifndef KVENGINE_HASH_TYPE_H
#define KVENGINE_HASH_TYPE_H

#include <utility>

#include "../../trie/include/trie_store.h"

namespace bustub {

    class HashType {
    public:
        void addField(const std::string &field_name, std::string field_value);

        void removeField(const std::string &field_name);

        std::string getField(const std::string &field_name) const;

        std::string getAllFields();

    private:
        std::unordered_map<std::string, std::string> table;
    };

}


#endif //KVENGINE_HASH_TYPE_H
