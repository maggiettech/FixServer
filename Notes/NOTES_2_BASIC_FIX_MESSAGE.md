# Notes 2: Basic FIX Message Structure

## Objective
Structure of a basic FIX message

## Details

FIX messages after starting up FIX server and FIX client.

###  Basic Login Message (35=A)
```
8=FIX.4.2|9=69|35=A|34=2|49=CLIENT_A|52=20240317-14:46:43.000|56=SERVER|98=0|108=20|10=050
```
| Tag | Field | Description
| --- | ----- | -----------
| 8   | BeginString   | mandatory tag at the beginning of a FIX message specifying the FIX protocol version
| 9   | BodyLength | message length in bytes
|35   | MsgType |
|34   | MsgSeqNum | 
|49   | SenderCompID |
|52   | SendingTime |
|56   | TargetCompID |
|98   | EncryptMethod |
|108  | HeartBtInt    |
|10   | CheckSum

![1_logon.png](screenshots%2F1_logon.png)

### Response from server
```
8=FIX.4.2|9=82|35=5|34=1|49=SERVER|52=20240317-14:46:43.000|56=CLIENT_A|58=Incorrect BeginString|10=216
```

| Tag | Field | Description
|-----|-------| -----------
| 58  | Text  | Incorrect BeginString

Server was complaining about Incorrect BeginString

### After fixing BeginString issue

* Client sends login message to server
* Server sends login message to client
* FIX connection is established
* However, looks like client login message has sequence number = 2, expected value should be 1

    ![2_logon_success.png](screenshots%2F2_logon_success.png)

    Reference: https://www.onixs.biz/fix-dictionary/4.3/msgtype_a_65.html

