package id.ezyindustries.smkkodingmqtt;

import android.app.Application;

import org.eclipse.paho.android.service.MqttAndroidClient;

public class MqttApplication extends Application {

    public static MqttAndroidClient mqttAndroidClient;

    public static MqttAndroidClient getMqttAndroidClient() {
        return mqttAndroidClient;
    }

    public static void setMqttAndroidClient(MqttAndroidClient mqttAndroidClient) {
        MqttApplication.mqttAndroidClient = mqttAndroidClient;
    }
}
