echo "ready to compile ..."
rm *.class
javac -cp .:py4j-0.10.1.jar MySimpleServer.java MyStack.java
echo "begin to start gateserver..."
java -cp .:py4j-0.10.1.jar MySimpleServer
