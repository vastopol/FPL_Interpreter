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

 void Pattern::generateTree(std::ofstream& out, Node* n, int i=1) // might 
 {
     if (n == 0)
     {
         return;
     }

     std::string temp_M = n->getKey()->stringify(); 
     if(temp_M == ":"){temp_M = "Colon";}
     temp_M = temp_M + "_" + std::to_string(i);

     out << '\n'; out << temp_M << " [label=\"" << temp_M; out << "\"];";
     // i++;

     if (n->getLeft() != 0)
     {
        i++;
        std::string temp_L = (n->getLeft())->getKey()->stringify();
        if(temp_L == ":"){temp_L = "Colon";}
        temp_L = temp_L + "_" + std::to_string(i);
        out << "\n" << temp_M << " -> " << temp_L << ";";
        generateTree(out, n->getLeft(), i);
     }
     if (n->getRight() != 0)
     {
        i++;
        std::string temp_R = (n->getRight())->getKey()->stringify();
        if(temp_R == ":"){temp_R = "Colon";}
        temp_R = temp_R + "_" + std::to_string(i);
        out << "\n" << temp_M << " -> " << temp_R << ";";
        generateTree(out, n->getRight(), i);
     }
 }
//--------------------------------------------------

void Pattern::generateTree2(std::ofstream& out, Node* n) // iterative, BROKEN // (geeks for geeks)
{   
    if (n == 0)
    {
        return;
    }

    std::string temp_M;
    std::string temp_L;
    std::string temp_R;
    Node* prev = 0;
    std::stack<Node*> s;
    s.push(n);

    while(!s.empty())
    {
        Node* current = s.top();

        /* go down the tree in search of a leaf an if so process it 
        and pop stack otherwise move down */
        if (prev == 0 || prev->getLeft() == current || prev->getRight() == current) 
        {
            if (current->getLeft() != 0)
            {
                s.push(current->getLeft());
            }
            else if (current->getRight() != 0)
            {
                s.push(current->getRight());
            }
            else
            {
                temp_M = (s.top())->getKey()->stringify();
                if(temp_M == ":"){temp_M = "Colon";}
                out << '\n'; out << temp_M << " [label=\"" << temp_M; out << "\"];";
                s.pop();
            }

            /* go up the tree from left node, if the child is right 
               push it onto stack otherwise process parent and pop 
               stack */
        } 
        else if (current->getLeft() == prev) 
        {
            if (current->getRight() != 0)
            {
                s.push(current->getRight());
            }
            else
            {
                temp_L = (s.top())->getKey()->stringify();
                if(temp_L == ":"){temp_L = "Colon";}
                out << '\n'; out << temp_L << " [label=\"" << temp_L; out << "\"];";
                out << "\n" << temp_M << " -> " << temp_L << ";";
                s.pop();
            }
              
            /* go up the tree from right node and after coming back
             from right node process parent and pop stack */
        } 
        else if (current->getRight() == prev) 
        {
            temp_R = (s.top())->getKey()->stringify();
            if(temp_R == ":"){temp_R = "Colon";}
            out << '\n'; out << temp_R << " [label=\"" << temp_R; out << "\"];";
            out << "\n" << temp_M << " -> " << temp_R << ";";
            s.pop();
        }

        prev = current;
    }
}
//--------------------------------------------------


 void Pattern::visualizeTree(const std::string& outputFilename)
 {
    std::ofstream outFS;
    outFS.open(outputFilename.c_str());
    if(!outFS.is_open())
    {
        std::cout << "Error opening " << outputFilename << std::endl;
        return;
    }
    outFS << "digraph G {";
    generateTree(outFS,root);
    outFS << std::endl << "}";
    outFS.close();
    std::string jpgFilename = outputFilename.substr(0,outputFilename.size()-4) + ".jpg";
    std::string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
