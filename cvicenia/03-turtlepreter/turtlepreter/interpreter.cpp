#include "interpreter.hpp"
#include "controllable.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "heap_monitor.hpp"

namespace turtlepreter {
Node::Node(ICommand *cmd, Cursor *cur) : m_command(cmd), m_cursor(cur), m_parent(nullptr), m_isFocused(false) {}
Node::~Node() { delete m_cursor; delete m_command; for (Node* s : m_subnodes) delete s; }
Node* Node::createLeafNode(ICommand *cmd) { auto* c = new CursorUp(); auto* n = new Node(cmd, c); c->setNode(n); return n; }
Node* Node::createSequentialNode() { auto* c = new SequentialCursor(); auto* n = new Node(nullptr, c); c->setNode(n); return n; }
std::string Node::toString() const { std::stringstream ss; if (m_isFocused) ss << "> "; if (m_command) ss << m_command->toString(); else ss << "Sequential"; if (m_cursor) ss << " [" << m_cursor->toString() << "]"; return ss.str(); }
void Node::addSubnode(Node *sub) { if (!sub) throw std::invalid_argument("subnode is nullptr"); m_subnodes.push_back(sub); sub->m_parent = this; }
Node* Node::getParent() const { return m_parent; }
const std::vector<Node*>& Node::getSubnodes() const { return m_subnodes; }
ICommand* Node::getCommand() const { return m_command; }
Cursor* Node::getCursor() const { return m_cursor; }
void Node::setIsFocused(bool f) { m_isFocused = f; }
bool Node::isFocused() const { return m_isFocused; }
Cursor::Cursor(): m_node(nullptr) {}
void Cursor::setNode(Node *n) { m_node = n; }
Node* Cursor::getNode() const { return m_node; }
Node* CursorUp::next() { return m_node->getParent(); }
void CursorUp::reset() {}
std::string CursorUp::toString() { return "Up"; }
SequentialCursor::SequentialCursor() : m_current(-1) {}
Node* SequentialCursor::next() { m_current++; if (static_cast<size_t>(m_current) < m_node->getSubnodes().size()) return m_node->getSubnodes()[m_current]; return m_node->getParent(); }
void SequentialCursor::reset() { m_current = -1; }
std::string SequentialCursor::toString() { if (static_cast<size_t>(m_current + 1) < m_node->getSubnodes().size()) return "Child " + std::to_string(m_current+2) + "/" + std::to_string(m_node->getSubnodes().size()); return "Up"; }
Interpreter::Interpreter(Node* r) : m_root(r), m_current(nullptr), m_somethingExecuted(false), m_stopOnNodeWithoutCommand(true) { reset(); }
void Interpreter::interpretStep(Controllable& c) { if(isFinished()) return; ICommand* cmd = m_current->getCommand(); if(cmd) { if(cmd->canBeExecutedOn(c)) { cmd->execute(c); m_somethingExecuted = true; } else { std::cout << "Cmd '" << cmd->toString() << "' cannot be executed." << std::endl; }} moveCurrent(); }
void Interpreter::interpretAll(Controllable& c) { reset(); c.reset(); while(!isFinished()) { ICommand* cmd = m_current->getCommand(); if (cmd) { if(cmd->canBeExecutedOn(c)) cmd->execute(c); else std::cout << "Cmd '" << cmd->toString() << "' cannot be executed." << std::endl; } moveCurrent(); }}
void Interpreter::reset() { m_somethingExecuted = false; resetNodeCursors(m_root); if(m_current) m_current->setIsFocused(false); m_current = m_root; if(m_current) m_current->setIsFocused(true); if(!m_stopOnNodeWithoutCommand && m_current && !m_current->getCommand()) moveCurrent(); }
void Interpreter::resetNodeCursors(Node* n) { if(!n) return; n->getCursor()->reset(); for(auto* s : n->getSubnodes()) resetNodeCursors(s); }
bool Interpreter::isFinished() const { return m_current == nullptr; }
bool Interpreter::wasSomethingExecuted() const { return m_somethingExecuted; }
bool Interpreter::stopOnNodeWithoutCommand() const { return m_stopOnNodeWithoutCommand; }
void Interpreter::setStopOnNodeWithoutCommand(bool v) { m_stopOnNodeWithoutCommand = v; }
Node* Interpreter::getRoot() const { return m_root; }
Node* Interpreter::getCurrent() const { return m_current; }
void Interpreter::moveCurrent() { if(isFinished()) return; do { if(m_current) m_current->setIsFocused(false); m_current = m_current->getCursor()->next(); if(m_current) m_current->setIsFocused(true); } while(m_current && !m_stopOnNodeWithoutCommand && !m_current->getCommand()); }
}