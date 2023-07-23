//
// Created by leever on 2023/3/13.
//
#include "high_performance_server.h"

static bool switch_to_user(uid_t user_id, gid_t gp_id) {
    // 先确保目标用户不是 root
    if ((user_id == 0) && (gp_id == 0)) {
        return false;
    }
    // 确保当前用户是合法用户：root 或者目标用户
    gid_t gid = getgid();
    uid_t uid = getuid();
    if (((gid != 0) || (uid != 0)) && ((gid != gp_id) || (uid != user_id))) {
        return false;
    }
    // 如果不是 root，则已经是目标用户
    if (uid != 0) {
        return true;
    }
    // 切换到目标用户
    if ((setgid(gp_id) < 0) || (setuid(user_id) < 0)) {
        return false;
    }
    return true;
}