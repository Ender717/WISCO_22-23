#include "menu/MenuData.hpp"
#include "Menu.hpp"
#include <fstream>

// Constant definitions -------------------------------------------------------
const std::string MenuData::DATA_FILE = "/usd/menudata.txt";

// Static member defaults -----------------------------------------------------
bool MenuData::initialized = false;
Menu::Autons MenuData::auton = Menu::Autons::BLUE_LEFT;
Menu::Configurations MenuData::configuration = Menu::Configurations::TEST;
Menu::Profiles MenuData::profile = Menu::Profiles::NATHAN;

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

void MenuData::readData()
{
    std::ifstream data;
    data.open(DATA_FILE);
    if (data.is_open())
    {
        data >> initialized;
        std::string input;

        data >> input;
        for (int i = 0; i < Menu::NUM_PROFILES; i++)
        {
            if (input == Menu::profileStr[i])
            {
                profile = static_cast<Menu::Profiles>(i);
                break;
            }
        }

        data >> input;
        for (int i = 0; i < Menu::NUM_CONFIGURATIONS; i++)
        {
            if (input == Menu::configurationStr[i])
            {
                configuration = static_cast<Menu::Configurations>(i);
                break;
            }
        }

        data >> input;
        for (int i = 0; i < Menu::NUM_AUTONS; i++)
        {
            if (input == Menu::autonStr[i])
            {
                auton = static_cast<Menu::Autons>(i);
                break;
            }
        }
    }
    data.close();
}

void MenuData::writeData()
{
    std::ofstream data;
    data.open(DATA_FILE, std::ofstream::out | std::ofstream::trunc);
    if (data.is_open())
    {
        data << initialized << std::endl;
        data << Menu::profileStr[static_cast<int>(profile)] << std::endl;
        data << Menu::configurationStr[static_cast<int>(configuration)] << std::endl;
        data << Menu::autonStr[static_cast<int>(auton)];
    }
    data.close();
}