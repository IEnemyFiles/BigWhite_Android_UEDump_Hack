#include "Android_draw/draw.h"
#include "main.h"
#if defined(USE_OPENGL)
#include "imgui_image.h"
#else
#include "VulkanUtils.h"
#endif

#include "picture_ZhenAiKun_png.h"


#include "My_Utils/http.h"
#include "My_Utils/Encrypt.h"


bool main_thread_flag = true;

int abs_ScreenX = 0;
int abs_ScreenY = 0;



/**
 * imgui测试
 */
#if defined(USE_OPENGL)
TextureInfo op_img;
#else
MyTextureData vk_img;
#endif

int main(int argc, char *argv[]) {
    std::cout << "免责声明：" << std::endl << std::endl;
    std::cout << "此软件是一款用于逆向分析和测试游戏功能的工具，旨在帮助开发者理解游戏的内部工作原理以及进行相关测试。然而，请注意以下几点：" << std::endl << std::endl;

    std::cout << "1. 本软件的使用仅限于合法的研究和测试目的。任何将此软件用于非法活动、侵犯版权或其他违法行为的用户将承担相应的法律责任。" << std::endl;
    std::cout << "2. 本软件可能会影响游戏的正常运行，甚至可能导致游戏崩溃、数据损坏或其他不可预测的问题。使用本软件可能会对游戏的稳定性和功能性产生不利影响。" << std::endl;
    std::cout << "3. 本软件可能会涉及游戏厂商的知识产权和利益，因此使用本软件可能会引起游戏厂商的不满甚至法律纠纷。" << std::endl;
    std::cout << "4. 用户对使用本软件所产生的一切后果和风险负全部责任。软件开发者及其关联方不承担任何直接或间接的责任，包括但不限于因软件使用造成的损失、损害、法律纠纷或其他不良后果。" << std::endl;
    std::cout << "5. 本软件的发布和使用可能受到不同国家和地区的法律法规的限制。用户应当遵守当地的法律法规，确保在合法范围内使用本软件。" << std::endl << std::endl;

    std::cout << "请在使用本软件前详细阅读并理解上述免责声明。一旦您开始使用本软件，即代表您同意遵守上述声明，并愿意承担因此产生的一切风险和责任。" << std::endl;
    std::cout << "对于任何因使用本软件所引起的问题，我们将不负有任何法律或经济责任。" << std::endl << std::endl;
    std::cout << "（https://t.me/BigWhiteChat）" << std::endl;
    execCommand("mkdir -p /storage/emulated/0/A_BigWhiteTool/SDK");
    //获取屏幕信息
    screen_config();
    ::abs_ScreenX = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::abs_ScreenY = (displayInfo.height < displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    // 初始化imgui
    if (!initGUI_draw(native_window_screen_x, native_window_screen_y, true)) {
        return -1;
    }
    py = displayInfo.height / 2;
    px = displayInfo.width / 2;

    printf("当前程序Pid : %d\n", getpid());
#if defined(USE_OPENGL)
    op_img = createTexture_ALL_FromMem(picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H));
#else
    LoadTextureFromMemory((const void *)&picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H), &vk_img);
#endif

    Touch_Init(displayInfo.width, displayInfo.height, displayInfo.orientation, true);

    processes = GetUE4Processes();//获取包含libue4.so的进程


    while (main_thread_flag) {
        // imgui画图开始前调用
        drawBegin(); //
        Layout_tick_UI();
        drawEnd();// imgui画图结束调用
        std::this_thread::sleep_for(1ms);
    }

    shutdown();
    Touch_Close();
    return 0;
}


