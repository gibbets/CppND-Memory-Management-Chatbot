#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>
#include <memory>
#include <utility>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    std::shared_ptr<GraphNode> _rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    ChatBot(const ChatBot& other) :
        _currentNode(other._currentNode),
    _rootNode(other._rootNode),
    _chatLogic(other._chatLogic),
    _image(new wxBitmap(*other._image))
    {std::cout << "ChatBot Copy Constructor" << std::endl;


    }
 
    ChatBot(ChatBot&& other) noexcept :
    _currentNode(std::exchange(other._currentNode, nullptr)),
    _rootNode(std::exchange(other._rootNode, nullptr)),
    _chatLogic(std::exchange(other._chatLogic, nullptr)),
    _image(std::move(other._image))

    {std::cout << "ChatBot Move Constructor" << std::endl;}
 
    ChatBot& operator=(const ChatBot& other) // copy assignment
    {
        std::cout << "ChatBot Copy Assignment" << std::endl;

        _currentNode = other._currentNode;
     _rootNode = other._rootNode;
        _chatLogic = other._chatLogic;
        _image = new wxBitmap(*other._image);
        return *this;
    }
 
    ChatBot& operator=(ChatBot&& other) noexcept // move assignment
    {
        std::cout << "ChatBot Move Assignment" << std::endl;
            _currentNode = std::exchange(other._currentNode, nullptr);
    _rootNode = std::exchange(other._rootNode, nullptr);
    _chatLogic =std::exchange(other._chatLogic, nullptr);
    _image =std::move(other._image);
        return *this;
    }

    //// STUDENT CODE
    ////

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(std::shared_ptr<GraphNode> rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
