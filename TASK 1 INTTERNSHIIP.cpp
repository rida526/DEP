#include <iostream>
#include <string>
#include <map>
#include <vector>

// Location class definition
class Location {
private:
    std::string name;
    double latitude;
    double longitude;

public:
    Location(const std::string& name, double lat, double lon)
        : name(name), latitude(lat), longitude(lon) {}

    std::string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    void setName(const std::string& name) { this->name = name; }
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }
};

// WeatherVariable class definition
class WeatherVariable {
private:
    std::map<std::string, double> variables;

public:
    void addVariable(const std::string& name, double value) {
        variables[name] = value;
    }

    void removeVariable(const std::string& name) {
        variables.erase(name);
    }

    double getVariable(const std::string& name) const {
        auto it = variables.find(name);
        return (it != variables.end()) ? it->second : 0.0;
    }

    void listVariables() const {
        for (const auto& pair : variables) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

// WeatherForecastingSystem class definition
class WeatherForecastingSystem {
public:
    void fetchWeatherData(const Location& location) {
        // Simulate fetching weather data
        std::cout << "Fetching weather data for " << location.getName() << std::endl;
    }

    void displayWeatherData() const {
        // Simulate displaying weather data
        std::cout << "Displaying weather data" << std::endl;
    }
};

// HistoricalWeatherSystem class definition
class HistoricalWeatherSystem {
public:
    void fetchHistoricalData(const Location& location) {
        // Simulate fetching historical weather data
        std::cout << "Fetching historical weather data for " << location.getName() << std::endl;
    }

    void displayHistoricalData() const {
        // Simulate displaying historical weather data
        std::cout << "Displaying historical weather data" << std::endl;
    }
};

// AirQualityForecastingSystem class definition
class AirQualityForecastingSystem {
public:
    void fetchAirQualityData(const Location& location) {
        // Simulate fetching air quality data
        std::cout << "Fetching air quality data for " << location.getName() << std::endl;
    }

    void displayAirQualityData() const {
        // Simulate displaying air quality data
        std::cout << "Displaying air quality data" << std::endl;
    }
};

// Main function to demonstrate functionality
int main() {
    // Create a location
    Location loc("Paris", 48.8566, 2.3522);

    // Create weather variable manager
    WeatherVariable weatherVar;
    weatherVar.addVariable("Temperature", 20.0);
    weatherVar.addVariable("Wind Speed", 5.5);
    weatherVar.listVariables();

    // Create and use weather forecasting system
    WeatherForecastingSystem weatherSys;
    weatherSys.fetchWeatherData(loc);
    weatherSys.displayWeatherData();

    // Create and use historical weather system
    HistoricalWeatherSystem histWeatherSys;
    histWeatherSys.fetchHistoricalData(loc);
    histWeatherSys.displayHistoricalData();

    // Create and use air quality forecasting system
    AirQualityForecastingSystem airQualitySys;
    airQualitySys.fetchAirQualityData(loc);
    airQualitySys.displayAirQualityData();

    return 0;
}