void Layout_tick_UI() {
    static bool show_demo_window = false;
    static bool show_another_window = false;
    static bool show_finddata_window = false;
    static bool show_Dump_window = false;
    static bool show_pointerTool_window = false;
    static float f = 0.0f;
    static int counter = 0;
    static float color_number = 50.0f;
    ImGui::Begin(u8"BigWhiteHack");
    ImGui::SetWindowSize({1150, 700});

    ImGuiStyle& style = ImGui::GetStyle();

    style.FrameRounding = 10.0f;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

    ImGui::SetCursorPos({ 10.0f, 30.0f });
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR", ImVec2(230, 680), true, window_flags);
    if (ImGui::BeginTable("split", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
    {
        ImGui::TableNextColumn();

        float Btn_Pos_Y = 10.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 1 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("Home", ImVec2(200, 90))) {
            Var::ColorNumber = 1;
        }
        ImGui::PopStyleColor();

        Btn_Pos_Y += 110.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 2 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("Button", ImVec2(200, 90))) {
            Var::ColorNumber = 2;
        }
        ImGui::PopStyleColor();


        Btn_Pos_Y += 110.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 3 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("CheckBox", ImVec2(200, 90))) {
            Var::ColorNumber = 3;
        }
        ImGui::PopStyleColor();


        Btn_Pos_Y += 110.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 4 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("Slide", ImVec2(200, 90))) {
            Var::ColorNumber = 4;
        }
        ImGui::PopStyleColor();


        Btn_Pos_Y += 110.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 5 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("Plot", ImVec2(200, 90))) {
            Var::ColorNumber = 5;
        }
        ImGui::PopStyleColor();


        Btn_Pos_Y += 110.0f;
        ImGui::SetCursorPos({ 10.0f, Btn_Pos_Y });
        ImGui::PushStyleColor(ImGuiCol_Button, Var::ColorNumber == 6 ? ImVec4(1.0f, 0.5f, 0.3f, 1.0f) : ImVec4(0.35f, 0.00f, 1.00f, 0.50f));
        if (ImGui::Button("Execl", ImVec2(200, 90))) {
            Var::ColorNumber = 6;
        }
        ImGui::PopStyleColor();

        ImGui::EndTable();
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();


    ImGui::SetCursorPos({ 250.0f, 55.0f });
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("Content", ImVec2(830, 650), true, window_flags);
    if (ImGui::BeginTable("split_1", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
    {
        ImGui::TableNextColumn();

        if (Var::ColorNumber == 1) {
            if (ReadMode == 0 && ImGui::BeginMenu("驱动")) {
                if (ImGui::MenuItem("普通")){
                    ReadMode=1;
                }
                if (ImGui::MenuItem("QX10.6")){
                    ReadMode=2;
                }
                ImGui::EndMenu();
            }


            if (BigWhitePid==0 && ReadMode >0 && ImGui::BeginMenu("进程")) {
                for (const ProcessInfo& process : processes) {
                    std::string jc = "PID: " + process.pid + " | Name: " + process.name;
                    if (ImGui::MenuItem(jc.c_str())) {
                        BigWhitePid = std::stoi(process.pid);//这里给BigWhite_pid赋值 是为了BigWhiteRead里面需要用
                        if (ReadMode==2){
                            BigWhiteinit();
                        }
                        //Gname->75e17530d0   Offset->1c34a0d0
                        LibBase = GetLibBase(BigWhitePid);
                        printf("Pid：%d\nLibBase：%lx\n",BigWhitePid,LibBase);
                        //ProcessName=process.name;//将进程名保存为全局变量
                        //ResetOffsets();//重新选择进程时 重置偏移结构体变量
                        //addr.libbase = GetLibBase(BigWhite_pid);
                        //GameBase=addr.libbase;
                        //printf("Pid：%d\nlibBase：%lx\nGname：%lx\nGobject：%lx\n",BigWhite_pid,addr.libbase,addr.GNames,addr.Gobject);
                        cout << "Init Is OK！"<<endl;
                        //cshzt = true;
                    }
                }
                ImGui::EndMenu();
            }

            if (BigWhitePid>0&&ImGui::BeginMenu("窗口"))
            {
                ImGui::MenuItem("ImguiDemo", NULL, &show_demo_window);
                ImGui::Separator();
                ImGui::MenuItem("初始化数据", NULL, &show_finddata_window);
                ImGui::MenuItem("UE4Dumper", NULL, &show_Dump_window);
                ImGui::MenuItem("指针扫描", NULL, &show_pointerTool_window);

                /*
                ImGui::MenuItem("DebugDumper", NULL, &ShowDebugDumper);
                ImGui::MenuItem("矩阵数据", NULL, &ShowDebugMatrix);*/
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("退出"))
            {
                main_thread_flag = false;
                ImGui::EndMenu();
            }
        }
        else if (Var::ColorNumber == 2) {
            for (int i = 0; i < 7; i++)
            {
                if (i > 0)
                    ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
                ImGui::Button("Click");
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }

            ImGui::NewLine();

            ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
            ImGui::Button("Long Button 1", sz);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
                ImGui::SetTooltip("I am Long Button 1");

            ImGui::Button("Long Button 2", sz);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
                ImGui::SetTooltip("I am Long Button 2");

            ImGui::Button("Long Button 3", sz);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay))
                ImGui::SetTooltip("I am Long Button 3", ImGui::GetStyle().HoverDelayShort);

            ImGui::Button("Long Button 4", sz);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay))
                ImGui::SetTooltip("I am Long Button 4)", ImGui::GetStyle().HoverDelayNormal);

            ImGui::Button("Long Button 5", sz);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
                ImGui::SetTooltip("I am Long Button 5");


            ImGui::NewLine();
            for (int i = 0; i < 5; i++) {
                ImGui::Button("MainButton");
                ImGui::SameLine();
            }
            ImGui::NewLine();
            if (ImGui::Button("Button")) {
                Var::count += 1;
            }
            for (int i = 0; i < Var::count; i++) {
                ImGui::Button("New Button");
                // ImGui::SameLine();
            }

        }
        else if (Var::ColorNumber == 3) {
            static bool checkOne = false;
            static bool checkTwo = true;
            static bool checkThree = false;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i == 0) {
                        ImGui::Checkbox("CheckBox", &checkOne);
                    }
                    else if (i == 1) {
                        ImGui::Checkbox("CheckBox1", &checkTwo);
                    }
                    else {
                        ImGui::Checkbox("CheckBox2", &checkThree);
                    }
                    ImGui::SameLine();

                }
                ImGui::NewLine();
            }
            static bool checkMain = false;
            ImGui::Checkbox("MainCheckBox", &checkMain);
        }
        else if (Var::ColorNumber == 4) {
            const float spacing = 4;
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

            static int int_value = 0;
            ImGui::VSliderInt("##int", ImVec2(18, 160), &int_value, 0, 5);
            ImGui::SameLine();

            static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
            ImGui::PushID("set1");
            for (int i = 0; i < 7; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
                ImGui::VSliderFloat("##v", ImVec2(18, 160), &values[i], 0.0f, 1.0f, "");
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("%.3f", values[i]);
                ImGui::PopStyleColor(4);
                ImGui::PopID();
            }
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::PushID("set2");
            static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
            const int rows = 3;
            const ImVec2 small_slider_size(18, (float)(int)((160.0f - (rows - 1) * spacing) / rows));
            for (int nx = 0; nx < 4; nx++)
            {
                if (nx > 0) ImGui::SameLine();
                ImGui::BeginGroup();
                for (int ny = 0; ny < rows; ny++)
                {
                    ImGui::PushID(nx * rows + ny);
                    ImGui::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
                    if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                        ImGui::SetTooltip("%.3f", values2[nx]);
                    ImGui::PopID();
                }
                ImGui::EndGroup();
            }
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::PushID("set3");
            for (int i = 0; i < 4; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
                ImGui::VSliderFloat("##v", ImVec2(40, 160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
                ImGui::PopStyleVar();
                ImGui::PopID();
            }
            ImGui::PopID();
            ImGui::PopStyleVar();
        }
        else if (Var::ColorNumber == 5) {
            {
                static bool animate = true;
                ImGui::Checkbox("Animate", &animate);

                static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
                ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
                ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));

                static float values[90] = {};
                static int values_offset = 0;
                static double refresh_time = 0.0;
                if (!animate || refresh_time == 0.0)
                    refresh_time = ImGui::GetTime();
                while (refresh_time < ImGui::GetTime())
                {
                    static float phase = 0.0f;
                    values[values_offset] = cosf(phase);
                    values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
                    phase += 0.10f * values_offset;
                    refresh_time += 1.0f / 60.0f;
                }

                {
                    float average = 0.0f;
                    for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                        average += values[n];
                    average /= (float)IM_ARRAYSIZE(values);
                    char overlay[32];
                    sprintf(overlay, "avg %f", average);
                    ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
                }

                struct Funcs
                {
                    static float Sin(void*, int i) { return sinf(i * 0.1f); }
                    static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
                };
                static int func_type = 0, display_count = 70;
                ImGui::SeparatorText("Functions");
                ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
                ImGui::Combo("func", &func_type, "Sin\0Saw\0");
                ImGui::SameLine();
                ImGui::SliderInt("Sample count", &display_count, 1, 400);
                float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
                ImGui::PlotLines("Lines", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
                ImGui::PlotHistogram("Histogram", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
                ImGui::Separator();

                static float progress = 0.0f, progress_dir = 1.0f;
                if (animate)
                {
                    progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                    if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
                    if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
                }

                ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Text("Progress Bar");

                float progress_saturated = IM_CLAMP(progress, 0.0f, 1.0f);
                char buf[32];
                sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
                ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);
            }
        }
        else if (Var::ColorNumber == 6) {
            static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings;

            for (int n = 0; n < 3; n++)
            {
                char buf[32];
                sprintf(buf, "Synced Table %d", n);
                bool open = ImGui::CollapsingHeader(buf, ImGuiTreeNodeFlags_DefaultOpen);
                if (open && ImGui::BeginTable("Table", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5)))
                {
                    ImGui::TableSetupColumn("One");
                    ImGui::TableSetupColumn("Two");
                    ImGui::TableSetupColumn("Three");
                    ImGui::TableHeadersRow();
                    const int cell_count = (n == 1) ? 27 : 9;
                    for (int cell = 0; cell < cell_count; cell++)
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text("this cell %d", cell);
                    }
                    ImGui::EndTable();
                }
            }
        }


        ImGui::EndTable();
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::NewLine();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

    //ImGui::TextColored(ImVec4(0.5f, 0.0f, 1.0f, 1.0f), "Developer:Troice   QQ:2133351499.");
    ImGui::SameLine();
    ImGui::GetBackgroundDrawList()->AddLine({ 0, 0 }, { 123, 456 }, ImColor(0, 255, 0, 255), { 1.5 });

    g_window = ImGui::GetCurrentWindow();
    ImGui::End();

    if (show_another_window) { // 3. Show another simple window.
        ImGui::Begin("另一个窗口", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("另一个窗口的 爱坤!");
#if defined(USE_OPENGL)
        ImGui::Image((ImTextureID)op_img.textureId, ImVec2(170, 170));
#else
        ImGui::Image((ImTextureID)vk_img.DS, ImVec2(170, 170));
#endif
        if (ImGui::Button("关闭这个坤口")) {
            show_another_window = false;
        }

        ImGui::End();

    }

    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    if (show_finddata_window) {
        ShowFindDataWindow();
    }
    if (show_Dump_window) {
        ShowDumpWindow();
    }
    if (show_pointerTool_window) {
        ShowpointerToolWindow();
    }


}


