//
// Created by leever on 9/2/2022.
//

#include "getuid_getgid.h"

int main() {
#ifdef _WIN32

    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) {
        printf("[!]OpenProcessToken error\n");
        return 0;
    }
    DWORD Size, UserSize, DomainSize;
    SID *sid;
    SID_NAME_USE SidType;
    TCHAR UserName[64], DomainName[64];
    TOKEN_USER *User;
    Size = 0;
    GetTokenInformation(hToken, TokenUser, nullptr, 0, &Size);
    if (!Size)
        return 0;

    User = (TOKEN_USER *)malloc(Size);
    assert(User);
    GetTokenInformation(hToken, TokenUser, User, Size, &Size);
    assert(Size);
    Size = GetLengthSid(User->User.Sid);
    assert(Size);
    sid = (SID *)malloc(Size);
    assert(sid);

    CopySid(Size, sid, User->User.Sid);
    UserSize = (sizeof UserName / sizeof *UserName) - 1;
    DomainSize = (sizeof DomainName / sizeof *DomainName) - 1;
    LookupAccountSid(nullptr, sid, UserName, &UserSize, DomainName, &DomainSize, &SidType);

    LPWSTR StringSid = nullptr;
    int ret = ConvertSidToStringSid(User->User.Sid, reinterpret_cast<LPSTR *>(&StringSid));
    printf("StringSid is: %S\n", StringSid);
    printf("Who am I: %s\\%s\n", DomainName, UserName);
    free(sid);
    free(User);

    char username[UNLEN + 1] = {0};
    DWORD username_len = UNLEN + 1;
    if (!::GetUserNameA(username, &username_len)) {
        // error handling
    }
    printf("username = %s, username_len = %lu\n", username, username_len);
    exit(0);
#else
    printf("uid = %d, gid = %d\n", getuid(), getgid());
    exit(0);
#endif
}