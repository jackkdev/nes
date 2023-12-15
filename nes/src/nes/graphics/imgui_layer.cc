//
// Copyright (c) 2023 - darkrp-is.gay, All rights reserved.
//

#include "imgui_layer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>

#include <utility>

namespace nes {

ImGuiLayer::ImGuiLayer(GLFWwindow *glfw_window,
                       std::shared_ptr<Emulator> emulator)
    : glfw_window_(glfw_window), emulator_(std::move(emulator)) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(glfw_window_, true);
  ImGui_ImplOpenGL3_Init("#version 430");
}

ImGuiLayer::~ImGuiLayer() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

const char *ImGuiLayer::Name() { return "ImGui"; }

void ImGuiLayer::OnDraw(const Renderer &renderer) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

//  ImGui::ShowDemoWindow();

  ImGui::Begin("Emulator");

  if (ImGui::BeginTabBar("TabBar")) {
    DrawRegisters();
    DrawMemoryMap();

    ImGui::EndTabBar();
  }

  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::DrawRegisters() {
  if (ImGui::BeginTabItem("Registers")) {
    ImGui::BeginTable("Registers##2", 6,
                      ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit |
                          ImGuiTableFlags_NoHostExtendX);

    ImGui::TableSetupColumn("A");
    ImGui::TableSetupColumn("X");
    ImGui::TableSetupColumn("Y");
    ImGui::TableSetupColumn("PC");
    ImGui::TableSetupColumn("S");
    ImGui::TableSetupColumn("P");
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();

    const auto &regs = emulator_->GetCpu()->GetRegisters();

    ImGui::TableNextColumn();
    ImGui::Text("0x%02X", regs.a);

    ImGui::TableNextColumn();
    ImGui::Text("0x%02X", regs.x);

    ImGui::TableNextColumn();
    ImGui::Text("0x%02X", regs.y);

    ImGui::TableNextColumn();
    ImGui::Text("0x%04X", regs.pc);

    ImGui::TableNextColumn();
    ImGui::Text("0x%02X", regs.s);

    ImGui::TableNextColumn();
    ImGui::Text("0x%02X", regs.p);

    ImGui::EndTable();

    ImGui::EndTabItem();
  }
}

void ImGuiLayer::DrawMemoryMap() {
  constexpr auto kDatumSpacing = 2.5f;

  auto ram = emulator_->GetCpuRam();

  // Calculate the # of datums we can display per row.
  u32 n_items;
  {
    const auto datum_sz = ImGui::CalcTextSize("00").x;
    const auto avail = ImGui::GetContentRegionAvail();

    // Total Width = 200
    // Datum Width = 6
    // Spacing = 4

    // # of Items = Total Width / (Datum Width + Spacing Per Datum)
    n_items = floor(avail.x / (datum_sz + kDatumSpacing));
  }

  u32 n_rows = ceil(ram->size() / n_items);

  if (ImGui::BeginTabItem("Memory Map")) {
    ImGui::Text("n_items: %d", n_items);
    ImGui::SameLine();
    ImGui::Text("n_rows: %d", n_rows);

    ImGui::PushStyleColor(ImGuiCol_Button, ImU32(ImColor(0, 0, 0, 0)));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImU32(ImColor(0, 0, 0, 0)));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImU32(ImColor(0, 0, 0, 0)));

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    for (u32 row = 0; row < n_rows; row++) {
      for (u32 col = 0; col < n_items - 1; col++) {
        ImGui::PushID((row * n_items) + col);
        ImGui::Button("00");
        ImGui::SameLine(0.0f, kDatumSpacing);
        ImGui::PopID();
      }

      ImGui::PushID((row * n_items) + n_items - 1);
      ImGui::Button("00");
      ImGui::PopID();
    }

    ImGui::PopStyleVar();

    ImGui::PopStyleColor(3);

    ImGui::EndTabItem();
  }
}

} // namespace nes