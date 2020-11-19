#include <iostream>         // for the input/output
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#define GPIO_PATH "/sys/class/gpio/gpio46"
using namespace std;
using namespace cgicc;
#include "GPIO.h"
using namespace exploringBB;

int getGPIOstate(string filename)
{
   int state;
   fstream fs;
   string path(GPIO_PATH);
   fs.open((path + filename).c_str(), fstream::in);
   fs >> state;
   fs.close();
   return state;
}

int main()
{
   Cgicc form;                      // the CGI form object

   // get the state of the form that was submitted - script calls itself
   bool isStatus = form.queryCheckbox("status");
   char *value = getenv("REMOTE_ADDR");    // The remote IP address
    
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("CPE422 Reading a Pushbutton as Digital Input") << head() << endl;
   cout << body() << h1("CPE 422 Reading a Push Button as Digital Input") << endl;
   cout << h2("Reading a Pushbutton on gpio46 via a Web Browser") << endl;
   cout << "<form action=\"/cgi-bin/led.cgi\" method=\"POST\">\n";
   cout << "<input type=\"submit\" value=\"READ GPIO\" />";
   cout << h2("Pushbutton State") << endl;
   int GPIO_state = getGPIOstate("value");
   if(GPIO_state == 1)
   {
	cout << h2("Pressed") << endl;
   }
   else
   {
	cout << h2("Not Pressed") << endl;
   }

   cout << "</div></form>";
   cout << "<div> The CGI REMOTE_ADDR value is " << value << "</div>";
   cout << body() << html();
   return 0;
}
