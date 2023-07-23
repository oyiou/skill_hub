//
// Created by leever on 7/23/2022.
//

#ifndef PRIMER_TEXTQUERY_H
#define PRIMER_TEXTQUERY_H
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>

void runQueries(std::ifstream &);

class Query;
std::ostream &operator<<(std::ostream&, const Query&);
Query operator&(const Query&, const Query&);
Query operator|(const Query&, const Query&);
Query operator~(const Query&);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TextQuery

class QueryResult;  // 为了定义函数 query 的返回类型，这个定义是必须的
class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file; // 输入文件
    // 每个单词到它所在的行号的集合的映射
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QueryResult

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
protected:
    using line_no = TextQuery::line_no;    // 用于 eval 函数
public:
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f);
private:
    std::string sought; // 查询单词
    std::shared_ptr<std::set<line_no>> lines;   // 出现行号
    std::shared_ptr<std::vector<std::string>> file; // 输入文件
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Query_base

// 这是一个抽象基类，具体的查询类型从中派生，所有成员都是 private 的
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // 用于 eval 函数
    virtual ~Query_base() = default;
private:
    // eval 返回与当前 Query 匹配的 QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep 是表示查询的一个 string
    virtual std::string rep() const = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Query

class WordQuery;
// 这是一个管理 Query_base 继承体系的接口类
class Query {
    // 这些运算符需要接受 shared_ptr 的构造函数，而该函数是私有的
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator~(const Query &);
public:
    Query(const std::string&);   // 构建一个新的 WordQuery
    // 接口函数：调用对应的 Query_base 操作
    QueryResult eval(const TextQuery &t) const;
    std::string rep() const;
//    std::ostream &operator<<(std::ostream &os, const Query &query);
private:
    Query(std::shared_ptr<Query_base> query);
    std::shared_ptr<Query_base> q;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WordQuery

class WordQuery: public Query_base {
    friend class Query; // Query 使用 WordQuery 构造函数
    WordQuery(std::string s);
    // 具体的类：WordQuery 将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const override;
    std::string rep() const override;
    std::string query_word; // 要查找的单词
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NotQuery

class NotQuery: public Query_base {
    friend Query operator~(const Query&);
    NotQuery(Query q);
    // 具体的类：NotQuery 将定义所有继承而来的纯虚函数
    std::string rep() const override;
    QueryResult eval(const TextQuery&) const override;
    Query query;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BinaryQuery

class BinaryQuery: public Query_base {
protected:
    BinaryQuery(Query l, Query r, std::string s);
    // 抽象类：BinaryQuery 不定义 eval
    std::string rep() const override;
    Query lhs, rhs; // 左侧和右侧运算对象
    std::string opSym;  // 运算符的名字
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AndQuery

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right);
    // 具体的类：AndQuery 继承了 rep 并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&) const override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrQuery

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right);
    // 具体的类：AndQuery 继承了 rep 并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&) const override;
};


#endif //PRIMER_TEXTQUERY_H
