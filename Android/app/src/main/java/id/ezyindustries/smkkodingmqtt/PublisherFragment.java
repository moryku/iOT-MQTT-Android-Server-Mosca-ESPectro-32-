package id.ezyindustries.smkkodingmqtt;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.Toast;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

import static id.ezyindustries.smkkodingmqtt.MqttApplication.mqttAndroidClient;

public class PublisherFragment extends Fragment {


    @BindView(R.id.topic)
    EditText mTopic;
    @BindView(R.id.message)
    EditText mMessage;

    public PublisherFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_publisher, container, false);
        ButterKnife.bind(this, view);

        return view;
    }


    @OnClick(R.id.publish)
    public void publishMessage() {
        if (TextUtils.isEmpty(mMessage.getText()) || TextUtils.isEmpty(mTopic.getText())) {
            Toast.makeText(getActivity(), "Message or Topic still empty", Toast.LENGTH_LONG).show();
            return;
        }
        if (mqttAndroidClient.isConnected()) {
            Toast.makeText(getActivity(), "MQTT Android still not connected to server", Toast.LENGTH_LONG).show();
            return;
        }
        try {
            MqttMessage message = new MqttMessage();
            message.setPayload(mMessage.getText().toString().getBytes());
            mqttAndroidClient.publish(mTopic.getText().toString(), message);
            Toast.makeText(getActivity(), "Has been published", Toast.LENGTH_LONG).show();
        } catch (MqttException e) {
            System.err.println("Error Publishing: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