void Layout_tick_UI2() {
    static bool show_demo_window = false;
    static bool show_another_window = false;
    static bool show_finddata_window = false;
    static bool show_Dump_window = false;
    static bool show_pointerTool_window = false;
    {
        static float f = 0.0f;
        static int counter = 0;
        static int style_idx = 1;
        static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
#if defined(USE_OPENGL)
        const static char* name = "(OpenGL)->搞批(Symbol chain)";
#else
        const static char *name = "(Vulkan)->搞批(Symbol chain)";
#endif
        if (ImGui::BeginMainMenuBar())
        {
            // 计算菜单宽度
            ImVec2 menuSize = ImVec2(100, 50); // 菜单的宽度和高度
            float menuBarWidth = ImGui::GetWindowWidth();
            float menuX = (menuBarWidth - menuSize.x) * 0.5f; // 计算居中位置
            ImGui::SetCursorPosX(menuX);

            if (ReadMode == 0 && ImGui::BeginMenu("驱动")) {
                if (ImGui::MenuItem("普通")){
                    ReadMode=1;
                }
                if (ImGui::MenuItem("QX10.6")){
                    ReadMode=2;
                }
                ImGui::EndMenu();
            }

            if (BigWhitePid==0 && ReadMode >0 && ImGui::BeginMenu("进程")) {
                for (const ProcessInfo& process : processes) {
                    std::string jc = "PID: " + process.pid + " | Name: " + process.name;
                    if (ImGui::MenuItem(jc.c_str())) {
                        BigWhitePid = std::stoi(process.pid);//这里给BigWhite_pid赋值 是为了BigWhiteRead里面需要用
                        if (ReadMode==2){
                            BigWhiteinit();
                        }
                        //Gname->75e17530d0   Offset->1c34a0d0
                        LibBase = GetLibBase(BigWhitePid);
                        printf("Pid：%d\nLibBase：%lx\n",BigWhitePid,LibBase);
                        //ProcessName=process.name;//将进程名保存为全局变量
                        //ResetOffsets();//重新选择进程时 重置偏移结构体变量
                        //addr.libbase = GetLibBase(BigWhite_pid);
                        //GameBase=addr.libbase;
                        //printf("Pid：%d\nlibBase：%lx\nGname：%lx\nGobject：%lx\n",BigWhite_pid,addr.libbase,addr.GNames,addr.Gobject);
                        cout << "Init Is OK！"<<endl;
                        //cshzt = true;
                    }
                }
                ImGui::EndMenu();
            }

            if (BigWhitePid>0&&ImGui::BeginMenu("窗口"))
            {
                ImGui::MenuItem("ImguiDemo", NULL, &show_demo_window);
                ImGui::Separator();
                ImGui::MenuItem("初始化数据", NULL, &show_finddata_window);
                ImGui::MenuItem("UE4Dumper", NULL, &show_Dump_window);
                ImGui::MenuItem("指针扫描", NULL, &show_pointerTool_window);

                /*
                ImGui::MenuItem("DebugDumper", NULL, &ShowDebugDumper);
                ImGui::MenuItem("矩阵数据", NULL, &ShowDebugMatrix);*/
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("退出"))
            {
                main_thread_flag = false;
                ImGui::EndMenu();
            }


        }
/*        ImGui::Begin(name, 0);  // Create a window called "Hello, world!" and append into it.
        ImGui::Text("这是一些有用的文本.");               // Display some text (you can use a format strings too)
        if (ImGui::Combo("##主题", &style_idx, "白色主题\0蓝色主题\0紫色主题\0")) {
            switch (style_idx) {
                case 0: ImGui::StyleColorsLight(); break;
                case 1: ImGui::StyleColorsDark(); break;
                case 2: ImGui::StyleColorsClassic(); break;
            }
        }
        ImGui::Checkbox("演示窗口", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::SameLine();
        ImGui::Checkbox("绘制射线", &show_draw_Line);
        ImGui::Checkbox("坤坤窗口", &show_another_window);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit4("取色器", (float *) &clear_color); // Edit 3 floats representing a color
        if (ImGui::Button("Button")) {
            counter++;
        }

        ImGui::SameLine();
        ImGui::Text("计数 = %d", counter);
        ImGui::Text("窗口集中 = %d", ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "应用平均 %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::Button("退出gui")) {
            main_thread_flag = false;
        }
        g_window = ImGui::GetCurrentWindow();
        ImGui::End();*/
    }


}
void InputInit(){
    uint64_t Address = 0;
    for (int i = 0; i < sizeof(inputText) / sizeof(inputText[0]); ++i) {
        if (!inputText[i].empty()){
            uint64_t inputValue;
            if (inputText[i].find("BASE")!= std::string::npos){
                inputValue = LibBase;
            }else {
                inputValue = std::stoull(inputText[i], nullptr, 16);// 第三个参数是进制，这里使用十六进制
            }
            if (i==0){
                Address += inputValue;
            }else{
                Address=GetAddr(Address+inputValue);
            }
        }
        //cout << i << endl;
    }
    DumperAddress = Address;
}
void InputClear(){
    // 使用循环将数组内容清空
    for (int i = 0; i < 10; ++i) {
        inputText[i] = "";
    }
}
void ShowDumpWindow(){
    ImGui::Begin("UE4Dump工具");
    // 渲染编辑框
    for (int i = 0; i < OffsetLevel; ++i) {
        ImGui::InputText((i == 0) ? "地址" : (std::to_string(i) + "层偏移").c_str(), inputText[i].data(), inputText[i].size() + 1); // 使用 size() + 1
        // 如果点击了编辑框，则显示虚拟键盘并获取焦点
        if (ImGui::IsItemClicked()) {
            activeEditBoxIndex = i; // 记录活动编辑框的索引
            showVirtualKeyboard = true;
            ImGui::SetKeyboardFocusHere(-1);
        }

        if (i==0){
            ImGui::SameLine();
            if (ImGui::Button("+")){
                OffsetLevel++;
                InputInit();
            }
            ImGui::SameLine();
            if (ImGui::Button("-")){
                if (OffsetLevel>1)   --OffsetLevel;
                inputText[OffsetLevel].clear();
                InputInit();
            }
        }
    }

    if (ImGui::Button("确定")){
        InputInit();
    }

    if (ImGui::Button("Uworld")){
        InputClear();
        OffsetLevel = 2;
        std::stringstream OffsetsUworldStr;
        OffsetsUworldStr << std::hex << OffsetsUworld;
        inputText[0] = "BASE";
        inputText[1] = OffsetsUworldStr.str();
        InputInit();
    }
    ImGui::SameLine();
    if (ImGui::Button("Matrix")){
        InputClear();
        OffsetLevel = 2;
        std::stringstream OffsetsMatrixStr;
        OffsetsMatrixStr << std::hex << OffsetsMatrix;
        inputText[0] = "BASE";
        inputText[1] = OffsetsMatrixStr.str();
        InputInit();
    }
    ImGui::InputText("过滤", DumpFilter.data(), DumpFilter.size());
    if (ImGui::IsItemClicked()) {
        showVirtualKeyboard = true;
        ImGui::SetKeyboardFocusHere(-1);
    }

    // 渲染虚拟键盘
    if (showVirtualKeyboard) {
        RenderVirtualKeyboard();
    }


    ImGui::SetNextWindowSize(ImVec2(1500, 1000), ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable("split", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        std::vector<StructureList> aaa = foreachAddress(DumperAddress);
        int i = 100000;
        for (const auto &data : aaa) {
            ImGui::PushID(i);
            ShowPlaceholderObject(data, i);
            ImGui::PopID();
            //ImGui::Separator();
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
    ImGui::End();

}
void ShowFindDataWindow(){
    ImGui::SetNextWindowSize(ImVec2(800, 800)); // 设置窗口的宽度和高度

    ImGui::Begin("初始化数据");
    static bool isShow = false;
    static char GnameBuffer[0x256];
    static char GObjectBuffer[0x256];
    static char UWorldBuffer[0x256];
    static char GEngineBuffer[0x256];
    static char DebugCanvasBuffer[0x256];
    static char MatrixBuffer[0x256];
    if (BigWhitePid>0){
        ImGui::Checkbox("是否UE423以上版本\n（谨慎选择 选择错会导致卡死！卡十几秒左右是正常的！）",&isUE423);
        ImGui::Text("获取到Gname和Gobject会出现DumpSDK按钮");
        if (ImGui::Button("获取Gname",ImVec2(400,75))){
            AddrOffsets Gname = GetGname();
            OffsetsGname=Gname.Offsets;//设置全局Gname偏移
            //addr.GNames = addr.libbase + Gname.Offsets;//设置全局Gname地址
            NamePoolData = (FNamePool*)(LibBase+OffsetsGname);
            AddrGNames = (LibBase+Gname.Offsets);
            sprintf(GnameBuffer,"Gname->%lx   Offset->%x",Gname.Addr,Gname.Offsets);
            cout << GnameBuffer <<"\n" <<endl;
            isShow= true;
        }
        if (OffsetsGname>0&&ImGui::Button("获取Gobject",ImVec2(400,75))){
            AddrOffsets Gobject = GetGobject();
            OffsetsGobject = Gobject.Offsets;
            ObjObjects = (TUObjectArray*)(LibBase+Gobject.Offsets+0x10);
            AddrGObject = (LibBase+Gobject.Offsets+0x10);
            sprintf(GObjectBuffer,"Gobject->%lx   Offset->%x",Gobject.Addr,Gobject.Offsets);
            cout << GObjectBuffer <<"\n" <<endl;
            isShow= true;
        }
        if (OffsetsGname>0&&ImGui::Button("获取Matrix",ImVec2(400,75))){
            AddrOffsets Matrix = GetMatrix();
            OffsetsMatrix=Matrix.Offsets;//设置全局Matrix偏移
            sprintf(MatrixBuffer,"Matrix->%lx  Offset->%x",Matrix.Addr,Matrix.Offsets);
            cout << MatrixBuffer <<"\n" <<endl;
            isShow= true;
        }
        if (OffsetsGname>0&&ImGui::Button("获取Uworld",ImVec2(400,75))){
            AddrOffsets Uworld = GetUworld();
            OffsetsUworld = Uworld.Offsets;//设置全局Uworld偏移
            sprintf(UWorldBuffer,"Uworld->%lx  Offset->%x",Uworld.Addr,Uworld.Offsets);
            cout << UWorldBuffer <<"\n" <<endl;
            isShow= true;
        }
        if ((OffsetsGname>0&&OffsetsGobject>0) && ImGui::Button("DumpSDK",ImVec2(400,75))){
            Dumper& Dump = Dumper::GetInstance();
            try
            {
                Dump.Init(LibBase, AddrGNames, AddrGObject + 0x10);
            }
            catch (const char* error)
            {
                printf("%s\n", error);
            }
            Dump.Dump();
        }

        if (isShow && ImGui::Button("保存",ImVec2(400,75))){
            FILE* outFile = fopen("/storage/emulated/0/A_BigWhiteTool/Data.txt", "w+");
            if (outFile != NULL) {
                if (outFile) {
                    fprintf(outFile, "%s\n", GnameBuffer);
                    fprintf(outFile, "%s\n", UWorldBuffer);
                    fprintf(outFile, "%s\n", MatrixBuffer);
                    fprintf(outFile, "%s\n", GObjectBuffer);
                    fclose(outFile);
                    cout<<"保存成功路径：/storage/emulated/0/A_BigWhiteTool\n"<<endl;
                } else {
                    printf("Error opening output file\n");
                }
            }else {
                // 处理文件打开失败的情况
                perror("Error opening file");
            }

        }

        if (isShow){
            ImGui::Text("%s",GnameBuffer,ImVec2(400,75));
            ImGui::Text("%s",UWorldBuffer,ImVec2(400,75));
            ImGui::Text("%s",MatrixBuffer,ImVec2(400,75));
            ImGui::Text("%s",GObjectBuffer,ImVec2(400,75));
        }
    } else{
        ImGui::Text("请先选择进程！",ImVec2(400,75));
    }
    ImGui::End();
}
void ShowpointerToolWindow(){
    //77867a99c0 指向 76c66c5b60
    ImGui::Begin("指针工具");
    static char SearchAddr[128] = "76c66c5b60";
    ImGui::InputText("地址", SearchAddr, IM_ARRAYSIZE(SearchAddr));
    if (ImGui::Button("暂未开放")){/*
        uint64_t knownAddress=0x76c66c5b60;
        // 在此处进行指针扫描
        std::vector<uint64_t> foundPointers;
        // 假设扫描的范围是从0到一个大的地址值
        const uint64_t StartAddress = GetProcessBase(BigWhitePid, false);
        const uint64_t EndAddress = GetProcessBase(BigWhitePid, true);
        printf("%lx,%lx",StartAddress,EndAddress);
        cout << "\n"<<endl;
        // 开始扫描内存
        for (uint64_t i = StartAddress; i < EndAddress; ++i) {
            if (GetAddr(i) == knownAddress){
                foundPointers.push_back(i);
            }
        }
        // 输出找到的指针信息
        std::cout << "Pointers found:" << std::endl;
        for (int i = 0; i < foundPointers.size(); ++i) {
            std::cout << "Pointer at address: "<<foundPointers[i] << std::endl;
        }*/
    }

    ImGui::End();
}