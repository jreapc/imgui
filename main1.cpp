#include <iostream>
#include "tpi/glfw/GLFW/glfw3.h"
#include "tpi/imgui/imgui.h"
#include "tpi/backend/imgui_impl_glfw.h"

#include "tpi/backend/imgui_impl_opengl3.h"

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) return -1;

    // Set OpenGL versions (3.3 Core is widely compatible)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a desktop window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Test", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(4); // Enable v-sync

    // 2. Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    // Enable Docking
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           

// Enable Multi-Viewport / Popout Windows (Optional but highly recommended)
io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         


    // 3. Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main application loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        // 4. SHOW THE DEMO WINDOW
        ImGui::ShowDemoWindow();

        // Rendering setup
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup backend contexts
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


/*
 "Forgot to call UpdatePlatformWindows() in main loop after EndFrame()? Check examples/ applications for reference.");

*/