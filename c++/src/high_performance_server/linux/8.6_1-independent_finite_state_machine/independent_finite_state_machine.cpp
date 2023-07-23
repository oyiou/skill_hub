//
// Created by leever on 2023/3/14.
//
STATE_MACHINE(Package _pack) {
    PackageType _type = _pack.GetType();
    switch (_type) {
        case type_A:
            process_package_A(_pack);
            break;
        case type_B:
            process_package_B(_pack);
            break;
    }
}