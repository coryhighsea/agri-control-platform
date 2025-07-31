#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <mosquitto.h>

class MQTTClient {
public:
    MQTTClient(const std::string& host, int port, const std::string& clientId);
    ~MQTTClient();

    bool connect();
    void subscribe(const std::string& topic);
    void publish(const std::string& topic, const std::string& message);
    std::string getNextCommand();

private:
    static void on_connect_callback(struct mosquitto *mosq, void *userdata, int result);
    static void on_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);

    void network_thread_main();

    struct mosquitto *m_mosq;
    std::string m_host;
    int m_port;
    std::string m_clientId;

    std::queue<std::string> m_commandQueue;
    std::mutex m_queueMutex;
    std::thread m_networkThread;
};

#endif // MQTT_CLIENT_H