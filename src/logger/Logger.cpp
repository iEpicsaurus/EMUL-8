#include "Logger.h"
#include <string>
#include <chrono>

using namespace std;

const Logger* Logger::_instance = NULL; ///< Instance is originally NULL until it is instanced and instantiated

/**
 * Provides access to the global, internal instance of this Singleton
 * @return _instance A pointer to the Singleton instance
 */
const Logger& Logger::getInstance(){
    /// Lazy initialize
    if(_instance == NULL){ ///< Instance not created
        _instance = new Logger;
    }
    return *_instance; ///< Return pointer to instance
}

/**
 * Protects the constructor such that we can restrict the instances of the logger to only one
 */
Logger::Logger() {
    this->_output.open("debug.log");
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::time_t now = std::chrono::system_clock::to_time_t(time_point);
    this->_output << "Program run at " << std::ctime(&now);
}

/**
 * Destructs the file on delete and closes the file
 */
Logger::~Logger() {
    this->_output.close();
}

/**
 * Logs a given string to the debug.log file
 *
 * @param message The String to be logged to the file
 */
const Logger& Logger::log(const string& message) const{
    this->_output << message << endl;
    return *this;
}

/**
 * Overloads the << operator such that logs can be printed similar to cout (ex. cout << message << endl;)
 *
 * @param message The String to be logged to the file
 */
const Logger& Logger::operator<<(const string &message) const {
    return this->log(message);
}
