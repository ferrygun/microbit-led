var PubNub = require('pubnub')

function publish() {
  
    const uuid = PubNub.generateUUID();

    pubnub = new PubNub({
        publishKey : 'pub-c-fed11a86-4aa6-44ec-897d-872c38a2a094',
        subscribeKey : 'sub-c-46e94e80-82e7-11ea-8dff-bafe0457d467',
        uuid: uuid
    })
      
    function publishSampleMessage() {
        console.log("Since we're publishing on subscribe connectEvent, we're sure we'll receive the following publish.");
        var publishConfig = {
            channel : "pubnub_onboarding_channel",
            message : {"sender": uuid, "content": "Hello From JavaScript SDK"}
        }
        pubnub.publish(publishConfig, function(status, response) {
            console.log(status, response);
        })
    }
      
    pubnub.addListener({
        status: function(statusEvent) {
            if (statusEvent.category === "PNConnectedCategory") {
                publishSampleMessage();
            }
        },
        message: function(msg) {
            console.log(msg.message.content);
        },
        presence: function(presenceEvent) {
            // handle presence
        }
    })      
    console.log("Subscribing..");
    pubnub.subscribe({
        channels: ['pubnub_onboarding_channel'] 
    });
};


publish()
