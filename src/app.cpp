#include "app.h"

App::App(const std::string& name_, const std::string version_) 
:
name{name_}, version{version_} {
}

std::string App::get_name() const {
    return name;
}

std::string App::get_version() const {
    return version;
}

std::string App::get_qualified_name() const {
    return name + " " + version;
}