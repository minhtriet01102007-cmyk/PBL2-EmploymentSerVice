#include "AccountService.h"

AccountService::AccountService(){
}
bool AccountService::login(const string& NV_ID, const string& pass, Account& loginAccount, string& message){
    // Tai khoan quan ly mac dinh
    if (NV_ID == "Admin" && pass == "quanly123"){
        loginAccount = Account("quanly123", "manager", "Admin", false);
        message = "Dang nhap quan ly thanh cong!";
        return true;
    }
    Account account;
    if (!accountRepository.findByID(NV_ID, account)){
        message = "Ma dang nhap khong ton tai!";
        return false;
    }
    if (account.getIsLocked()){
        message = "Tai khoan da bi khoa!";
        return false;
    }
    if (account.getPass() != pass){
        message = "Mat khau khong chinh xac!";
        return false;
    }
    loginAccount = account;
    message = "Dang nhap thanh cong!";
    return true;
}
bool AccountService::changePassword(string NV_ID, string oldPass, string newPass, string& message){
    Account account;
    if (!accountRepository.findByID(NV_ID, account)){
        message = "Khong tim thay tai khoan!";
        return false;
    }
    if (account.getIsLocked()){
        message = "Tai khoan dang bi khoa!";
        return false;
    }
    if (account.getPass() != oldPass){
        message = "Mat khau hien tai khong dung!";
        return false;
    }
    if (newPass.length() < 6){
        message = "Mat khau moi phai co it nhat 6 ky tu!";
        return false;
    }
    if (newPass == oldPass){
        message = "Mat khau moi phai khac mat khau cu!";
        return false;
    }
    account.setPass(newPass);
    if (!accountRepository.update(account)){
        message = "Doi mat khau that bai!";
        return false;
    }
    message = "Doi mat khau thanh cong!";
    return true;
}
bool AccountService::createAccount(string NV_ID, string role){
    Account account(NV_ID, role, NV_ID, false);
    return accountRepository.add(account);
}
bool AccountService::lockAccount(
    string NV_ID, string& message){
    if (NV_ID == "Admin"){
        message = "Khong the khoa tai khoan quan ly!";
        return false;
    }
    Account account;
    if (!accountRepository.findByID(NV_ID, account)){
        message = "Khong tim thay tai khoan!";
        return false;
    }
    if (account.getIsLocked()){
        message = "Tai khoan da bi khoa!";
        return false;
    }
    account.setIsLocked(true);
    if (!accountRepository.update(account)){
        message = "Khoa tai khoan that bai!";
        return false;
    }
    message = "Khoa tai khoan thanh cong!";
    return true;
}
bool AccountService::unlockAccount(string NV_ID, string& message){
    if (NV_ID == "Admin"){
        message = "Tai khoan quan ly mac dinh khong can mo khoa!";
        return false;
    }
    Account account;

    if (!accountRepository.findByID(NV_ID, account)){
        message = "Khong tim thay tai khoan!";
        return false;
    }
    if (!account.getIsLocked()){
        message = "Tai khoan dang hoat dong!";
        return false;
    }
    account.setIsLocked(false);
    if (!accountRepository.update(account)){
        message = "Mo khoa tai khoan that bai!";
        return false;
    }
    message = "Mo khoa tai khoan thanh cong!";
    return true;
}
vector<Account> AccountService::getAllAccounts(){
    return accountRepository.getAll();
}