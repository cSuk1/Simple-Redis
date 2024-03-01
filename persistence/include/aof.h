//
// Created by 65224 on 2024/2/29.
//

#ifndef KVENGINE_AOF_H
#define KVENGINE_AOF_H

#include <iostream>
#include <fstream>
#include <queue>

#include "../../trie/include/trie.h"

namespace bustub {
    class AOF {
    private:
        std::string fileName;
        std::fstream fs;
        std::fstream fsi;
        std::queue<std::string> data;

        AOF() : fileName("AOF") {
            fs.open(fileName, std::ios::out | std::ios::app);
            fsi.open(fileName, std::ios::in | std::ios::app);
        }

        AOF(const AOF &);

    public:
        /**
         * 单例模式
         * @return
         */
        static std::shared_ptr<AOF> getInstance() {
            static std::shared_ptr<AOF> instance(new AOF());
            return instance;
        }

        void writeBack();

        std::fstream &readBack();

        void append(const std::string &);
    };
}


#endif //KVENGINE_AOF_H
