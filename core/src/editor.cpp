#include "editor.h"
#include "nlohmann/json.hpp"

#include <fstream>

#include "model_basic.h"
#include "sound.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "model_complex.h"
#include <entt/entt.hpp>
#include "scripts.h"


void Editor::Save() {
    nlohmann::json data = nlohmann::json::object();
    std::vector<nlohmann::json> modelsVector = { };
    for (auto t : assetManager->models) {
        nlohmann::json model = nlohmann::json::object();
        model["name"] = t->name;
        model["uuid"] = t->uuid;
        model["type"] = t->type;
        if (ModelComplex* complex = dynamic_cast<ModelComplex*>(t))
        {
            model["path"] = complex->path;
        }
        modelsVector.push_back(model);
    }

    data["models"] = modelsVector;
    std::vector<nlohmann::json> entitiesVector = { };

    auto view = manager->registry.view<Thing*>();
    for (auto [e, thing] : view.each()) {
        nlohmann::json entity = nlohmann::json::object();
        entity["uuid"] = thing->uuid;
        entity["x"] = thing->x;
        entity["y"] = thing->y;
        entity["z"] = thing->z;
        entity["model"] = thing->model->uuid;
        if (manager->registry.any_of<Script*>(e)) {
            auto script = manager->registry.get<Script*>(entity);
            entity["script"] = script->id;
        }
        entitiesVector.push_back(entity);
    }

    data["entities"] = entitiesVector;

    std::string s = data.dump();
    std::ofstream myfile;
    myfile.open("example.json");
    myfile << s;
    myfile.close();
}

void Editor::Play() {
    eventManager->play = true;
    eventManager->breakRender = true;
}

void Editor::Load() {
    std::ifstream ifs("example.json");
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    auto j3 = nlohmann::json::parse(content);

    manager->registry.clear();
    assetManager->models.clear();

    assetManager->Load(j3["models"]);
    for (auto jsonT : j3["entities"]) {
        this->manager->CreateThing(jsonT);
    }
}

void Editor::RenderProperties() {
    if (selectedThing != -1) {
        {
            try {
                auto t = manager->ThingById(selectedThing);
                char buffer[50];
                sprintf(buffer, "Entity %d", t->uuid);

                ImGui::Begin(buffer);

                ImGui::Text("Position");

                ImGui::InputFloat("X", &t->x);
                ImGui::InputFloat("Y", &t->y);
                ImGui::InputFloat("Z", &t->z);

                ImGui::Text("Shader");
                sprintf(buffer, "ID %d", t->shader->ID);
                ImGui::Text(buffer);

                sprintf(buffer, "Meshes (%d)", t->model->meshes.size());
                ImGui::Text(buffer);

                for (int i = 0; i < t->model->meshes.size(); i++) {
                    sprintf(buffer, "Mesh %d", i + 1);
                    ImGui::Text(buffer);
                    sprintf(buffer, "Vertices (%d)", t->model->meshes[i].vertices.size());
                    ImGui::Text(buffer);
                    sprintf(buffer, "Textures (%d)", t->model->meshes[i].textures.size());
                    ImGui::Text(buffer);

                    for (int j = 0; j < t->model->meshes[i].textures.size(); j++) {
                        sprintf(buffer, "T%d - %s", j + 1, t->model->meshes[i].textures[j].type.c_str());
                        ImGui::Text(buffer);
                        sprintf(buffer, "%s", t->model->meshes[i].textures[j].path.c_str());
                        ImGui::Text(buffer);
                       
                    }
                   
                }

                ImGui::Text("Actions");

                if (ImGui::Button("Delete")) {
                    int toDelete = selectedThing;
                    selectedThing = -1;
                    manager->Delete(toDelete);
                }

                if (ImGui::Button("Unselect")) {
                    selectedThing = -1;
                }

                ImGui::End();
            }
            catch (const std::exception&) {
                selectedThing = -1;
            }
        }
    }
}

void Editor::RenderPlayingEditor() {
    ImGui::Begin("Options");
    {
        if (ImGui::Button("Quit")) {
            eventManager->play = false;
            eventManager->breakRender = true;
        }
    }
    ImGui::End();
}

void Editor::RenderEditorGUI() {
    ImVec2 sizeAppWindow = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(200, 0), ImGuiCond_Always);

    char buffer[500];

    ImGui::Begin("Options");
    {
        if (ImGui::Button("Play")) {
            Play();
        }
   
        if (ImGui::Button("Load Project")) {
            Load();
        }

        if (ImGui::Button("Save Project")) {
            Save();
        }
    }
    ImGui::End();

    ImGui::Begin("Things");
    {
        if (ImGui::Button("New Thing", ImVec2(120, 20))) {
            selectedThing = manager->registry.get<Thing*>(manager->CreateThing())->uuid;
        }

        auto view = manager->registry.view<Thing*>();
        for (auto [entity, thing] : view.each()) {
            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

            sprintf(buffer, "Entity %d", thing->uuid);
            if (ImGui::Button(buffer)) {
                this->selectedThing = thing->uuid;
            }
        }

    }
    ImGui::End();

    ImGui::Begin("Models");

    if (ImGui::Button("Add Model")) {
        this->assetManager->models.push_back(new ModelBasic());
    }

    for (Model* m : assetManager->models) {
        sprintf(buffer, "%s", m->name.c_str());
        ImGui::Text(buffer);
    }
    ImGui::End();


    RenderProperties();
}

void Editor::Render() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (!eventManager->play) {
        RenderEditorGUI();
    } else {
        RenderEditorGUI();

        RenderPlayingEditor();
    }
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
