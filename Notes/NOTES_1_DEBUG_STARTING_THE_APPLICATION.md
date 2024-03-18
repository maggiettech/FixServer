# Notes 1: Debug Starting the Application

## Objective
Tracing how the application gets started behind the scenes

## Details
### SessionSettings
```
FIX::SessionSettings settings("/Users/maggietsui/CLionProjects/FixServer/config.cfg");
```
This creates a settings object, which reads from the configuration file and converts key value pairs into a dictionary for lookup
If there are any missing fields a ConfigError will be thrown

### FileStoreFactory

### ScreenLogFactory

### SocketAcceptor
We're creating a FIX Server here which will be accepting connections.

## Logs
### Server Side
```
# Client sends login message 35=A to server
8=FIX.4.2|9=69|35=A|34=2|49=CLIENT_A|52=20240317-14:46:43.000|56=SERVER|98=0|108=20|10=050

# Server sends logout message to client 35=5 complaning about 'Incorrect BeginString'
8=FIX.4.2|9=82|35=5|34=1|49=SERVER|52=20240317-14:46:43.000|56=CLIENT_A|58=Incorrect BeginString|10=216

# Client sends a logout message to server 35=5
8=FIX.4.2|9=57|35=5|34=3|49=CLIENT_A|52=20240317-14:46:43.000|56=SERVER|10=012
```


* server is complaining about 'Incorrect BeginString' from client