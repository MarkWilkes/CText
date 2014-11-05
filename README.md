CText
=====

//set up the server side \n
1. open the CText-develop folder \n
2. open the ServerSide folder \n
3. open the 'cuTPSServer.pro' file \n
4. it will open the QT Creator, just click 'Configure Project' \n
5. Server is good \n

//set up the client test \n
1. open the CText-develop folder \n
2. open the ClientSideTest folder \n
3. open the 'cuTPSTestClient.pro' file \n
4. it will open the QT Creator, just click 'Configure Project' \n
5. Client is god \n

//Run the program
1. run the cuTPSServer on the QT \n
(NOTES: when you try to run this program, there maybe an error like <QApplication/...> Can't find. If so, go to the cuTPSServer.pro, fin the line 'QT   += gui' and then change the 'gui' to 'widgets') \n

2. run the cuTPSTestClient on the QT \n
(NOTES: when you try to run this program, there maybe an error like <QApplication/...> Can't find. If so, go to the cuTPSServer.pro, fin the line 'QT   += gui' and then change the 'gui' to 'widgets') \n

3. run the test case one by one, and then you can see the test case description/ expected value/ and returned value. \n

