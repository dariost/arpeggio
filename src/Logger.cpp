#include "Logger.hpp"

void Logger::print(Level level, const string& message)
{
    string msg;
    if(level == DEBUG)
        msg = "[DEBUG] " + message;
    else if(level == INFO)
        msg = "[INFO] " + message;
    else if(level == WARNING)
        msg = "[WARNING] " + message;
    else if(level == ERROR)
        msg = "[ERROR] " + message;
    else if(level == CRITICAL)
        msg = "[CRITICAL] " + message;

    cout << msg << endl;
}

Logger::Logger(Level min_verbosity)
{
    verbosity_level = min_verbosity;
#ifdef _WIN32
    is_tty = _isatty(_fileno(stdout));
#else
    is_tty = isatty(fileno(stdout));
#endif
}
