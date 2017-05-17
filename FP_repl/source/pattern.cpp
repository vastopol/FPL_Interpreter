#include "../header/pattern.h"

// std::string expression;
// Node* root;
// Interpreter* interpreter;
// Action* action;

//--------------------------------

Pattern::Pattern(std::string s)
    : expression(s), root(0), interpreter( new Interpreter() ), action( new Action() )
{}
//--------------------------------------------------------------

Pattern::~Pattern()
{
    // std::cout << "PATTERN DESTRUCTOR" << std::endl;
    
    delete root;
    root = 0;
    delete interpreter; 
    interpreter = 0;
    delete action; 
    action = 0;
}
//--------------------------------------------------------------

void Pattern::setRoot(Node* n)
{
    this->root = n;
}
//---------------------------------------------------------------

Node* Pattern::getRoot()     // get root of abstract syntax tree
{
    return root;
}
//--------------------------------------------------------------

Interpreter* Pattern::getI() // get interpreter object
{
    return interpreter;
}
//--------------------------------------------------------------

Action* Pattern::getA()      // get execution object
{
    return action;
}
//--------------------------------------------------------------

void Pattern::preOrder(Node* n)
{
    if(n == NULL)
    {
      return;
    }
    

    std::cout << "(";
    n->getKey()->print();
    std::cout << "), ";

    preOrder(n->getLeft());

    preOrder(n->getRight());
}
//--------------------------------------------------

void Pattern::inOrder(Node* n)
{
    if(n == NULL)
    {
      return;
    }
    
    inOrder(n->getLeft());

    std::cout << "(";
    n->getKey()->print();
    std::cout << "), ";
    
    inOrder(n->getRight());
}
//--------------------------------------------------

void Pattern::postOrder(Node* n)
{
    if(n == NULL)
    {
      return;
    }
    
    postOrder(n->getLeft());

    postOrder(n->getRight());

    std::cout << "(";
    n->getKey()->print();
    std::cout << "), ";
}
//--------------------------------------------------


 void Pattern::generateTree(std::ofstream& out, Node* n) // broken...
 {
     if (n == 0)
     {
         return;
     }
     out << '\n';
     out /*<< n->getKey()->stringify()*/ << " [label=\"" << n->getKey()->stringify();
     out << "\"];";
     if (n->getLeft() != 0)
     {
        out /*<< "\n" << n->getKey()->stringify()*/ << " -> " << (n->getLeft())->getKey()->stringify() << ";";
        generateTree(out, n->getLeft());
     }
     if (n->getRight() != 0)
     {
        out /*<< "\n" << n->getKey()->stringify()*/ << " -> " << (n->getRight())->getKey()->stringify() << ";";
        generateTree(out, n->getRight());
     }
 }


 void Pattern::visualizeTree(const std::string& outputFilename)
 {
    std::ofstream outFS;
    outFS.open(outputFilename.c_str());
    if(!outFS.is_open())
    {
        std::cout << "Error opening " << outputFilename << std::endl;
        return;
    }
    outFS << "digraph G {" << std::endl;
    generateTree(outFS,root);
    outFS << "}";
    outFS.close();
    std::string jpgFilename = outputFilename.substr(0,outputFilename.size()-4) + ".jpg";
    std::string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}