#include "EMailManager.h"

void EMailManager::Send(const std::string &to, const std::string &subject, const std::string &message)
{
    system(std::string("/home/alex/serverTEESTT/email.sh " + to + " \"" + subject + "\" \"" + message + "\"").c_str());
}
