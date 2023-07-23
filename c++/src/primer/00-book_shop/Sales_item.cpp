
#include "Sales_item.h"
int add(Sales_item &item1,Sales_item &item2) {
    std::cout << "input item1,item2:" << std::endl;
    std::cin >> item1 >> item2;
    if (item1.isbn() == item2.isbn()) {
        std::cout << item1 + item2 << std::endl;
        return 0;
    } else {
        std::cerr << "Data must refer to same ISBN" << std::endl;
        return -1;
    }
}
int total() {
    Sales_item total;
    std::cout << "input items:" << std::endl;
    if (std::cin >> total) {
        Sales_item trans;
        while (std::cin >> trans) {
            if (total.isbn() == trans.isbn())
                total + trans;
            else {
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "No data!" << std::endl;
        return -1;
    }
    return 0;
}

Sales_item::Sales_item() {
    ISBN = 0;
    sales_num = 0;
    sales_volume = 0;
    price = 0;
}

Sales_item::~Sales_item() = default;

std::ostream &operator<<(std::ostream & output, Sales_item & salesItem) {
    output <<
           "ISBN" << salesItem.ISBN <<
           "sales_num:" << salesItem.sales_num <<
           "sales_volume:" << salesItem.sales_volume <<
           "price:" << salesItem.price;
    return output;
}

std::istream &operator>>(std::istream & input, Sales_item & salesItem) {
    std::cout << "input ISBN,sales_num,price,:";
    input >>
          salesItem.ISBN >>
          salesItem.sales_num >>
          salesItem.price;
    salesItem.sales_volume = salesItem.sales_num * salesItem.price;
    return input;
}

Sales_item &operator+(Sales_item & left, Sales_item & right) {
//    Sales_item salesItem;
//    salesItem.ISBN = left.ISBN;
    left.sales_num = left.sales_num + right.sales_num;
    left.price = (left.price + right.price) / 2;
    left.sales_volume = left.sales_num * left.price;
    return left;
}

int Sales_item::isbn() const {
    return this->ISBN;
}

void input(Sales_data &data1, Sales_data &data2) {
    double price = 0;
    std::cin  >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;
}
void output_add(Sales_data &data1, Sales_data &data2) {
    if(data1.bookNo == data2.bookNo) {
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt << " " << totalRevenue << " ";
        if(totalCnt != 0)
            std::cout << totalRevenue/totalCnt << std::endl;
        else
            std::cout << "(no  sales)" << std::endl;
    } else {
        std::cerr << "Data must refer to the same ISBN" << std::endl;
    }
}
int main() {
    Sales_item item1, item2;
    add(item1,item2);

    Sales_data data1, data2;
    input(data1, data2);
    output_add(data1, data2);

    total();
}