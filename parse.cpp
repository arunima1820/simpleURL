#include "parse.h"
#include<string>


parse::parse(string const &u) {
    url = u;
    if (assign()) {
        print();
    } else {
        cout << "Erroreous URL: \tContains Invalid syntax.\n";
    }
}

bool parse::assign() {    
    //index till the end of protocol
    int index = url.find("://");

    if (index < url.length()) {
        protocol = url.substr(0, index);
        domain = url.substr(url.find("://")+3);
       
        // if no port
        if (url.find_first_of(':') == url.find_last_of(':')) {
            domain = domain.substr(0, domain.find_first_of('/'));
        } else { // if yes port
            index = domain.find(':')+1;
            while (domain.at(index) != '/') {
                port += domain.at(index);
                index++;
            }
            domain = domain.substr(0, domain.find_first_of(":"));
        }
        filePath = url.substr(url.find("://")+3);
        index = url.find('?');
        if(index < url.length()) {
            param = url.substr(url.find('?')+1);
            
            // FIXME help
            filePath = filePath.erase(filePath.find('?'), filePath.length());
            filePath = filePath.substr(filePath.find_first_of('/'));

        } else {
            filePath = filePath.substr(filePath.find_first_of('/'));
        }

        return true; // if everything is ok

    } else {
        // if syntax error
        return false;
    }
}

    bool parse::checkURL(int val) {
        switch(val) {
            case 1: {  // PROTOCOL
                if (protocol == "http" || protocol == "https" || protocol == "ftp" || protocol == "ftps") {
                    return true;
                }
                else {
                    return false;
                }
            break;
            }
            case 2: { // DOMAIN
                string host = domain.substr(domain.find_last_of('.')+1); //com, edu, etc
                if (host == "com" || host == "net" || host == "gov" || host == "edu" || host == "biz") { 
                        return true;
                } else {
                    return false;
                }
            break;
            }
            case 3: { // PORT
                if (port.empty()) return true;

                int portNo = std::stoi(port);
                if (portNo > 65535 || portNo < 1) {
                    return false;
                }
                else
                    return true;
            break;    
            }

            case 4: {// FILEPATH
                string ext = filePath.substr(filePath.find_last_of('.')+1);
                if (ext == "htm" || ext == "html") {
                    return true;
                } else {
                    return false;
                }
            break;
            }

            case 5: { // PARAMETERS
                if (param.empty()) return true;
            break;
            }
        }

        return false;
    }

void parse::print() {
    int index = 1;
    bool no_error = true;
    while (index < 5) {
        if (!checkURL(index)) {
            no_error = false;
            break;
        }
        index++;
    }

    if (no_error) {
        cout << endl;
        if (!protocol.empty())
            cout << "Protocol: \t" + protocol << endl;

        if(!domain.empty())
            cout << "Domain: \t"+domain << endl;

        if(!port.empty())
            cout << "Port:   \t"+port << endl;
        
        if(!filePath.empty())
            cout << "File path: \t"+filePath << endl;
        
        if(!param.empty())
            cout << "Parameters: \t"+param << endl;
    } else {
        cout << "\nInvalid URL with the following erroneous components:\n";
        index = 1;
        while (index <= 5) {
            if (!checkURL(index)) {
                printErrors(index);
            }
            index++;
        }
    }
}

void parse::printErrors(int i) {
    if (checkURL(i)) {
        return;
    }

    switch (i) {
        case 1: 
            cout << "Protocol: \t"+protocol+" is an invalid protocol.\n";
        break;
        case 2: 
            cout << "Domain: \t"+domain+" is an invalid domain.\n";
        break;
        case 3: 
            cout << "Port:    \t"+port+" must be between 1 and 65535.\n";
        break;
        case 4: 
            cout << "File Path: \t"+filePath+" must end with htm or html\n";
        break;
    }
}