#include "turtle_gui.hpp"
#include <imgui/imgui.h>
#include "heap_monitor.hpp"

namespace turtlepreter {
TurtleGUI::TurtleGUI(Controllable *c, Interpreter *i)
	: m_controllable(c),
	  m_interpreter(i),
	  m_widthLeftPanel(250) {
}

void TurtleGUI::build() {
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::Begin(
		"TP",
		nullptr,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse
	);

	buildTopBar();
	ImGui::Separator();
	buildLeftPanel();
	ImGui::SameLine();
	buildSplitter();
	ImGui::SameLine();
	buildRightPanel();

	ImGui::End();
}

void TurtleGUI::buildTopBar() {
	ImGui::BeginDisabled(m_interpreter->isFinished());
	if (ImGui::Button("Run", {100, 0})) {
		m_interpreter->interpretAll(*m_controllable);
	}
	ImGui::EndDisabled();

	ImGui::SameLine();

	ImGui::BeginDisabled(m_interpreter->isFinished());
	if (ImGui::Button("Step", {100, 0})) {
		m_interpreter->interpretStep(*m_controllable);
	}
	ImGui::EndDisabled();

	ImGui::SameLine();

	ImGui::BeginDisabled(
		!m_interpreter->wasSomethingExecuted() &&
		m_interpreter->getCurrent() == m_interpreter->getRoot()
	);
	if (ImGui::Button("Reset", {100, 0})) {
		m_controllable->reset();
		m_interpreter->reset();
	}
	ImGui::EndDisabled();

	ImGui::SameLine();

	ImGui::BeginDisabled(m_interpreter->isFinished());
	bool stopOnNoCmd = m_interpreter->stopOnNodeWithoutCommand();
	if (ImGui::Checkbox("Stop on no-cmd", &stopOnNoCmd)) {
		m_interpreter->setStopOnNodeWithoutCommand(stopOnNoCmd);
	}
	ImGui::EndDisabled();
}

void TurtleGUI::buildLeftPanel() {
	ImGui::BeginChild("Script", {m_widthLeftPanel, 0}, true);
	populateTreeNodes(m_interpreter->getRoot());
	ImGui::EndChild();
}

void TurtleGUI::buildSplitter() {
	ImGui::PushStyleColor(ImGuiCol_Button, {0.5f, 0.5f, 0.5f, 1.0f});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0.7f, 0.7f, 0.7f, 1.0f});
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0.9f, 0.9f, 0.9f, 1.0f});

	ImGui::Button("|", {5, ImGui::GetContentRegionAvail().y});
	if (ImGui::IsItemActive()) {
		m_widthLeftPanel += ImGui::GetIO().MouseDelta.x;
		if (m_widthLeftPanel < 100) {
			m_widthLeftPanel = 100;
		}
	}

	ImGui::PopStyleColor(3);
}

void TurtleGUI::buildRightPanel() {
	ImGui::BeginChild("Turtle", {0, 0}, true);

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	friimgui::Region region = friimgui::Region::createFromAvail();

	drawList->AddRectFilled(region.getP0(), region.getP2(), IM_COL32(60, 60, 60, 255));
	region.reserveSpace();
	m_controllable->draw(region);

	ImGui::EndChild();
}

void TurtleGUI::populateTreeNodes(Node *n) {
	if (n) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
		if (n->getSubnodes().empty()) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		const std::string label = n->toString();
		if (ImGui::TreeNodeEx(n, flags, "%s", label.c_str())) {
			for (Node *sn : n->getSubnodes()) {
				populateTreeNodes(sn);
			}
			ImGui::TreePop();
		}
	}
}
} // namespace turtlepreter