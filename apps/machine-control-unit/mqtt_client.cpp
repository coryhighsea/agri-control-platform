#include "mqtt_client.h"
#include <iostream>
#include <cstring>

MQTTClient::MQTTClient(const std::string& host, int port, const std::string& clientId)
    : m_host(host), m_port(port), m_clientId(clientId), m_mosq(nullptr) {
    mosquitto_lib_init();
    m_mosq = mosquitto_new(m_clientId.c_str(), true, this);
    if (!m_mosq) {
        std::cerr << "Error: Out of memory." << std::endl;
    }

    mosquitto_connect_callback_set(m_mosq, on_connect_callback);
    mosquitto_message_callback_set(m_mosq, on_message_callback);
}

MQTTClient::~MQTTClient() {
    if (m_networkThread.joinable()) {
        mosquitto_disconnect(m_mosq);
        mosquitto_loop_stop(m_mosq, true);
        m_networkThread.join();
    }
    mosquitto_destroy(m_mosq);
    mosquitto_lib_cleanup();
}

bool MQTTClient::connect() {
    int rc = mosquitto_connect(m_mosq, m_host.c_str(), m_port, 60);
    if (rc != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: " << mosquitto_strerror(rc) << std::endl;
        return false;
    }

    m_networkThread = std::thread(&MQTTClient::network_thread_main, this);
    return true;
}

void MQTTClient::network_thread_main() {
    std::cout << "[MQTT] Network thread started." << std::endl;
    mosquitto_loop_forever(m_mosq, -1, 1);
    std::cout << "[MQTT] Network thread finished." << std::endl;
}

void MQTTClient::subscribe(const std::string& topic) {
    int rc = mosquitto_subscribe(m_mosq, NULL, topic.c_str(), 1);
    if (rc != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error subscribing: " << mosquitto_strerror(rc) << std::endl;
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& message) {
    int rc = mosquitto_publish(m_mosq, NULL, topic.c_str(), message.length(), message.c_str(), 1, false);
    if (rc != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error publishing: " << mosquitto_strerror(rc) << std::endl;
    }
}

std::string MQTTClient::getNextCommand() {
    std::lock_guard<std::mutex> lock(m_queueMutex);
    if (m_commandQueue.empty()) {
        return "";
    }
    std::string command = m_commandQueue.front();
    m_commandQueue.pop();
    return command;
}

void MQTTClient::on_connect_callback(struct mosquitto *mosq, void *userdata, int result) {
    if (result == 0) {
        std::cout << "[MQTT] Connected to broker." << std::endl;
    } else {
        std::cerr << "[MQTT] Connect failed." << std::endl;
    }
}

void MQTTClient::on_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    MQTTClient* client = static_cast<MQTTClient*>(userdata);
    if (message->payloadlen) {
        std::string payload(static_cast<char*>(message->payload), message->payloadlen);
        std::cout << "[MQTT] Received message on topic '" << message->topic << "': " << payload << std::endl;
        
        std::lock_guard<std::mutex> lock(client->m_queueMutex);
        client->m_commandQueue.push(payload);
    }
}