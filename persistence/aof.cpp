//
// Created by 65224 on 2024/2/29.
//

#include "include/aof.h"

namespace bustub {

    /**
     * 写回
     */
    void AOF::writeBack() {
        if (!fs.is_open()) {
            fs.open(fileName, std::ios::out | std::ios::app);
        }
        while (!data.empty()) {
            fs << data.front();
            data.pop();
        }
        fs.flush();
        fs.close();
    }

    /**
     * 追加
     * @param cmd
     */
    void AOF::append(const std::string &cmd) {
        data.push(cmd);
    }

    /**
     * 读回
     * @return
     */
    std::fstream &AOF::readBack() {
        if (!fsi.is_open()) {
            fsi.open(fileName, std::ios::in | std::ios::app);
        }
        return fsi;
    }
}