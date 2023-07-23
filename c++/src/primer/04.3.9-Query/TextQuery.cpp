//
// Created by leever on 7/23/2022.
//

#include "TextQuery.h"

#include <utility>
#include <algorithm>

void runQueries(std::ifstream &infile) {
    // infile 是一个 ifstream，指向要处理的文件
    TextQuery tq(infile);   // 保存文件并建立查询 map
    while (true) {
        std::cout << "enter word to look for,or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }

}
std::ostream &operator<<(std::ostream &os, const Query &query) {
    // Query::rep 通过它的 Query_base 指针对 rep() 进行了虚调用
    return os << query.rep();
}
inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TextQuery

// 读取输入文件并建立单词到行号的映射
TextQuery::TextQuery(std::ifstream &is): file(new std::vector<std::string>) {
    std::string text;
    while (std::getline(is, text)) {    // 对文件中每一行
        file->push_back(text);  // 保存此行文本
        int n = file->size() - 1;   // 当前行号
        std::istringstream line(text);  // 将行文本分解为单词
        std::string word;
        while (line >> word) {  // 对行中每个单词
            auto &lines = wm[word]; // lines 是一个 shared_ptr
            if (!lines) // 在第一次遇到这个单词时，此指针为空
                lines.reset(new std::set<line_no>); // 分配一个新的 set
            lines->insert(n);   // 将此行号插入 set 中
        }
    }
}
QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}
std::ostream &print(std::ostream &os, const QueryResult &qr) {
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num: *qr.lines)
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QueryResult

QueryResult::QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f): sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Query_base

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Query

QueryResult Query::eval(const TextQuery &t) const {
    return q->eval(t);
}
std::string Query::rep() const {
    return q->rep();
}
inline Query::Query(const std::string &s): q(new WordQuery(s)) {

}
Query::Query(std::shared_ptr<Query_base> query): q(std::move(query)) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WordQuery

WordQuery::WordQuery(std::string s): query_word(std::move(s)) {

}
QueryResult WordQuery::eval(const TextQuery &t) const {
    return t.query(query_word);
}
std::string WordQuery::rep() const {
    return query_word;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NotQuery

NotQuery::NotQuery(Query q): query(std::move(q)) {

}
// 具体的类：NotQuery 将定义所有继承而来的纯虚函数
std::string NotQuery::rep() const {
    return "~(" + query.rep() + ")";
}
QueryResult NotQuery::eval(const TextQuery &text) const {
    // 通过 Query 运算对象对 eval 进行虚调用
    auto result = query.eval(text);
    // 开始时结果 set 为空
    auto ret_lines = std::make_shared<std::set<line_no>>();
    // 必须在运算对象出现的所有行中进行迭代
    auto beg = result.begin(), end = result.end();
    // 对于输入文件中的每一行，如果该行不在 result 当中，则将其添加到 ret_lines
    auto sz = result.get_file()->size();
    for(size_t n = 0; n != sz; ++n) {
        // 如果还没有处理完 result 的所有行，检查当前行是否存在
        if(beg == end || *beg != n)
            ret_lines->insert(n);   // 如果不在 result 当中，添加这一行
        else if(beg != end)
            ++beg;  // 否则继续获取 result 的下一行（如果有的话）
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BinaryQuery

BinaryQuery::BinaryQuery(Query l, Query r, std::string s): lhs(std::move(l)), rhs(std::move(r)), opSym(std::move(s)) {

};
// 抽象类：BinaryQuery 不定义 eval
std::string BinaryQuery::rep() const {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AndQuery

AndQuery::AndQuery(const Query &left, const Query &right): BinaryQuery(left, right, "&") {

}
QueryResult AndQuery::eval(const TextQuery &text) const {
    // 通过 Query 运算对象进行虚调用，以获得运算对象的查询结果 set
    auto left = lhs.eval(text), right = rhs.eval(text);
    // 保存 left 和 tight 交集的 set
    auto ret_lines = std::make_shared<std::set<line_no>>();
    // 将两个范围的交集写入一个目的迭代器中
    // 本次调用的目的迭代器向 ret 添加元素
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrQuery

OrQuery::OrQuery(const Query &left, const Query &right): BinaryQuery(left, right, "|") {

}
QueryResult OrQuery::eval(const TextQuery &text) const {
    // 通过 Query 成员 lhs 和 rhs 进行的虚调用
    // 通过 eval 返回每个运算对象的 QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    // 将左侧运算对象行号拷贝到结果 set 中
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    // 插入右侧运算对象所得的行号
    ret_lines->inset(right.begin(), right.end());
    // 返回一个新的 QueryResult，它表示 lhs 和 rhs 的并集
    return QueryResult(rep(), ret_lines, left.get_file());
}
