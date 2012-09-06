#include "WCodeMirror.h"

#include <iostream>
#include <string>

#include <Wt/WApplication>

class MyWtCodeMirror : public Wt::WApplication
{
	public:
	MyWtCodeMirror (const Wt::WEnvironment& env);
	Wt::WCodeMirrorTextArea * cmta_;

};

MyWtCodeMirror::MyWtCodeMirror (const Wt::WEnvironment& env)
	: Wt::WApplication (env), cmta_(new Wt::WCodeMirrorTextArea(this->root()))
{ 
	std::cout << cmta_->getText() << std::endl;
}


Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new MyWtCodeMirror(env);
}


int main(int argc, char **argv)
{
  return Wt::WRun(argc, argv, &createApplication);
}


