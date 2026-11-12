#include "AppGui.h"
#include <cstring>
#include <iostream>

// Bảng màu chuẩn xanh mint
const Color MINT_BG = { 240, 251, 247, 255 };       
const Color MINT_PRIMARY = { 26, 188, 156, 255 };   
const Color MINT_HOVER = { 22, 160, 133, 255 };     
const Color MINT_BORDER = { 163, 228, 215, 255 };   
const Color TEXT_DARK = { 44, 62, 80, 255 };        
const Color DARKRED = { 139, 0, 0, 255 };           

AppGui::AppGui(){
    this->currentScreen = SCREEN_LOGIN;
    this->currentModal = MODAL_NONE;
    this->activeInput = 0;
    this->loginId = "";
    this->loginPass = "";
    this->loginMessage = "";
    this->actionMessage = "";
    this->filterPhg = "";

    memset(inputName, 0, sizeof(inputName));
    memset(inputDob, 0, sizeof(inputDob));
    memset(inputGender, 0, sizeof(inputGender));
    memset(inputPhone, 0, sizeof(inputPhone));
    memset(inputAddress, 0, sizeof(inputAddress));
    memset(inputPhgId, 0, sizeof(inputPhgId));
    memset(searchKeyword, 0, sizeof(searchKeyword));
}

AppGui::~AppGui() {
    UnloadFont(thaiFont);
}

void AppGui::HandleTextInput(std::string &text, int maxLength){
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (text.length() < maxLength)){
            text += (char)key;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && text.length() > 0) {
        text.pop_back();
    }
}

void AppGui::HandleCharInput(char *buffer, int maxLength) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125)) {
            int len = strlen(buffer);
            if (len < maxLength - 1) {
                buffer[len] = (char)key;
                buffer[len + 1] = '\0';
            }
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(buffer);
        if (len > 0) {
            buffer[len - 1] = '\0';
        }
    }
}

