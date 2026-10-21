#include <iostream>
#include <queue>
#include <string>

struct Customer {
    int callId;
    std::string customerName;
    std::string phoneNumber;
    std::string issueSummary;
};

class CallCenter {
private:
    std::queue<Customer> callQueue;
    int nextCallId;

public:
    CallCenter() : nextCallId(101) {}

    void incomingCall(const std::string& name, const std::string& phone, const std::string& issue) {
        Customer newCustomer = {nextCallId++, name, phone, issue};
        callQueue.push(newCustomer);
        std::cout << "[Call Center] Incoming call from " << name 
                  << " (" << phone << "). Assigned Call ID #" << newCustomer.callId 
                  << " and placed in the queue.\n";
    }

    void answerNextCall(const std::string& agentName) {
        if (callQueue.empty()) {
            std::cout << "[Call Center] No customers waiting in the queue. " << agentName << " is idle.\n";
            return;
        }

        Customer currentCustomer = callQueue.front();
        callQueue.pop();

        std::cout << "\n[Connected] " << agentName << " is now assisting Call ID #" 
                  << currentCustomer.callId << " (" << currentCustomer.customerName 
                  << ", Phone: " << currentCustomer.phoneNumber << ").\n"
                  << "Issue Description: " << currentCustomer.issueSummary << "\n\n";
    }

    void peekNextCall() const {
        if (callQueue.empty()) {
            std::cout << "[Call Center] The queue is currently empty. No callers waiting.\n";
            return;
        }

        const Customer& nextCustomer = callQueue.front();
        std::cout << "[Call Center] Next caller in line: Call ID #" << nextCustomer.callId 
                  << " | Name: " << nextCustomer.customerName 
                  << " | Issue: " << nextCustomer.issueSummary << "\n";
    }

    void displayQueue() const {
        if (callQueue.empty()) {
            std::cout << "[Call Center] The queue is currently empty.\n";
            return;
        }

        std::queue<Customer> tempQueue = callQueue;
        std::cout << "\n--- Current Call Queue (Waiting Customers) ---\n";
        int position = 1;
        while (!tempQueue.empty()) {
            Customer cust = tempQueue.front();
            std::cout << position << ". Call ID: " << cust.callId 
                      << " | Name: " << cust.customerName 
                      << " | Phone: " << cust.phoneNumber 
                      << " | Issue: " << cust.issueSummary << "\n";
            tempQueue.pop();
            position++;
        }
        std::cout << "----------------------------------------------\n";
    }

    bool isEmpty() const {
        return callQueue.empty();
    }
};

int main() {
    CallCenter center;

    center.incomingCall("Kwesi Brown", "0593673783", "Billing inquiry regarding last month's invoice.");
    center.incomingCall("Bob Fosu", "0202330484", "Technical support for router connection issue.");
    center.incomingCall("David Okoto", "0551414245", "Requesting account upgrade to premium plan.");

    center.displayQueue();
    center.peekNextCall();

    center.answerNextCall("Agent Ammisah");
    center.answerNextCall("Agent John");
    center.incomingCall("Diana Akoto", "0550909043", "Password reset assistance.");

    center.displayQueue();

    while (!center.isEmpty()) {
        center.answerNextCall("Agent Ammisah");
    }

    
    center.answerNextCall("Agent John");

    return 0;
}
