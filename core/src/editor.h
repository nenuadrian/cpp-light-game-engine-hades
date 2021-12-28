#pragma once
#include "manager.h"
#include "sound.h"
#include "plugin.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

class Editor : public Plugin {
    int selectedThing = -1;
public:
    Editor() : Plugin("Editor") {}
    void virtual Render();
    virtual ~Editor() {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
   
    void virtual Init(GLFWwindow* window, AssetManager* _assetManager, ThingManager* _manager, SoundManager* _soundManager) {
        this->manager = _manager;
        this->soundManager = _soundManager;
        this->assetManager = _assetManager;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, false);
        ImGui_ImplOpenGL2_Init();
        ImGui::StyleColorsDark();
    }

    void virtual scrollCallback(GLFWwindow* w, double x, double y) {
        ImGui_ImplGlfw_ScrollCallback(w, x, y);
    }

    void virtual mouseButtonCallback(GLFWwindow* w, int button, int action, int modsy) {
        ImGui_ImplGlfw_MouseButtonCallback(w, button, action, modsy);
    }

    void virtual keyCallBack(GLFWwindow* w, int key, int scancode, int action, int mods) {
        ImGui_ImplGlfw_KeyCallback(w, key, scancode, action, mods);
    }

    void virtual charCallback(GLFWwindow* w, unsigned int c) {
        ImGui_ImplGlfw_CharCallback(w, c);
    }

private:
    void Save();
    void Load();
    void RenderProperties();
    void Editor::RenderEditorGUI();
};

