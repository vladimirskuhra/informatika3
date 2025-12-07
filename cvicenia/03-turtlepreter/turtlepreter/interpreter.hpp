#ifndef TURTLEPRETER_INTERPRETER_HPP
#define TURTLEPRETER_INTERPRETER_HPP

#include "turtle.hpp"

#include <string>
#include <vector>

namespace turtlepreter {

class ICommand;
class Cursor; // Pred-deklarácia pre cyklickú závislosť

class Node {
public:
    // Továrenské metódy na vytváranie vrcholov
    static Node* createLeafNode(ICommand *command);
    static Node* createSequentialNode();

    ~Node();

    std::string toString() const;

    void addSubnode(Node *subnode);
    Node *getParent() const;
    const std::vector<Node *> &getSubnodes() const;
    ICommand *getCommand() const;
    
    // Nové metódy pre prácu s kurzorom a označením vrcholu
    Cursor *getCursor() const;
    void setIsFocused(bool focused);
    bool isFocused() const;

private:
    // Súkromný konštruktor, aby sa vrcholy vytvárali len cez továrenské metódy
    Node(ICommand *command, Cursor *cursor);

    ICommand *m_command;
    Cursor *m_cursor;
    Node *m_parent;
    std::vector<Node *> m_subnodes;
    bool m_isFocused;
};

// ==================================================

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(Turtle &turtle) = 0;
    virtual std::string toString() = 0;
};

// --------------------------------------------------

class CommandMove : public ICommand {
public:
    CommandMove(float d);
    void execute(Turtle &turtle) override;
    std::string toString() override;
private:
    float m_d;
};

// --------------------------------------------------

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

    // Nové metódy pre krokovanie a správu stavu
    void interpretStep(Turtle &turtle);
    void interpretAll(Turtle &turtle);
    void reset();

    // Metódy na kontrolu stavu pre GUI
    bool isFinished() const;
    bool wasSomethingExecuted() const;
    bool stopOnNodeWithoutCommand() const;
    void setStopOnNodeWithoutCommand(bool val);

    Node *getRoot() const;
    Node *getCurrent() const;

private:
    void moveCurrent();
    void resetNodeCursors(Node* node);

    Node *m_root;
    Node *m_current;
    bool m_somethingExecuted;
    bool m_stopOnNodeWithoutCommand;
};

// ==================================================
// Abstraktná trieda pre kurzory
class Cursor {
public:
    Cursor();
    virtual ~Cursor() = default;

    void setNode(Node *node);
    Node *getNode() const;

    virtual Node* next() = 0;
    virtual void reset() = 0;
    virtual std::string toString() = 0;

protected:
    Node *m_node;
};

// Kurzor pre listy stromu (ide vždy hore k rodičovi)
class CursorUp : public Cursor {
public:
    Node* next() override;
    void reset() override;
    std::string toString() override;
};

// Kurzor pre vnútorné uzly (prechádza deťmi a potom ide hore)
class SequentialCursor : public Cursor {
public:
    SequentialCursor();
    Node* next() override;
    void reset() override;
    std::string toString() override;

private:
    int m_current;
};


} // namespace turtlepreter

#endif