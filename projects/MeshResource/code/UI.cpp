#include "config.h"
#include "UI.h"
#include "imgui.h"
#include <sstream>
#include <iostream>
#include <fstream>


UI::UI()
{
}

UI::~UI()
{
}

void UI::RenderUI(){
    if (this->window->IsOpen())
	{
		bool show = true;
		// create a new window
		ImGui::Begin("Shader Sources", &show, ImGuiWindowFlags_NoSavedSettings);

		// create text editors for shader code
		ImGui::InputTextMultiline("Vertex Shader", vsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);

		ImGui::InputTextMultiline("Pixel Shader", fsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);
		// apply button
		if (ImGui::Button("Apply"))
		{
			// if pressed we compile the shaders
			this->CompileShaders();
		}
		if (this->compilerLog.length())
		{
			// if compilation produced any output we display it here
			ImGui::TextWrapped(this->compilerLog.c_str());
		}
		// close window
		ImGui::End();
	}
}

void UI::IncreaseScore(){
    this->points++;
    SaveScore();
}

void UI::SaveScore(){
    if(this->points > highscore){
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