#include "config.h"
#include "UI.h"
#include "imgui.h"
#include <iostream>
#include <fstream>


UI::UI()
{
}

UI::~UI()
{
}

void UI::RenderUI(){
    bool show = true;

    if(!isDead){
    // create a new window
    ImGui::SetNextWindowPos({ 0,0 }, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size, ImGuiCond_Always);
    ImGui::Begin("invis_wnd", &show, ImGuiWindowFlags_NoMove       |
                                     ImGuiWindowFlags_NoNav        |
                                     ImGuiWindowFlags_NoDecoration |
                                     ImGuiWindowFlags_NoInputs     |
                                     ImGuiWindowFlags_NoBackground);

    auto size = ImGui::GetMainViewport()->Size;
    ImGui::SetCursorPos({ 0.03f * size.x, 0.03f * size.y });
     //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0.4, 0.3, 1));
    ImGui::Text("%d", points);
    }
    else{
        ImGui::SetNextWindowPos({ 0,0 }, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size, ImGuiCond_Always);
        ImGui::Begin("GameOver", &show, ImGuiWindowFlags_NoMove       |
                                        ImGuiWindowFlags_NoNav        |
                                        ImGuiWindowFlags_NoDecoration |
                                        ImGuiWindowFlags_NoInputs);

        auto size = ImGui::GetMainViewport()->Size;
        ImGui::SetWindowFontScale(1.5);

        // rip
        auto textWidth = ImGui::CalcTextSize("Game Over!").x;
        ImGui::SetCursorPos({(size.x-textWidth)/2,size.y/3});
        ImGui::Text("Game Over!");

        // Points
        textWidth = ImGui::CalcTextSize("Highscore: ").x;
        ImGui::SetCursorPos({(size.x-textWidth)/2,size.y/2.5});
        ImGui::Text("Highscore: %d", highscore);

        textWidth = ImGui::CalcTextSize("Your points: !").x;
        ImGui::SetCursorPos({(size.x-textWidth)/2,size.y/2.2});
        ImGui::Text("Your points: %d!", points);

        if(glfwGetTime() - currentTime > 1){
            currentTime = glfwGetTime();
            blinkResetMsg = !blinkResetMsg;
        }

        if(blinkResetMsg){
            // Reset info
            textWidth = ImGui::CalcTextSize("Press the A button to reset!").x;
            ImGui::SetCursorPos({(size.x-textWidth)/2,size.y/1.5});
            ImGui::Text("Press the A button to reset!");
        }
    }
    
    // close window
    ImGui::End();
}

void UI::SetIsDead(bool isDeadIn){
    this->isDead = isDeadIn;
    if(!this->isDead){
        this->points = 0;
    }
}

void UI::IncreaseScore(){
    points++;
    SaveScore();
}

void UI::SaveScore(){
    if(points > highscore){
        highscore = points;
        std::ofstream highscoreFile;
        highscoreFile.open("highscore.txt");
        highscoreFile.clear();
        highscoreFile << highscore;
        highscoreFile.close();
    }
}

void UI::LoadScore(){
    std::ifstream highscoreFile;
    highscoreFile.open("highscore.txt");
    std::string line;
    getline(highscoreFile, line);
    highscoreFile.close();
    highscore = stoi(line);
}