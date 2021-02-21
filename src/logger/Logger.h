#pragma once

#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Logs debug messages to a file
 *
 * Is a Singleton that manages a debug.log file where any messages can be printed and read to better
 * understand internal processes. Cannot be copied or assigned and can only be accessed through instancing.
 *
 * @author Sean Aspinall
 */
class Logger{
public:

    /// Default destructor
    virtual ~Logger();

    /// Receive the Logger instance and create it if it does not exist
    static const Logger& getInstance();

    /// Log a message to the output file
    const Logger& log(const std::string& message) const;

    /// Log a message to the output file using the << operator
    const Logger& operator<<(const std::string& message) const;

protected:

    /// Default constructor that can only be accessed onjects of the Logger type
    Logger();

private:
    /**
    * Prevent copying of the instance to restrict it to only 1 instance
    *
    * @param other The copied instance to avoid
    */
    Logger(const Logger& other){};

    /**
     * Prevent assignment of the Logger to another instance
     *
     * @param other
     */
    Logger& operator=(const Logger & other);

    /// Stores the output location which is a debugging file
    mutable std::ofstream _output;

    /// Holds the single instance that gets shared
    static const Logger* _instance;
};
