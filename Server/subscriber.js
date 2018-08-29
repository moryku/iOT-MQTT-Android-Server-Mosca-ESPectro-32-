var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://192.168.43.213')
client.on('connect', function () {
    client.subscribe('myTopic')
    console.log("connect");
})
client.on('message', function (topic, message) {
context = message.toString();
console.log(context);
})