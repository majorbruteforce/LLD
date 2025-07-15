#include <bits/stdc++.h>
using namespace std;

enum eventType {
    USER_REQUEST,
    RIDE_ARRIVED,
    RIDE_ACCEPTED,
    RIDERS_UNAVAILABLE,
    RIDE_COMPLETED
}

enum rideStatus {
    ONGOING,
    PENDING
};

class User {
public:
    User(const string& name,
         const string& phone,
         const string& email,
         const string& id) : name(name), phone(phone), email(email), id(id) {};

    vector<Channel*> channels;
    string name;
    string phone;
    string email;
    string id;

    void addChannel(Channel& c);
};

class IProducer {
public:
    vector<User*> listeners;
    virtual void add(User& u) = 0;
    virtual void remove(User& u) = 0;
    virtual void send(Event& e) = 0;
    virtual ~IProducer = default;
};

class IObserver {
public:
    virtual void update(Event& e) = 0;
    virtual ~IObserver() = default;
};

class Consumer: public User, public IProducer, public IObserver {
public:
    Consumer(const string& name,
         const string& phone,
         const string& email,
         const string& id) : User(name, phone, email, id) {}

    void addChannel(Channel& c) {
        channels.push_back(c);
    }

    void add(User& u) override {
        listeners.push_back(u);
    }

    void remove(User& u) override {
        for(int i = 0; i < listeners.size(); i++){
            if(u == l){
                listeners.erase(listeners.begin() + i);
                return;
            }
        }
    }

    void send(Event& e) override {
        for(auto l: listeners) {
            l->update(e);
        }
    }

    void update(Event& e) override {
        for(auto c: channels) {
            c->display(e);
        }
    }
};

class Rider: public User, public IProducer, public IObserver {
public:
    Rider(const string& name,
         const string& phone,
         const string& email,
         const string& id) : User(name, phone, email, id) {}

    void addChannel(Channel& c) {
        channels.push_back(c);
    }

    void add(User& u) override {
        listeners.push_back(u);
    }

    void remove(User& u) override {
        for(int i = 0; i < listeners.size(); i++){
            if(u == l){
                listeners.erase(listeners.begin() + i);
                return;
            }
        }
    }

    void send(Event& e) override {
        for(auto l: listeners) {
            l->update(e);
        }
    }

    void update(Event& e) override {
        for(auto c: channels) {
            c->display(e);
        }
    }
};

class Event {
public:
    string id;
    eventType type;
    string message;
    Ride* ride;
}

class RideAcceptedEvent: public Event {
// ...
}

class Ride {
public:
    rideType type;
}

class Channel {
public:
    virtual void display(Event& e) = 0;
    virtual ~Channel() = default;
}

class WhatsApp: public Channel {
public:
    void display(Event& e) override {
        cout << "WhatsApp: "
             << e->name << " "
             << e->message<< " "
             << endl;
     }
}

class SMS: public Channel {
public:
    void display(Event& e) override {
        cout << "SMS: "
             << e->name << " "
             << e->message<< " "
             << endl;
     }
}

class Email: public Channel {
public:
    void display(Event& e) override {
        cout << "Email: "
             << e->name << " "
             << e->message<< " "
             << endl;
     }
}

class NotificationManager {
public:
    static vector<Consumer*> consumers;
    static vector<Rider*> riders;
    static unordered_map<Users*, Ride> ongoing;
    static eventIdCounter = 0;
    static userIdCounter = 0;


    static void registerConsumer(Consumer& c) {
        consumers.push_back(c);
    }

    static void removeConsumer(Consumer& c){
        auto it = find(consumers.begin(), consumers.end(), c);
        if(it != consumers.end()){
            consumers.erase(it);
        }
    }

    static void registerRider(Rider& r) {
        consumers.push_back(r);
    }

    static void removeRider(Rider& r){
        auto it = find(riders.begin(), riders.end(), r);
        if(it != riders.end()){
            riders.erase(it);
        }
    }

    static void startRide(Consumer& c, Rider& r, Ride& rd){
        removeRider(r);
        ongoing[r] = rd;
        ongoign[c] = rd;
    }

    static void endRide(Consumer& c, Rider& r, Ride& rd){
        ongoing.erase(c);
        ongoing.erase(r);
        addRider(r);
    }

    static void createRequest(Consumer& c){
        Ride* rd = new Ride(rideType::PENDING);
        if(riders.empty()){
            unique_ptr<Event> noti = make_unique<Event>(Event(++eventIdCounter, eventType::RIDER_UNAVAILABLE, "", rd));
            c->upadate(noti);
        } else {
            rd->status = rideStatus::ONGOING;
            startRide(c, riders.front(), rd);
            unique_ptr<Event> noti = make_unique<Event>(Event(++eventIdCounter, eventType::RIDE_ACCEPTED, "", rd));
            c->update(noti);
        }
    }
}

int main(){
    return 0;
}