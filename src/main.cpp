#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "UI/UIComponents.h"
#include "Domain/FolderService.h"
#include <nfd.h>



int main() {

    if (!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Color Baker", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    UIComponents uiState;

    NFD_Init();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Folder Settings");

        if (ImGui::Button("Open Folder")) {

            nfdchar_t *outPath = NULL;
            nfdresult_t chosenPath = NFD_PickFolder(&outPath, NULL);

            if (chosenPath == NFD_OKAY) {
                uiState.selectedFolder = outPath;
                uiState.hasFolderSelected = true;
                uiState.imageFiles = FolderService::ScanForImages(uiState.selectedFolder);
            }
        }

        if (uiState.hasFolderSelected) {
            ImGui::Text("Selected: %s", uiState.selectedFolder.string().c_str());

            if (ImGui::BeginListBox("Images Found")) {
                for (const auto& file : uiState.imageFiles) {
                    ImGui::Selectable(file.c_str());
                }
                ImGui::EndListBox();
            } else {
                ImGui::Text("No folder selected");
            }
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0,0, display_w, display_h);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    NFD_Quit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}