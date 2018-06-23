
var request = require("request")


// Route the incoming request based on type (LaunchRequest, IntentRequest,
// etc.) The JSON body of the request is provided in the event parameter.
exports.handler = function (event, context) {
    try {
        console.log("event.session.application.applicationId=" + event.session.application.applicationId);

        /**
         * Uncomment this if statement and populate with your skill's application ID to
         * prevent someone else from configuring a skill that sends requests to this function.
         */

    // if (event.session.application.applicationId !== "") {
    //     context.fail("Invalid Application ID");
    //  }

        if (event.session.new) {
            onSessionStarted({requestId: event.request.requestId}, event.session);
        }

        if (event.request.type === "LaunchRequest") {
            onLaunch(event.request,
                event.session,
                function callback(sessionAttributes, speechletResponse) {
                    context.succeed(buildResponse(sessionAttributes, speechletResponse));
                });
        } else if (event.request.type === "IntentRequest") {
            onIntent(event.request,
                event.session,
                function callback(sessionAttributes, speechletResponse) {
                    context.succeed(buildResponse(sessionAttributes, speechletResponse));
                });
        } else if (event.request.type === "SessionEndedRequest") {
            onSessionEnded(event.request, event.session);
            context.succeed();
        }
    } catch (e) {
        context.fail("Exception: " + e);
    }
};

/**
 * Called when the session starts.
 */
function onSessionStarted(sessionStartedRequest, session) {
    // add any session init logic here
}

/**
 * Called when the user invokes the skill without specifying what they want.
 */
function onLaunch(launchRequest, session, callback) {
    getWelcomeResponse(callback)
}

function helloIntent(intent, session, callback) {
    var cardTitle = 'Hello';
    var speechOutput = "Hello !";
    var repromptText = speechOutput;
    var shouldEndSession = true;
    callback({},
         buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}


function LightControl(intent, session, callback) {
    var cardTitle = 'Hello';
    var speechOutput = "Welcome to Smart home ";
    var repromptText = speechOutput;
    var colorSlot = intent.slots.color;
    var stateSlot = intent.slots.state;
    var shouldEndSession = true;
    
    //translate device name to relative controller's command name
    if(stateSlot.value == "on"){
        var comstr = "white";
    }
    else if(stateSlot.value == "off"){
        var comstr = "dark";
    }
    else{
        var comstr = colorSlot.value;
    }
        
    var url = "http://140.118.114.67/arcIOT.php?color=" + comstr;
    request.get(url, function(error, response, body) {
        callback({},
            buildSpeechletResponse(cardTitle, speechOutput, repromptText, true));
    });
}

function firstfloor(intent, session, callback) {
    var cardTitle = 'Hello';
    var speechOutput = "Welcome to Smart home ";
    var repromptText = speechOutput;
    var colorSlot = intent.slots.color;
    var stateSlot = intent.slots.state;
    var shouldEndSession = true;
    
    //translate device name to relative controller's command name
    if(stateSlot.value == "on"){
        var comstr = "white";
    }
    else if(stateSlot.value == "off"){
        var comstr = "dark";
    }
    else{
        var comstr = colorSlot.value;
    }
        
    var url = "http://140.118.114.67/embbed_1.php?color=" + comstr;
    request.get(url, function(error, response, body) {
        callback({},
            buildSpeechletResponse(cardTitle, speechOutput, repromptText, true));
    });
}

function secondfloor(intent, session, callback) {
    var cardTitle = 'Hello';
    var speechOutput = "Welcome to Smart home ";
    var repromptText = speechOutput;
    var colorSlot = intent.slots.color;
    var stateSlot = intent.slots.state;
    var shouldEndSession = true;
    
    //translate device name to relative controller's command name
    if(stateSlot.value == "on"){
        var comstr = "white";
    }
    else if(stateSlot.value == "off"){
        var comstr = "dark";
    }
    else{
        var comstr = colorSlot.value;
    }
        
    var url = "http://140.118.114.67/embbed_2.php?color=" + comstr;
    request.get(url, function(error, response, body) {
        callback({},
            buildSpeechletResponse(cardTitle, speechOutput, repromptText, true));
    });
}


function err(intent, session, callback) {
    var cardTitle = 'Hello';
    var speechOutput = "the sentence isn't be included in intent!";
    var repromptText = speechOutput;
    var shouldEndSession = true;
    callback({},
         buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));

}

/**
 * Called when the user specifies an intent for this skill.
 */
function onIntent(intentRequest, session, callback) {

    var intent = intentRequest.intent
    var intentName = intentRequest.intent.name;

    // dispatch custom intents to handlers here
    if (intentName === "helloIntent") {
        helloIntent(intent, session, callback);
    } 
    else if(intentName === "LightControl"){
        LightControl(intent, session, callback);
    }
    else if(intentName === "firstfloor"){
        firstfloor(intent, session, callback);
    }
    else if(intentName === "secondfloor"){
        secondfloor(intent, session, callback);
    }
    else {
         throw "Invalid intent"
    }
}

/**
 * Called when the user ends the session.
 * Is not called when the skill returns shouldEndSession=true.
 */
function onSessionEnded(sessionEndedRequest, session) {

}

// ------- Skill specific logic -------

function getWelcomeResponse(callback) {
    var speechOutput = "Welcome Alexa"

    var reprompt = "Welcome Alexa"

    var header = "Get Info"

    var shouldEndSession = false

    var sessionAttributes = {
        "speechOutput" : speechOutput,
        "repromptText" : reprompt
    }

    callback(sessionAttributes, buildSpeechletResponse(header, speechOutput, reprompt, shouldEndSession))

}


// ------- Helper functions to build responses for Alexa -------


function buildSpeechletResponse(title, output, repromptText, shouldEndSession) {
    return {
        outputSpeech: {
            type: "PlainText",
            text: output
        },
        card: {
            type: "Simple",
            title: title,
            content: output
        },
        reprompt: {
            outputSpeech: {
                type: "PlainText",
                text: repromptText
            }
        },
        shouldEndSession: shouldEndSession
    };
}

function buildSpeechletResponseWithoutCard(output, repromptText, shouldEndSession) {
    return {
        outputSpeech: {
            type: "PlainText",
            text: output
        },
        reprompt: {
            outputSpeech: {
                type: "PlainText",
                text: repromptText
            }
        },
        shouldEndSession: shouldEndSession
    };
}

function buildResponse(sessionAttributes, speechletResponse) {
    return {
        version: "1.0",
        sessionAttributes: sessionAttributes,
        response: speechletResponse
    };
}

function capitalizeFirst(s) {
    return s.charAt(0).toUpperCase() + s.slice(1)
}
