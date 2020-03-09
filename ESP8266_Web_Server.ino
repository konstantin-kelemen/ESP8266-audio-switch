#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

#include "bootstrap_min_css_gz.h"

ESP8266WebServer Server;
AutoConnect Portal(Server);

String content;
int relay1 = D2;
int device_switch = 0;

void rootPage() {
  content = "<!DOCTYPE html>";
  content+= "<html lang='en'>";
  content+= "  <head>";
  content+= "    <meta charset='utf-8'>";
  content+= "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  content+= "    <meta name='viewport' content='width=device-width, initial-scale=1'>";
  content+= "    <title>Audio switch</title>";
  content+= "    <link rel='apple-touch-icon-precomposed' sizes='180x180' href='data:image/png;base64,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'>";
//  content+= "    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>";
  content+= "    <link rel='stylesheet' href='bootstrap.min.css'>";
  content+= "  </head>";
  content+= "  <body>";
  content+= "    <style>";
  content+= "      html, body {height: 100%;}";
  content+= "      .container {height: 100%;}";
  content+= "      body { padding: 5%;}";
  content+= "    </style>";
  content+= "    <div class='container'>";
//  content+= String(device_switch);
  content+= "      <!-- <div class='text-center'><h1>Audio switch</h1></div> -->";
  content+= "      <div class='row h-100'>";
  content+= "        <div class='col my-auto'>";
  content+= "          <form action='/switch' method='post'>";
  content+= "            <button name='device' value='tv' class='btn btn-block btn-lg ";
  if (device_switch == 0) {
    content+= "btn-primary";
  } else {
    content+= "btn-secondary";
  }
  content+= "'>";
  content+= "              TV";
  content+= "            </button>";
  content+= "            <br />";
  content+= "            <button name='device' value='airport' class='btn btn-block btn-lg ";
  if (device_switch == 1) {
    content+= "btn-primary";
  } else {
    content+= "btn-secondary";
  }
  content+= "'>";
  content+= "              AirPort";
  content+= "            </button>";
  content+= "          </form>";
  content+= "        </div>";
  content+= "      </div>";
  content+= "    </div>";
  content+= "  </body>";
  content+= "</html>";
  Server.send(200, "text/html", content);
}

void handleBootstrapRequest() {
  Server.sendHeader("Content-Encoding", "gzip");
  Server.setContentLength(CONTENT_LENGTH_UNKNOWN);                         // I don't like this part
  Server.send(200, "text/css", "");                                        // but it works!
  Server.sendContent_P(bootstrap_min_css_gz, bootstrap_min_css_gz_len);
}

void setup(void){
  // preparing GPIOs
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);
  delay(1000);
  Serial.begin(115200);
  Serial.println("");
  Server.on("/", rootPage);
  Server.on("/index.htm", rootPage);
  Server.on("/index.html", rootPage);
  Server.on("/switch", HTTP_POST, switchDevice);                    // Call the 'switchDevice' function when a POST request is made to URI "/switch"
  Server.on("/bootstrap.min.css", HTTP_GET, handleBootstrapRequest);
  Portal.begin();
  Serial.println("HTTP server:" + WiFi.localIP().toString());
}

void switchDevice() {                                               // If a POST request is made to URI /switch
  if (! Server.hasArg("device")) {                                  // If the POST request doesn't have device data
      Server.send(400, "text/plain", "400: Invalid Request");       // The request is invalid, so send HTTP status 400
      return;
  }
  if (Server.arg("device") == "tv") {
      digitalWrite(relay1, LOW);
      device_switch = 0;
  }
  if (Server.arg("device") == "airport") {
      digitalWrite(relay1, HIGH);
      device_switch = 1;   
  }
  Server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  Server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void loop(void){
  Portal.handleClient();
} 
