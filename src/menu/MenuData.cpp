#include "menu/MenuData.hpp"

// Public method definitions --------------------------------------------------
void MenuData::setInitialized(bool _initialized)
{
    initialized = _initialized;
}

bool MenuData::isInitialized()
{
    return initialized;
}

void MenuData::setProfile(Menu::Profiles _profile)
{
    profile = _profile;
}

Menu::Profiles MenuData::getProfile()
{
    return profile;
}

void MenuData::setConfiguration(Menu::Configurations _configuration)
{
    configuration = _configuration;
}

Menu::Configurations MenuData::getConfiguration()
{
    return configuration;
}

void MenuData::setAuton(Menu::Autons _auton)
{
    auton = _auton;
}

Menu::Autons MenuData::getAuton()
{
    return auton;
}