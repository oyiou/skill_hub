//
// Created by leever on 2023/3/14.
//
STATE_MACHINE() {
    State cur_State = type_A;
    while (cur_State != type_C) {
        Package _pack = getNewPackage();
        switch (cur_State) {
            case type_A:
                process_package_A(_pack);
                cur_State = type_B;
                break;
            case type_B:
                process_package_B(_pack);
                cur_State = type_C;
                break;
        }
    }
}