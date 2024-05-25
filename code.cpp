#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;

class LogEntry {
public:
    long long timestamp;
    string log_type;
    float severity;

    LogEntry(long long timestamp, string log_type, float severity)
        : timestamp(timestamp), log_type(log_type), severity(severity) {}
};

class ErrorLogMonitoring {
private:
    vector<LogEntry> logs;
    unordered_map<string, vector<LogEntry>> log_type_map;

public:
    void addLogEntry(const string& entry) {
        stringstream ss(entry);
        string timestamp_str, log_type, severity_str;
        getline(ss, timestamp_str, ';');
        getline(ss, log_type, ';');
        getline(ss, severity_str, ';');

        LogEntry log_entry(stoll(timestamp_str), log_type, stof(severity_str));
        logs.push_back(log_entry);
        log_type_map[log_type].push_back(log_entry);
    }

    void MinMaxMean(const vector<LogEntry>& log_entries, ofstream& outputFile) {
        if (log_entries.empty()) {
            outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
            return;
        }

        float min_severity = numeric_limits<float>::max();
        float max_severity = numeric_limits<float>::min();
        float sum_severity = 0;

        for (const auto& entry : log_entries) {
            min_severity = min(min_severity, entry.severity);
            max_severity = max(max_severity, entry.severity);
            sum_severity += entry.severity;
        }

        float mean_severity = sum_severity / log_entries.size();
        outputFile << "Min: " << min_severity << ", Max: " << max_severity << ", Mean: " << mean_severity << "\n";
    }

    void LogType(const string& log_type, ofstream& outputFile) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            MinMaxMean(log_type_map[log_type], outputFile);
        } else {
            outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }

    void TimestampBefore(long long timestamp, ofstream& outputFile) {
        vector<LogEntry> result;
        for (const auto& entry : logs) {
            if (entry.timestamp < timestamp) {
                result.push_back(entry);
            }
        }
        MinMaxMean(result, outputFile);
    }

    void TimestampAfter(long long timestamp, ofstream& outputFile) {
        vector<LogEntry> result;
        for (const auto& entry : logs) {
            if (entry.timestamp > timestamp) {
                result.push_back(entry);
            }
        }
        MinMaxMean(result, outputFile);
    }

    void LogTypeTimestampBefore(const string& log_type, long long timestamp, ofstream& outputFile) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            vector<LogEntry> result;
            for (const auto& entry : log_type_map[log_type]) {
                if (entry.timestamp < timestamp) {
                    result.push_back(entry);
                }
            }
            MinMaxMean(result, outputFile);
        } else {
            outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }

    void LogTypeTimestampAfter(const string& log_type, long long timestamp, ofstream& outputFile) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            vector<LogEntry> result;
            for (const auto& entry : log_type_map[log_type]) {
                if (entry.timestamp > timestamp) {
                    result.push_back(entry);
                }
            }
            MinMaxMean(result, outputFile);
        } else {
            outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }
};

int main() {
    ErrorLogMonitoring errorLogMonitor;

    ifstream inputFile("inputf.in");
    ofstream outputFile("outputf.in");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files!\n";
        return 1;
    }

    vector<string> inputs;
    string line;

    while (getline(inputFile, line) && !line.empty()) {
        inputs.push_back(line);
    }

    for (const auto& input : inputs) {
        stringstream ss(input);
        int command;
        ss >> command;

        if (command == 1) {
            string log_entry;
            ss.ignore(); 
            getline(ss, log_entry);
            errorLogMonitor.addLogEntry(log_entry);
        } else if (command == 2) {
            string log_type;
            ss >> log_type;
            errorLogMonitor.LogType(log_type, outputFile);
        } else if (command == 3) {
            string condition;
            long long timestamp;
            ss >> condition >> timestamp;
            if (condition == "BEFORE") {
                errorLogMonitor.TimestampBefore(timestamp, outputFile);
            } else if (condition == "AFTER") {
                errorLogMonitor.TimestampAfter(timestamp, outputFile);
            }
        } else if (command == 4) {
            string condition, log_type;
            long long timestamp;
            ss >> condition >> log_type >> timestamp;
            if (condition == "BEFORE") {
                errorLogMonitor.LogTypeTimestampBefore(log_type, timestamp, outputFile);
            } else if (condition == "AFTER") {
                errorLogMonitor.LogTypeTimestampAfter(log_type, timestamp, outputFile);
            }
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
