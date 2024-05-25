#include<bits/stdc++.h>
using namespace std;
class LogEntry {
public:
    long long timestamp;
    string log_type;
    float severity;

    LogEntry(long long timestamp, string& log_type, float severity)
    {
        this->timestamp=timestamp;
        this->log_type=log_type;
        this->severity=severity;
    }
};

class ErrorLogMonitoring {
private:
    vector<LogEntry> logs;
    unordered_map<string, vector<LogEntry>> log_type_map;

public:
    void addLogEntry(string& entry) {
        stringstream ss(entry);
        string timestamp_str, log_type, severity_str;
        getline(ss, timestamp_str, ';');
        getline(ss, log_type, ';');
        getline(ss, severity_str, ';');

        LogEntry log_entry(stoll(timestamp_str), log_type, stof(severity_str));
        logs.push_back(log_entry);
        log_type_map[log_type].push_back(log_entry);
        cout << "No output\n";
    }

    void MinMaxMean(vector<LogEntry>& log_entries) {
        if (log_entries.empty()) {
            cout << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
            return;
        }

        float min_severity = numeric_limits<float>::max();
        float max_severity = numeric_limits<float>::min();
        float sum_severity = 0;

        for (auto& entry : log_entries) {
            min_severity = min(min_severity, entry.severity);
            max_severity = max(max_severity, entry.severity);
            sum_severity += entry.severity;
        }

        float mean_severity = sum_severity / log_entries.size();
        cout << "Min: " << min_severity << ", Max: " << max_severity << ", Mean: " << mean_severity << "\n";
    }

    void LogType(string& log_type) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            MinMaxMean(log_type_map[log_type]);
        } else {
            cout << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }

    void TimestampBefore(long long timestamp) {
        vector<LogEntry> result;
        for (auto& entry : logs) {
            if (entry.timestamp < timestamp) {
                result.push_back(entry);
            }
        }
        MinMaxMean(result);
    }

    void TimestampAfter(long long timestamp) {
        vector<LogEntry> result;
        for (auto& entry : logs) {
            if (entry.timestamp > timestamp) {
                result.push_back(entry);
            }
        }
        MinMaxMean(result);
    }

    void LogTypeTimestampBefore(string& log_type, long long timestamp) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            vector<LogEntry> result;
            for (auto& entry : log_type_map[log_type]) {
                if (entry.timestamp < timestamp) {
                    result.push_back(entry);
                }
            }
            MinMaxMean(result);
        } else {
            cout << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }

    void LogTypeTimestampAfter(string& log_type, long long timestamp) {
        if (log_type_map.find(log_type) != log_type_map.end()) {
            vector<LogEntry> result;
            for (auto& entry : log_type_map[log_type]) {
                if (entry.timestamp > timestamp) {
                    result.push_back(entry);
                }
            }
            MinMaxMean(result);
        } else {
            cout << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        }
    }
};

int main() 
{
    ErrorLogMonitoring errorLogMonitor;

    ios_base::sync_with_stdio(false);                         
    cin.tie(NULL);                          
    #ifndef ONLINE_JUDGE                 
    freopen("inputf.in", "r", stdin);                                                
    freopen("outputf.in", "w", stdout);                    
    #endif   

    vector<string> inputs;
    string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        inputs.push_back(line);
    }

    for (auto& input : inputs) {
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
            errorLogMonitor.LogType(log_type);
        } else if (command == 3) {
            string condition;
            long long timestamp;
            ss >> condition >> timestamp;
            if (condition == "BEFORE") {
                errorLogMonitor.TimestampBefore(timestamp);
            } else if (condition == "AFTER") {
                errorLogMonitor.TimestampAfter(timestamp);
            }
        } else if (command == 4) {
            string condition, log_type;
            long long timestamp;
            ss >> condition >> log_type >> timestamp;
            if (condition == "BEFORE") {
                errorLogMonitor.LogTypeTimestampBefore(log_type, timestamp);
            } else if (condition == "AFTER") {
                errorLogMonitor.LogTypeTimestampAfter(log_type, timestamp);
            }
        }
    }

    return 0;
}
