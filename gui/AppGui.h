#pragma once
#include "../bll/AccountService.h"
#include "../bll/EmployeeService.h"
#include <raylib.h>
#include <string>
#include <vector>

enum ScreenState{
    SCREEN_LOGIN,
    SCREEN_MANAGER
};
enum ModalState{
    MODAL_NONE,
    MODAL_ADD,
    MODAL_EDIT,
    MODAL_DELETE_CONFIRM
};
class AppGui{
private:
    AccountService accountService;
    EmployeeService employeeService;
    ScreenState currentScreen;
    ModalState currentModal;

    std::string loginId;
    std::string loginPass;
    std::string loginMessage;
    int activeInput;

    char inputName[50];
    char inputDob[20];
    char inputGender[10];
    char inputPhone[20];
    char inputAddress[50];
    char inputPhgId[10];
    std::string selectedEmployeeId;
    std::string actionMessage;

    char searchKeyword[50];
    std::string filterPhg;

    Font thaiFont;

    void DrawLoginScreen();
    void DrawManagerScreen();
    void DrawModal();
    void HandleTextInput(std::string &text, int maxLength);
    void HandleCharInput(char *buffer, int maxLength);

public:
    AppGui();
    ~AppGui();
    void Run(); 
};