#include "turtle_gui.hpp"

#include <libfriimgui/types.hpp>

#include <imgui/imgui.h>

namespace turtlepreter {

TurtleGUI::TurtleGUI(Turtle *turtle, Interpreter *interpreter) :
    m_turtle(turtle),
    m_interpreter(interpreter),
    m_widthLeftPanel(250) { // Zväčšil som panel pre lepšiu čitateľnosť
}

void TurtleGUI::build() {
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin(
        "Turtlepreter",
        nullptr,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
    );

    buildTopBar();
    buildLeftPanel();
    ImGui::SameLine();
    buildSplitter();
    ImGui::SameLine();
    buildRightPanel();

    ImGui::End();
}

void TurtleGUI::buildTopBar() {
    // Tlačidlo Run
    ImGui::BeginDisabled(m_interpreter->isFinished());
    if (ImGui::Button("Run", ImVec2(100, 0))) {
        m_interpreter->interpretAll(*m_turtle);
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    // Tlačidlo Step
    ImGui::BeginDisabled(m_interpreter->isFinished());
    if (ImGui::Button("Step", ImVec2(100, 0))) {
        m_interpreter->interpretStep(*m_turtle);
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    // Tlačidlo Reset
    ImGui::BeginDisabled(!m_interpreter->wasSomethingExecuted() && m_interpreter->getCurrent() == m_interpreter->getRoot());
    if (ImGui::Button("Reset", ImVec2(100, 0))) {
        m_turtle->reset();
        m_interpreter->reset();
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    // Checkbox pre preskakovanie uzlov
    ImGui::BeginDisabled(m_interpreter->isFinished());
    bool stop = m_interpreter->stopOnNodeWithoutCommand();
    if (ImGui::Checkbox("Stop on node without command", &stop)) {
        m_interpreter->setStopOnNodeWithoutCommand(stop);
    }
    ImGui::EndDisabled();
}

void TurtleGUI::buildLeftPanel() {
    ImGui::BeginChild("Script", ImVec2(m_widthLeftPanel, 0), true);
    populateTreeNodes(m_interpreter->getRoot());
    ImGui::EndChild();
}

void TurtleGUI::buildSplitter() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
    ImGui::Button("|", ImVec2(5, ImGui::GetContentRegionAvail().y));
    if (ImGui::IsItemActive()) {
        m_widthLeftPanel += ImGui::GetIO().MouseDelta.x;
        if (m_widthLeftPanel < 100) {
            m_widthLeftPanel = 100;
        }
    }
    ImGui::PopStyleColor(3);
}

void TurtleGUI::buildRightPanel() {
    ImGui::BeginChild("Turtle", ImVec2(0, 0), true);
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    friimgui::Region region = friimgui::Region::createFromAvail();
    drawList->AddRectFilled(region.getP0(), region.getP2(), IM_COL32(60, 60, 60, 255));
    region.reserveSpace();
    m_turtle->draw(region);
    ImGui::EndChild();
}

void TurtleGUI::populateTreeNodes(Node *node) {
    if (node != nullptr) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
        
        if (node->getSubnodes().empty()) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }

        // Získame textovú reprezentáciu priamo z vrchola
        const std::string nodeStr = node->toString();
        
        if (ImGui::TreeNodeEx(node, flags, "%s", nodeStr.c_str())) {
            for (Node* subnode : node->getSubnodes()) {
                populateTreeNodes(subnode);
            }
            ImGui::TreePop();
        }
    }
}

} // namespace turtlepreter