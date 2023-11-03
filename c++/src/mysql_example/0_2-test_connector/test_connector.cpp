//
// Created by leever on 2023/8/1.
//
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

#include <mysql_connector/mysqlx/xdevapi.h>

using namespace mysqlx;

int main() {
    // 修改控制台编码
    std::system("chcp 65001");

    try {
        // 改成你的信息
        Session sess(SessionOption::USER, "oyiou",
                     SessionOption::PWD, "oyiou",
                     SessionOption::HOST, "localhost",
                     SessionOption::PORT, 33066,
                     SessionOption::DB, "mysql");

        auto result = sess.sql("select * from user").execute();

        for (auto row : result.fetchAll()) {
            std::cout << row[0] << " " << row[1] << " " << row[2] << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
