#include "Node.h"

Node::Node(int NodeID, std::string const & creationTimeStr,
           long long lifeTimeInMins)
    : NodeID(NodeID), lifeTimeInMins(lifeTimeInMins)
{
    std::tm tm = {};
    strptime(creationTimeStr.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    creationTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

bool Node::operator<(Node const &node) const
{
    return minutesLeft() < node.minutesLeft();
}

bool Node::operator>(Node const &node) const
{
    return !(*this < node);
}

long long Node::minutesLeft() const
{
    //auto timePointOfDeath = creationTime + std::chrono::minutes(lifeTimeInMins) - std::chrono::system_clock::now();

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(creationTime +
            std::chrono::minutes(lifeTimeInMins) - std::chrono::system_clock::now());

    return minutes.count();
}

bool Node::isAlive() const
{
    return minutesLeft() > 0;
}


#ifdef _WIN32

//Windows doesn`t contain strptime function, so we need to make it ourself
//I just have founded this code in the enthernet
//I haven`t tested this yet
//TODO:
//Try to compile it!

extern "C" char* Node::strptime(const char* s,
                          const char* f,
                          struct tm* tm) {
 //Isn't the C++ standard lib nice? std::get_time is defined such that its
 //format parameters are the exact same as strptime. Of course, we have to
 //create a string stream first, and imbue it with the current C locale, and
 //we also have to make sure we return the right things if it fails, or
 //if it succeeds, but this is still far simpler an implementation than any
 //of the versions in any of the C standard libraries.
  std::istringstream input(s);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(tm, f);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(s + input.tellg());
}
#endif
