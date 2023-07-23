
#include <iostream>
#ifndef PRIMER_SALES_ITEM_H
#define PRIMER_SALES_ITEM_H

class Sales_data{
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
public:
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) {};
    Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p * n) {};
    Sales_data(std::istream &);

    std::string isbn() const {return bookNo};
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

class Sales_item{
private:
    int ISBN;
    int sales_num;
    int sales_volume;
    int price;
public:
    Sales_item();
    ~Sales_item();
    friend std::ostream& operator<<(std::ostream&, Sales_item&);
    friend std::istream& operator>>(std::istream&, Sales_item&);
    friend Sales_item& operator+(Sales_item&, Sales_item&);
    int isbn() const;
};

#endif //PRIMER_SALES_ITEM_H