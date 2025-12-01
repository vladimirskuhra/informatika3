#ifndef TURTLEPRETER_INTERPRETER_HPP
#define TURTLEPRETER_INTERPRETER_HPP

#include "turtle.hpp"

#include <string>
#include <vector>

namespace turtlepreter {

class ICommand;

class Node {
public:

    static Node* createLeafNode(ICommand *command);
    static Node *createSequentialNode();


    
    /*
     * Vráti reťazec reprezentujúci vrchol.
     * Ak vrchol nemá priradený command, vráti "No command".
     * Inak vráti reťazec reprezentujúci command.
     */
    std::string toString() const;

    /**
     * Uloží @p subnode do zoznamu synov.
     * Nastaví sa ako otec @p subnode
     * Preberá zodpovednosť za životný cyklus @p subnode
     */
    void addSubnode(Node *subnode);

    Node *getParent() const;
    const std::vector<Node *> &getSubnodes() const;

    ICommand *getCommand() const;

    Cursor *getCursor() const;
    void setIsFocused(bool focused);
    bool isFocused() const;

    /**
     * Odstráni synov vrcholu.
     */
    ~Node();


private:
    /**
     * Inicializuje vrchol s príkazom.
     */
    Node(ICommand *command, Cursor *cursor);
    ICommand *m_command;
    Cursor *m_cursor;
    Node *m_parent;
    std::vector<Node *> m_subnodes;
    bool m_isFocused = false;
};

// ==================================================

class ICommand {
public:
    virtual ~ICommand() = default;

    /**
     * Vykoná akciu s korytnačkou @p turtle
     */
    virtual void execute(Turtle &turtle) = 0;

    /**
     * Vráti reťazec popisujúci príkaz.
     */
    virtual std::string toString() = 0;
};

// --------------------------------------------------

/**
 * Posunie korytnačku o zadanú vzdialenosť v smere jej natočenia.
 */
class CommandMove : public ICommand {
public:
    CommandMove(float d);

    void execute(Turtle &turtle) override;
    std::string toString() override;

private:
    float m_d;
};

// --------------------------------------------------

/**
 * Presunie korytnačku na zadané súradnice.
 */
class CommandJump : public ICommand {
public:
    CommandJump(float x, float y);

    void execute(Turtle &turtle) override;
    std::string toString() override;

private:
    float m_x;
    float m_y;
};

// --------------------------------------------------

/**
 * Zmení natočenie korytnačky.
 */
class CommandRotate : public ICommand {
public:
    CommandRotate(float angleRad);

    void execute(Turtle &turtle) override;
    std::string toString() override;

private:
    float m_angleRad;
};

// ==================================================

class Interpreter {
public:
    Interpreter(Node *root);

    // Execute a single step (current node) and advance the interpreter.
    void interpretStep(Turtle &turtle);

    // Interpret entire tree (reset + run until finished).
    void interpretAll(Turtle &turtle);

    // Reset interpreter state (cursors, flags, current node).
    void reset();

    bool isFinished() const;
    bool wasSomethingExecuted() const;

    bool stopOnNodeWithoutCommand() const;
    void setStopOnNodeWithoutCommand(bool val);

    Node *getRoot() const;

private:
    Node *m_root;
    Node *m_current;
    bool m_somethingExecuted;
    bool m_stopOnNodeWithoutCommand;

    // Advance m_current according to current node's cursor logic.
    void moveCurrent();
};

class Cursor {
public:
    Cursor() : m_node(nullptr) {}
    virtual ~Cursor() = default;

    void setNode(Node *node) { m_node = node; }
    Node *getNode() const { return m_node; }

    virtual Node* next() = 0;
    virtual void reset() = 0;
    virtual std::string toString() = 0;

protected:
    Node *m_node;
};

class CursorUp : public Cursor {
public:
    Node* next() override;
    void reset() override {}
    std::string toString() override { return "Up"; }
};

class SequentialCursor : public Cursor {
public:
    SequentialCursor() : m_current(-1) {}
    Node* next() override;
    void reset() override;
    std::string toString() override;

private:
    int m_current;
};

} // namespace turtlepreter

#endif
