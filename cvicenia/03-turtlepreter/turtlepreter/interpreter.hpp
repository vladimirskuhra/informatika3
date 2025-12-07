#ifndef TURTLEPRETER_INTERPRETER_HPP
#define TURTLEPRETER_INTERPRETER_HPP

#include <string>
#include <vector>

namespace turtlepreter { class Controllable; }

namespace turtlepreter {
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(Controllable &c) = 0;
    virtual bool canBeExecutedOn(Controllable &c) = 0;
    virtual std::string toString() = 0;
};
class Cursor;
class Node {
public:
    static Node* createLeafNode(ICommand *cmd);
    static Node* createSequentialNode();
    ~Node();
    std::string toString() const;
    void addSubnode(Node *sub);
    Node* getParent() const;
    const std::vector<Node*>& getSubnodes() const;
    ICommand* getCommand() const;
    Cursor* getCursor() const;
    void setIsFocused(bool f);
    bool isFocused() const;
private:
    Node(ICommand *cmd, Cursor *cur);
    ICommand *m_command; Cursor *m_cursor; Node *m_parent;
    std::vector<Node*> m_subnodes; bool m_isFocused;
};
class Cursor {
public:
    Cursor(); virtual ~Cursor() = default; void setNode(Node* n); Node* getNode() const;
    virtual Node* next() = 0; virtual void reset() = 0; virtual std::string toString() = 0;
protected: Node *m_node;
};
class CursorUp : public Cursor { public: Node* next() override; void reset() override; std::string toString() override; };
class SequentialCursor : public Cursor {
public:
    SequentialCursor(); Node* next() override; void reset() override; std::string toString() override;
private: int m_current;
};
class Interpreter {
public:
    Interpreter(Node* root); void interpretStep(Controllable& c); void interpretAll(Controllable& c);
    void reset(); bool isFinished() const; bool wasSomethingExecuted() const;
    bool stopOnNodeWithoutCommand() const; void setStopOnNodeWithoutCommand(bool v);
    Node* getRoot() const; Node* getCurrent() const;
private:
    void moveCurrent(); void resetNodeCursors(Node* n);
    Node *m_root; Node *m_current; bool m_somethingExecuted; bool m_stopOnNodeWithoutCommand;
};
}
#endif