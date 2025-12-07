#include "interpreter.hpp"
#include <stdexcept>
#include <sstream>

#include "heap_monitor.hpp"

namespace turtlepreter {

// ==================================================
// Node
// ==================================================

// Súkromný konštruktor
Node::Node(ICommand *command, Cursor *cursor) :
    m_command(command),
    m_cursor(cursor),
    m_parent(nullptr),
    m_subnodes(),
    m_isFocused(false)
{
}

// Deštruktor musí uvoľniť pamäť kurzora a všetkých synov
Node::~Node() {
    delete m_cursor;
    delete m_command;
    for (Node *sub : m_subnodes) {
        delete sub;
    }
    m_subnodes.clear();
}

// Továrenská metóda pre listy
Node* Node::createLeafNode(ICommand *command) {
    Cursor* cursor = new CursorUp();
    Node* node = new Node(command, cursor);
    cursor->setNode(node);
    return node;
}

// Továrenská metóda pre vnútorné uzly
Node* Node::createSequentialNode() {
    Cursor* cursor = new SequentialCursor();
    Node* node = new Node(nullptr, cursor);
    cursor->setNode(node);
    return node;
}

std::string Node::toString() const {
    std::stringstream ss;
    // Pridanie prefixu pre aktuálne označený vrchol
    if (m_isFocused) {
        ss << "> ";
    }

    if (m_command) {
        ss << m_command->toString();
    } else {
        ss << "Sequential";
    }

    // Pridanie stavu kurzora
    if (m_cursor) {
        ss << " [" << m_cursor->toString() << "]";
    }
    
    return ss.str();
}

void Node::addSubnode(Node *subnode) {
    if (subnode == nullptr) {
        throw std::invalid_argument("subnode is nullptr");
    }
    m_subnodes.push_back(subnode);
    subnode->m_parent = this;
}

Node *Node::getParent() const { return m_parent; }
const std::vector<Node *> &Node::getSubnodes() const { return m_subnodes; }
ICommand *Node::getCommand() const { return m_command; }
Cursor *Node::getCursor() const { return m_cursor; }
void Node::setIsFocused(bool focused) { m_isFocused = focused; }
bool Node::isFocused() const { return m_isFocused; }


// ==================================================
// Commands (bezo zmeny)
// ==================================================
CommandMove::CommandMove(float d) : m_d(d) {}
void CommandMove::execute(Turtle &turtle) { turtle.move(m_d); }
std::string CommandMove::toString() { return "Move " + std::to_string(m_d); }

CommandJump::CommandJump(float x, float y) : m_x(x), m_y(y) {}
void CommandJump::execute(Turtle &turtle) { turtle.jump(m_x, m_y); }
std::string CommandJump::toString() { return "Jump " + std::to_string(m_x) + ", " + std::to_string(m_y); }

CommandRotate::CommandRotate(float angleRad) : m_angleRad(angleRad) {}
void CommandRotate::execute(Turtle &turtle) { turtle.rotate(m_angleRad); }
std::string CommandRotate::toString() { return "Rotate " + std::to_string(m_angleRad); }

// ==================================================
// Cursor
// ==================================================
Cursor::Cursor() : m_node(nullptr) {}
void Cursor::setNode(Node *node) { m_node = node; }
Node* Cursor::getNode() const { return m_node; }

// ==================================================
// CursorUp
// ==================================================
Node* CursorUp::next() {
    return m_node->getParent();
}
void CursorUp::reset() {
    // Nemá stav, takže nerobí nič
}
std::string CursorUp::toString() {
    return "Up";
}

// ==================================================
// SequentialCursor
// ==================================================
SequentialCursor::SequentialCursor() : m_current(-1) {}

Node* SequentialCursor::next() {
    m_current++;
    const auto& subnodes = m_node->getSubnodes();
    if (m_current < subnodes.size()) {
        return subnodes[m_current];
    }
    return m_node->getParent();
}

void SequentialCursor::reset() {
    m_current = -1;
}

std::string SequentialCursor::toString() {
    const auto& subnodes = m_node->getSubnodes();
    if (m_current + 1 < subnodes.size()) {
        return "Child " + std::to_string(m_current + 1) + "/" + std::to_string(subnodes.size());
    }
    return "Up";
}

// ==================================================
// Interpreter
// ==================================================
Interpreter::Interpreter(Node *root) : 
    m_root(root), 
    m_current(nullptr), 
    m_somethingExecuted(false),
    m_stopOnNodeWithoutCommand(true)
{
    reset();
}

void Interpreter::interpretStep(Turtle &turtle) {
    if (isFinished()) {
        return;
    }

    m_somethingExecuted = true;
    if (m_current->getCommand()) {
        m_current->getCommand()->execute(turtle);
    }

    moveCurrent();
}

void Interpreter::interpretAll(Turtle &turtle) {
    if (isFinished()) {
        return;
    }
    
    reset();
    while (!isFinished()) {
        interpretStep(turtle);
    }
}

void Interpreter::reset() {
    m_somethingExecuted = false;
    resetNodeCursors(m_root);
    
    if (m_current) {
        m_current->setIsFocused(false);
    }
    
    m_current = m_root;
    
    if (m_current) {
        m_current->setIsFocused(true);
    }
    
    // Ak nemáme zastavovať na prázdnych uzloch a prvý je prázdny, posunieme sa
    if (!m_stopOnNodeWithoutCommand && m_current && !m_current->getCommand()) {
        moveCurrent();
    }
}

void Interpreter::resetNodeCursors(Node* node) {
    if (!node) {
        return;
    }
    node->getCursor()->reset();
    for (Node* subnode : node->getSubnodes()) {
        resetNodeCursors(subnode);
    }
}

bool Interpreter::isFinished() const {
    return m_current == nullptr;
}

bool Interpreter::wasSomethingExecuted() const {
    return m_somethingExecuted;
}

bool Interpreter::stopOnNodeWithoutCommand() const {
    return m_stopOnNodeWithoutCommand;
}

void Interpreter::setStopOnNodeWithoutCommand(bool val) {
    m_stopOnNodeWithoutCommand = val;
}

Node *Interpreter::getRoot() const {
    return m_root;
}

Node *Interpreter::getCurrent() const {
    return m_current;
}

void Interpreter::moveCurrent() {
    if (isFinished()) {
        return;
    }

    do {
        // Zrušenie označenia starého vrcholu
        if (m_current) {
            m_current->setIsFocused(false);
        }

        // Získanie ďalšieho vrcholu
        m_current = m_current->getCursor()->next();

        // Označenie nového vrcholu
        if (m_current) {
            m_current->setIsFocused(true);
        }

        // Opakuj, ak je m_current platný, sme v režime preskakovania
        // a aktuálny vrchol nemá príkaz.
    } while (m_current && !m_stopOnNodeWithoutCommand && !m_current->getCommand());
}


} // namespace turtlepreter