void AppGui::DrawLoginScreen(){
    ClearBackground(MINT_BG);
    DrawTextEx(thaiFont, "ĐANG NHAP HE THONG QUAN LY", (Vector2){240, 90}, 24, 1, MINT_HOVER);

    Vector2 mouse = GetMousePosition();
    Rectangle boxId = {320, 160, 260, 40};
    Rectangle boxPass = {320, 220, 260, 40};
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, boxId)) activeInput = 0;
        else if (CheckCollisionPointRec(mouse, boxPass)) activeInput = 1;
    }

    if (activeInput == 0) HandleTextInput(loginId, 20);
    else if (activeInput == 1) HandleTextInput(loginPass, 20);

    DrawTextEx(thaiFont, "Ma dang nhap:", (Vector2){180, 170}, 18, 1, TEXT_DARK);
    DrawRectangleRec(boxId, WHITE);
    DrawRectangleLinesEx(boxId, 2, (activeInput == 0) ? MINT_PRIMARY : MINT_BORDER);
    DrawTextEx(thaiFont, loginId.c_str(), (Vector2){330, 170}, 18, 1, TEXT_DARK);

    DrawTextEx(thaiFont, "Mat khau:", (Vector2){180, 230}, 18, 1, TEXT_DARK);
    DrawRectangleRec(boxPass, WHITE);
    DrawRectangleLinesEx(boxPass, 2, (activeInput == 1) ? MINT_PRIMARY : MINT_BORDER);
    std::string hiddenPass(loginPass.length(), '*');
    DrawTextEx(thaiFont, hiddenPass.c_str(), (Vector2){330, 230}, 18, 1, TEXT_DARK);

    Rectangle btnLogin = {320, 290, 260, 45};
    bool isBtnHover = CheckCollisionPointRec(mouse, btnLogin);
    
    DrawRectangleRounded(btnLogin, 0.3f, 4, isBtnHover ? MINT_HOVER : MINT_PRIMARY);
    DrawTextEx(thaiFont, "DANG NHAP", (Vector2){395, 302}, 18, 1, WHITE);

    if (isBtnHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Account acc;
        if (accountService.login(loginId, loginPass, acc, loginMessage)) {
            if (acc.getRole() == "manager") {
                currentScreen = SCREEN_MANAGER; 
                loginMessage = "";
            } else {
                loginMessage = "Chi Quan ly moi đuoc truy cap he thong";
            }
        }
    }
    
    if (!loginMessage.empty()) {
        DrawTextEx(thaiFont, loginMessage.c_str(), (Vector2){320, 350}, 16, 1, RED);
    }
    DrawTextEx(thaiFont, "Goi y tai khoan: Admin / quanly123", (Vector2){320, 390}, 14, 1, GRAY);
}
void AppGui::DrawManagerScreen() {
    ClearBackground(MINT_BG);
    DrawRectangle(0, 0, 1024, 60, MINT_PRIMARY);
    DrawTextEx(thaiFont, "HE THONG QUAN LY NHAN VIEN", (Vector2){20.0f, 18.0f}, 20, 1, WHITE);

    Vector2 mouse = GetMousePosition();
    Rectangle btnLogout = { 890.0f, 14.0f, 110.0f, 32.0f };
    bool hovLogout = CheckCollisionPointRec(mouse, btnLogout);
    DrawRectangleRounded(btnLogout, 0.3f, 4, hovLogout ? (Color){200, 50, 50, 255} : (Color){220, 80, 80, 255});
    DrawTextEx(thaiFont, "Dang xuat", (Vector2){btnLogout.x + 18.0f, btnLogout.y + 8.0f}, 14, 1, WHITE);

    if (currentModal == MODAL_NONE && hovLogout && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentScreen = SCREEN_LOGIN;
        loginId = "";
        loginPass = "";
        loginMessage = "Đa dang xuat khoi he thong";
        currentModal = MODAL_NONE;
        return;
    }

    // Nút Thêm mới
    Rectangle btnAdd = {20.0f, 80.0f, 110.0f, 36.0f};
    bool hoverAdd = CheckCollisionPointRec(mouse, btnAdd);
    DrawRectangleRounded(btnAdd, 0.3f, 4, hoverAdd ? MINT_HOVER : MINT_PRIMARY);
    DrawTextEx(thaiFont, "+ Them moi", (Vector2){32.0f, 89.0f}, 15, 1, WHITE);

    if (currentModal == MODAL_NONE && hoverAdd && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentModal = MODAL_ADD;
        activeInput = 0; // Đặt trỏ chuột mặc định vào ô đầu tiên (Họ và tên)
        memset(inputName, 0, sizeof(inputName));
        memset(inputDob, 0, sizeof(inputDob));
        memset(inputGender, 0, sizeof(inputGender));
        memset(inputPhone, 0, sizeof(inputPhone));
        memset(inputAddress, 0, sizeof(inputAddress));
        memset(inputPhgId, 0, sizeof(inputPhgId));
        actionMessage = "";
    }

    // Ô tìm kiếm theo tên (CHỈ NHẬN PHÍM KHI KHÔNG CÓ MODAL)
    DrawRectangle(145, 80, 220, 36, WHITE);
    DrawRectangleLinesEx({145, 80, 220, 36}, 1, MINT_BORDER);
    
    if (currentModal == MODAL_NONE) {
        HandleCharInput(searchKeyword, 40);
    }

    if (strlen(searchKeyword) == 0) {
        DrawTextEx(thaiFont, "Tim kiem theo ten...", (Vector2){155.0f, 90.0f}, 14, 1, GRAY);
    } else {
        DrawTextEx(thaiFont, searchKeyword, (Vector2){155.0f, 90.0f}, 14, 1, TEXT_DARK);
    }

    // Lọc theo phòng ban (Chỉ hoạt động khi không mở modal)
    std::string depts[5] = {"", "101", "102", "103", "104"};
    for(int i=0; i<5; i++) {
        Rectangle btnDept = {380.f + i*75.0f, 80.0f, 65.0f, 36.0f};
        bool isSel = (filterPhg == depts[i]);
        bool hov = CheckCollisionPointRec(mouse, btnDept);
        DrawRectangleRounded(btnDept, 0.3f, 4, isSel ? MINT_PRIMARY : (hov ? MINT_BORDER : WHITE));
        DrawRectangleRoundedLines(btnDept, 0.3f, 4, MINT_PRIMARY);
        std::string lbl = (i==0) ? "Tat ca" : depts[i];
        DrawTextEx(thaiFont, lbl.c_str(), (Vector2){btnDept.x + 12.0f, btnDept.y + 10.0f}, 13, 1, isSel ? WHITE : TEXT_DARK);

        if (currentModal == MODAL_NONE && hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            filterPhg = depts[i];
        }
    }

    // Lấy danh sách nhân viên
    std::vector<Employee> list;
    if (strlen(searchKeyword) > 0) {
        list = employeeService.searchByName(searchKeyword);
    } else if (!filterPhg.empty()) {
        list = employeeService.filterByDepartment(filterPhg);
    } else {
        list = employeeService.getAllEmployees();
    }

    // Tiêu đề bảng dữ liệu
    DrawRectangle(20, 130, 984, 35, MINT_BORDER);
    DrawTextEx(thaiFont, "Ma NV", (Vector2){30.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "Ho và Ten", (Vector2){140.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "Gioi tinh", (Vector2){340.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "So đien thoai", (Vector2){440.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "Phong", (Vector2){580.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "Trang thai", (Vector2){670.0f, 138.0f}, 15, 1, TEXT_DARK);
    DrawTextEx(thaiFont, "Thao tac", (Vector2){850.0f, 138.0f}, 15, 1, TEXT_DARK);

    // Đổ dữ liệu lên bảng
    int yPos = 175;
    for (size_t i = 0; i < list.size(); i++) {
        if (i % 2 == 0) DrawRectangle(20, yPos - 5, 984, 32, WHITE);
        
        DrawTextEx(thaiFont, list[i].getNV_ID().c_str(), (Vector2){30.0f, (float)yPos}, 14, 1, TEXT_DARK);
        DrawTextEx(thaiFont, list[i].getFullName().c_str(), (Vector2){140.0f, (float)yPos}, 14, 1, TEXT_DARK);
        DrawTextEx(thaiFont, list[i].getGender().c_str(), (Vector2){340.0f, (float)yPos}, 14, 1, TEXT_DARK);
        DrawTextEx(thaiFont, list[i].getPhone().c_str(), (Vector2){440.0f, (float)yPos}, 14, 1, TEXT_DARK);
        DrawTextEx(thaiFont, list[i].getPHG_ID().c_str(), (Vector2){580.0f, (float)yPos}, 14, 1, TEXT_DARK);
        DrawTextEx(thaiFont, list[i].getStatus().c_str(), (Vector2){670.0f, (float)yPos}, 14, 1, TEXT_DARK);

        Rectangle btnDelRow = {840.0f, (float)(yPos - 2), 70.0f, 24.0f};
        bool hovDel = CheckCollisionPointRec(mouse, btnDelRow);
        DrawRectangleRounded(btnDelRow, 0.3f, 4, hovDel ? RED : LIGHTGRAY);
        DrawTextEx(thaiFont, "Xoa", (Vector2){btnDelRow.x + 22.0f, btnDelRow.y + 4.0f}, 12, 1, WHITE);

        if (currentModal == MODAL_NONE && hovDel && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selectedEmployeeId = list[i].getNV_ID();
            currentModal = MODAL_DELETE_CONFIRM;
            actionMessage = "";
        }

        yPos += 32;
        if (yPos > 560) break;
    }

    if (!actionMessage.empty() && currentModal == MODAL_NONE) {
        DrawRectangle(20, 575, 984, 30, WHITE);
        DrawTextEx(thaiFont, actionMessage.c_str(), (Vector2){30.0f, 582.0f}, 14, 1, MINT_HOVER);
    }

    // Gọi vẽ Modal nếu có
    if (currentModal != MODAL_NONE) {
        DrawModal();
    }
}

void AppGui::DrawModal() {
    // Vẽ lớp phủ mờ màn hình nền
    DrawRectangle(0, 0, 1024, 640, (Color){0, 0, 0, 120});

    Vector2 mouse = GetMousePosition();

    if (currentModal == MODAL_ADD) {
        Rectangle modalBox = {262, 100, 500, 480};
        DrawRectangleRounded(modalBox, 0.05f, 4, WHITE);
        DrawRectangleRoundedLines(modalBox, 0.05f, 4, MINT_PRIMARY);

        DrawTextEx(thaiFont, "THEM NHAN VIEN MOI", (Vector2){modalBox.x + 30.0f, modalBox.y + 20.0f}, 18, 1, MINT_PRIMARY);

        // Vùng các ô nhập liệu trong form
        Rectangle boxName = {modalBox.x + 140.0f, modalBox.y + 60.0f, 320.0f, 30.0f};
        Rectangle boxDob  = {modalBox.x + 210.0f, modalBox.y + 105.0f, 250.0f, 30.0f};
        Rectangle boxGender = {modalBox.x + 210.0f, modalBox.y + 150.0f, 250.0f, 30.0f};
        Rectangle boxPhone = {modalBox.x + 140.0f, modalBox.y + 195.0f, 320.0f, 30.0f};
        Rectangle boxAddress = {modalBox.x + 140.0f, modalBox.y + 240.0f, 320.0f, 30.0f};
        Rectangle boxPhgId = {modalBox.x + 210.0f, modalBox.y + 285.0f, 250.0f, 30.0f};

        // Click chuột để đổi ô nhập liệu (focus) trong modal
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, boxName)) activeInput = 0;
            else if (CheckCollisionPointRec(mouse, boxDob)) activeInput = 1;
            else if (CheckCollisionPointRec(mouse, boxGender)) activeInput = 2;
            else if (CheckCollisionPointRec(mouse, boxPhone)) activeInput = 3;
            else if (CheckCollisionPointRec(mouse, boxAddress)) activeInput = 4;
            else if (CheckCollisionPointRec(mouse, boxPhgId)) activeInput = 5;
        }

        // Nhận ký tự bàn phím vào ĐÚNG ô đang được chọn trong modal
        if (activeInput == 0) HandleCharInput(inputName, 45);
        else if (activeInput == 1) HandleCharInput(inputDob, 15);
        else if (activeInput == 2) HandleCharInput(inputGender, 10);
        else if (activeInput == 3) HandleCharInput(inputPhone, 15);
        else if (activeInput == 4) HandleCharInput(inputAddress, 30);
        else if (activeInput == 5) HandleCharInput(inputPhgId, 5);

        // Vẽ các nhãn và ô input
        DrawTextEx(thaiFont, "Ho và ten:", (Vector2){modalBox.x + 30.0f, modalBox.y + 65.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxName, WHITE);
        DrawRectangleLinesEx(boxName, 2, (activeInput == 0) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputName, (Vector2){boxName.x + 8.0f, boxName.y + 6.0f}, 14, 1, TEXT_DARK);

        DrawTextEx(thaiFont, "Ngay sinh:", (Vector2){modalBox.x + 30.0f, modalBox.y + 110.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxDob, WHITE);
        DrawRectangleLinesEx(boxDob, 2, (activeInput == 1) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputDob, (Vector2){boxDob.x + 8.0f, boxDob.y + 6.0f}, 14, 1, TEXT_DARK);

        DrawTextEx(thaiFont, "Gioi tinh:", (Vector2){modalBox.x + 30.0f, modalBox.y + 155.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxGender, WHITE);
        DrawRectangleLinesEx(boxGender, 2, (activeInput == 2) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputGender, (Vector2){boxGender.x + 8.0f, boxGender.y + 6.0f}, 14, 1, TEXT_DARK);

        DrawTextEx(thaiFont, "SĐT:", (Vector2){modalBox.x + 30.0f, modalBox.y + 200.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxPhone, WHITE);
        DrawRectangleLinesEx(boxPhone, 2, (activeInput == 3) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputPhone, (Vector2){boxPhone.x + 8.0f, boxPhone.y + 6.0f}, 14, 1, TEXT_DARK);

        DrawTextEx(thaiFont, "Que quan:", (Vector2){modalBox.x + 30.0f, modalBox.y + 245.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxAddress, WHITE);
        DrawRectangleLinesEx(boxAddress, 2, (activeInput == 4) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputAddress, (Vector2){boxAddress.x + 8.0f, boxAddress.y + 6.0f}, 14, 1, TEXT_DARK);

        DrawTextEx(thaiFont, "Ma Phong:", (Vector2){modalBox.x + 30.0f, modalBox.y + 290.0f}, 14, 1, TEXT_DARK);
        DrawRectangleRec(boxPhgId, WHITE);
        DrawRectangleLinesEx(boxPhgId, 2, (activeInput == 5) ? MINT_PRIMARY : MINT_BORDER);
        DrawTextEx(thaiFont, inputPhgId, (Vector2){boxPhgId.x + 8.0f, boxPhgId.y + 6.0f}, 14, 1, TEXT_DARK);

        if (!actionMessage.empty()) {
            DrawTextEx(thaiFont, actionMessage.c_str(), (Vector2){modalBox.x + 30.0f, modalBox.y + 335.0f}, 13, 1, RED);
        }

        // Nút Lưu và Hủy
        Rectangle btnSave = {modalBox.x + 260.0f, modalBox.y + 400.0f, 90.0f, 36.0f};
        Rectangle btnCancel = {modalBox.x + 370.0f, modalBox.y + 400.0f, 90.0f, 36.0f};

        bool hovSave = CheckCollisionPointRec(mouse, btnSave);
        bool hovCancel = CheckCollisionPointRec(mouse, btnCancel);

        DrawRectangleRounded(btnSave, 0.3f, 4, hovSave ? MINT_HOVER : MINT_PRIMARY);
        DrawTextEx(thaiFont, "Luu", (Vector2){btnSave.x + 32.0f, btnSave.y + 10.0f}, 14, 1, WHITE);

        DrawRectangleRounded(btnCancel, 0.3f, 4, hovCancel ? LIGHTGRAY : GRAY);
        DrawTextEx(thaiFont, "Huy", (Vector2){btnCancel.x + 32.0f, btnCancel.y + 10.0f}, 14, 1, WHITE);

        if (hovSave && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Employee newEmp("", inputName, inputDob, inputGender, inputPhone, inputAddress, inputPhgId, "", "Dang lam");
            std::string msg;
            if (employeeService.addEmployee(newEmp, msg)) {
                currentModal = MODAL_NONE;
                actionMessage = "Them nhan vien thanh cong";
            } else {
                actionMessage = msg;
            }
        }
        if (hovCancel && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentModal = MODAL_NONE;
        }
    } 
    else if (currentModal == MODAL_DELETE_CONFIRM) {
        Rectangle modalBox = {337.0f, 220.0f, 350.0f, 180.0f};
        DrawRectangleRounded(modalBox, 0.05f, 4, WHITE);
        DrawRectangleRoundedLines(modalBox, 0.05f, 4, RED);

        DrawTextEx(thaiFont, "XÁC NHẬN XÓA NHÂN VIÊN", (Vector2){modalBox.x + 40.0f, modalBox.y + 25.0f}, 16, 1, RED);
        std::string info = "Mã NV: " + selectedEmployeeId;
        DrawTextEx(thaiFont, info.c_str(), (Vector2){modalBox.x + 40.0f, modalBox.y + 65.0f}, 15, 1, TEXT_DARK);

        Rectangle btnYes = {modalBox.x + 50.0f, modalBox.y + 115.0f, 110.0f, 36.0f};
        Rectangle btnNo = {modalBox.x + 190.0f, modalBox.y + 115.0f, 110.0f, 36.0f};

        bool hovYes = CheckCollisionPointRec(mouse, btnYes);
        bool hovNo = CheckCollisionPointRec(mouse, btnNo);

        DrawRectangleRounded(btnYes, 0.3f, 4, hovYes ? RED : DARKRED);
        DrawTextEx(thaiFont, "Dong y xoa", (Vector2){btnYes.x + 18.0f, btnYes.y + 10.0f}, 14, 1, WHITE);

        DrawRectangleRounded(btnNo, 0.3f, 4, hovNo ? LIGHTGRAY : GRAY);
        DrawTextEx(thaiFont, "Quay lai", (Vector2){btnNo.x + 30.0f, btnNo.y + 10.0f}, 14, 1, WHITE);

        if (hovYes && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            std::string msg;
            if (employeeService.deleteEmployee(selectedEmployeeId, msg)) {
                actionMessage = "Da xoa nhan vien thanh cong";
            } else {
                actionMessage = msg;
            }
            currentModal = MODAL_NONE;
        }
        if (hovNo && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentModal = MODAL_NONE;
        }
    }
}
void AppGui::Run(){
    InitWindow(1024, 640, "Phan Mem Quan Ly Nhan Vien");
    SetTargetFPS(60);

    thaiFont = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, 0, 250);
    if (thaiFont.texture.id == 0) {
        thaiFont = GetFontDefault();
    }
    while (!WindowShouldClose()) { // Chỉ thoát hoàn toàn khi bấm dấu X của cửa sổ Windows
        BeginDrawing();
        switch(currentScreen) {
            case SCREEN_LOGIN:
                DrawLoginScreen();
                break;
            case SCREEN_MANAGER:
                DrawManagerScreen();
                break;
        }
        EndDrawing();
    }
    UnloadFont(thaiFont);
    CloseWindow();
}