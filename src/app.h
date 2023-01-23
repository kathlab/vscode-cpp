#ifndef APP_H
#define APP_H

#include <string>

class App {
public:
    App() = default;
    App(const std::string& name, const std::string version);
    virtual ~App() = default;

    std::string get_name() const;
    std::string get_version() const;
    std::string get_qualified_name() const;

private:
    std::string name{};
    std::string version{};
};

#endif // APP_H