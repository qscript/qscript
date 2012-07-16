/*
 * =====================================================================================
 *
 *       Filename:  rest_get_hello.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 16 July 2012 10:21:21  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>

using namespace Wt;

class RestGetHello : public Wt::WResource
{
   public:
       virtual ~RestGetHello(){
			beingDeleted();
	}

   protected:
       virtual void handleRequest(const Wt::Http::Request &request,
Wt::Http::Response &response)
       {
           response.out() << "Hello World!\n";
       }
};

int main(int argc, char **argv)
{
   try {
       WServer server(argv[0]);

       server.setServerConfiguration(argc, argv);

       RestGetHello getHello;

       server.addResource(&getHello, "/hello");

       if (server.start()) {
           WServer::waitForShutdown();
           server.stop();
       }
   } catch (WServer::Exception& e) {
       std::cerr << e.what() << std::endl;
   } catch (std::exception &e) {
       std::cerr << "exception: " << e.what() << std::endl;
   }
}
