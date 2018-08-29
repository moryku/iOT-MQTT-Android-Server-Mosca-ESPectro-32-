var mosca = require('mosca');
var settings = {
		port:1883
		}

var server = new mosca.Server(settings);	//here we start mosca
// server.on('ready', setup);	//on init it fires up setup()
// server.on('chat', chat);	//on init it fires up setup()

// fired when the mqtt server is ready
server.on('clientConnected', function(client) {
    console.log('client connected', client);
  });

  server.on('clientDisconnected', function(client) {
    console.log('client disconnected', client.id);
  });

  server.on('published', function(packet, client) {
    console.log(packet);
    console.log(packet.topic);
    if ((typeof packet.payload) != "string") {
        console.log((packet.payload).toString('utf8'));
    }
  });

  server.on('subscribed', function(topic, client) {
    console.log('subscribed: ' + client.id);
  });

  server.on('unsubscribed', function(topic, client) {
    console.log('unsubscribed: ' + client.id);    
  });

  server.on('ready', function() {
    console.log('Mosca server is up and running');
  });
          