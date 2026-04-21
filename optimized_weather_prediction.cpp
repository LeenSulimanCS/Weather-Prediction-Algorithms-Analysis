//optimize

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> // For rand()

using namespace std;

// Determines weather condition based on humidity and wind speed
string WeatherCondition(double humidity, double windSpeed) {
    if (humidity > 80) return "Rainy";
    else if (windSpeed > 30) return "Windy";
    else if (humidity > 60) return "Cloudy";
    else return "Sunny";
}

// Gets the index of the current day from the days array
int getStart(const string& currentDay, const string daysOfWeek[7]) {
    string input = currentDay;
    for (char& c : input) c = tolower(c);

    for (int i = 0; i < 7; ++i) {
        string check = daysOfWeek[i];
        for (char& c : check) c = tolower(c);
        if (input == check) return i;
    }

    return -1;
}

int main() {
    // Initial weather input values
    double Temperature, Humidity, WindSpeed;
    string currentDay;
    int predictionDays;

    string daysOfWeek[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    cout << "Enter current day: ";
    cin >> currentDay;

    cout << "Enter current temperature (°C): ";
    cin >> Temperature;

    cout << "Enter current humidity (%): ";
    cin >> Humidity;

    cout << "Enter current wind speed (km/h): ";
    cin >> WindSpeed;

    cout << "Enter number of prediction days: ";
    cin >> predictionDays;

    // Get index of current day
    int startDay = getStart(currentDay, daysOfWeek);
    if (startDay == -1) {
        cout << "Invalid day entered!\n";
        return 1;
    }

    cout << "\n\nWeather Prediction for " << daysOfWeek[startDay] << ":\n\n";
    cout << left << setw(12) << "Day"
         << setw(12) << "Temp(°C)"
         << setw(15) << "Humidity(%)"
         << setw(15) << "Wind(km/h)"
         << "Condition" << endl;
    cout << string(60, '-') << endl;
    cout << fixed << setprecision(1);

    // Print weather data for first day
    cout << left << setw(12) << daysOfWeek[startDay]
     << setw(12) << Temperature
     << setw(15) << Humidity
     << setw(15) << WindSpeed
     << WeatherCondition(Humidity, WindSpeed) << endl;

    for (int k = 1; k < predictionDays; ++k) {
        int dayIndex = (startDay + k) % 7;

        double temp = Temperature;
        double hum = Humidity;
        double wind = WindSpeed;

        // Apply random changes
        temp += (rand() % 6) / 2.0 * (rand() % 2 == 0 ? 1 : -1);   // Random change between -2.5 and +2.5
        hum += (rand() % 11) * (rand() % 2 == 0 ? 1 : -1);         // Random change between -10 and +10
        wind += (rand() % 7) * (rand() % 2 == 0 ? 1 : -1);          // Random change between -6 and +6

        // Ensure humidity stays between 0 and 100
        if (hum < 0) hum = 0;
        if (hum > 100) hum = 100;

        // Ensure wind speed stays between 0 and 60
        if (wind < 0) wind = 0;
        if (wind > 60) wind = 60;

        string condition = WeatherCondition(hum, wind);

        // Print weather data
        cout << left << setw(12) << daysOfWeek[dayIndex]
             << setw(12) << temp
             << setw(15) << hum
             << setw(15) << wind
             << condition << endl;
    }

    return 0;
}
