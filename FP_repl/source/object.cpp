#include "../header/object.h"



Element::Element(int i)
    : Object(),  val(i)
{}


Sequence::Sequence(std::list<int> l)
    : Object(),  seq(l)
{}


Function::Function(std::string s)
    : Object(),  func(s)
{}

Colon::Colon(std::string s)
    : Object(),  col(s)
{}

Block::Block(std::string s)
    : Object(),  block(s)
{}