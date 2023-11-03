//
// Created by oyiou on 2023/10/31.
//

enum num {
    tinyint, smallint, mediumint, int, bigint, float, double, decimal
};
enum time {
    date, time, year, datetime, timestamp
};
enum string {
    char, varchar, tinyblob, tinytest, blob, text, mediumblob, mediumtext, longblob, longtext
};

#define create_database     "create database runoob_database;"
#define drop_database       "drop database runoob_database;"
#define use_database        "use runoob_database;"
#define create_table        "create table if not exists runoob_table('id' int unsigned auto_increment, 'name' varchar(100) not null, 'date' date, primary key ('id'))engine=InnoDB default charset=utf8;"
#define drop_table          "drop table runoob_table"
#define insert  "insert into runoob_table (id, name, date) values (1, runoob, 2023-10-31);"
#define select  "select id,name,date from runoob_table [where id >= 1 [and/or name = runoob]] [limit 1] [offset 0];"
#define update  "update runoob_table set name = 'runoob', date = 2023-11-1 [where id = 1];"
#define delete  "delete runoob_table [where id = 1];"
#define like  "select * from runoob_table where name like 'noob';"
#define union  "select * from runoob_table  union select * from runoob_table2 order by country;"
#define order_by  "select * from runoob_table where name like 'noob' order by id asc/desc;"
#define group_by  "select * from runoob_table group by name;"
#define join  "select * from runoob_table a inner join select * from runoob_table2 b on a.name = b.name;"