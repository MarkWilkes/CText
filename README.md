CText
=====

//set up the server side  
1. open the CText-develop folder  
2. open the ServerSide folder  
3. open the 'cuTPSServer.pro' file  
4. it will open the QT Creator, just click 'Configure Project'  
5. Server is good  

//set up the client test  
1. open the CText-develop folder  
2. open the ClientSideTest folder  
3. open the 'cuTPSTestClient.pro' file  
4. it will open the QT Creator, just click 'Configure Project'  
5. Client is god  

//Run the program  
1. run the cuTPSServer on the QT  
(NOTES: when you try to run this program, there maybe an error like <QApplication/...> Can't find. If so, go to the cuTPSServer.pro, fin the line 'QT   += gui' and then change the 'gui' to 'widgets')  

2. run the cuTPSTestClient on the QT  
(NOTES: when you try to run this program, there maybe an error like <QApplication/...> Can't find. If so, go to the cuTPSServer.pro, fin the line 'QT   += gui' and then change the 'gui' to 'widgets')  

3. run the test case one by one, and then you can see the test case description/ expected value/ and returned value.  

