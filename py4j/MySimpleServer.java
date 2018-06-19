import py4j.GatewayServer;

public class MySimpleServer{
    private MyStack stack;
    public MySimpleServer(){
        stack = new MyStack();
        stack.push("Initial Item");
    }
    public MyStack getStack(){
        return stack;
    }

    public static void main(String[] args) {
        GatewayServer gatewayServer = new GatewayServer(new MySimpleServer());
        gatewayServer.start();
        System.out.println("Gateway Server Started");
    }

}
