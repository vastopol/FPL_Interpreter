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
//--------------------------------------------------------------

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
//--------------------------------------------------------------

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
//--------------------------------------------------------------

std::stack<std::string> Pattern::postOrderCheckWrap(Node* n) // wrapper to save && return state
{
    while(!secret_stk.empty()) // clear stack
    {
        secret_stk.pop();
    }

    postOrderCheck(n);  // fill stack

    return secret_stk;
}
//--------------------------------------------------------------

void Pattern::postOrderCheck(Node* n) // actual recursive traversal
{
    if(n == NULL)
    {
      return;
    }

    postOrderCheck(n->getLeft());

    postOrderCheck(n->getRight());

    secret_stk.push( n->getKey()->stringify() ); // save token
}
//--------------------------------------------------------------

// need to handle special chars that graphviz can't represent
 void Pattern::generateTree(std::ofstream& out, Node* n, int i=1)
 {
     if (n == 0)
     {
         return;
     }

     std::string temp_M = n->getKey()->stringify();
     if(temp_M == ":"){temp_M = "Colon";}
     if(temp_M == "+"){temp_M = "Add";}
     if(temp_M == "-"){temp_M = "Sub";}
     if(temp_M == "*"){temp_M = "Mul";}
     if(temp_M == "/"){temp_M = "Div";}
     if(temp_M == "%"){temp_M = "Mod";}
     if(temp_M == "^"){temp_M = "Pow";}
     temp_M = temp_M + "_" + std::to_string(i);
     out << '\n'; out << temp_M << " [label=\"" << temp_M; out << "\"];";

     if (n->getLeft() != 0)
     {
        i++;
        std::string temp_L = (n->getLeft())->getKey()->stringify();
        if(temp_L == ":"){temp_L = "Colon";}
        if(temp_L == "+"){temp_L = "Add";}
        if(temp_L == "-"){temp_L = "Sub";}
        if(temp_L == "*"){temp_L = "Mul";}
        if(temp_L == "/"){temp_L = "Div";}
        if(temp_L == "%"){temp_L = "Mod";}
        if(temp_L == "^"){temp_L = "Pow";}
        temp_L = temp_L + "_" + std::to_string(i);
        out << "\n" << temp_M << " -> " << temp_L << ";";
        generateTree(out, n->getLeft(), i);
     }

     if (n->getRight() != 0)
     {
        i++;
        std::string temp_R = (n->getRight())->getKey()->stringify();
        if(temp_R == ":"){temp_R = "Colon";}
        if(temp_R == "+"){temp_R = "Add";}
        if(temp_R == "-"){temp_R = "Sub";}
        if(temp_R == "*"){temp_R = "Mul";}
        if(temp_R == "/"){temp_R = "Div";}
        if(temp_R == "%"){temp_R = "Mod";}
        if(temp_R == "^"){temp_R = "Pow";}
        temp_R = temp_R + "_" + std::to_string(i);
        out << "\n" << temp_M << " -> " << temp_R << ";";
        generateTree(out, n->getRight(), i);
     }
 }
//--------------------------------------------------------------

 void Pattern::visualizeTree(const std::string& outputFilename)
 {
    std::ofstream outFS;
    outFS.open(outputFilename.c_str());
    if(!outFS.is_open())
    {
        std::cout << "Error opening " << outputFilename << std::endl;
        throw std::runtime_error("visualizeTree() : missing file");
    }

    outFS << "digraph G {";
    generateTree(outFS,root);
    outFS << std::endl << "}";
    outFS.close();
    std::string jpgFilename = outputFilename.substr(0,outputFilename.size()-4) + ".jpg";
    std::string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
//--------------------------------------------------------------
