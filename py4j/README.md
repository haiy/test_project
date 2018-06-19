### example to use py4j


#### before start 

安装py4j和java，`pip install py4j`

#### let's begin

- 1 just use `start.sh` to start the server
- 2 open an python console,try to play with the server,

```python
 from py4j.java_gateway import JavaGateway

# build a bridge, what happend if kill the server now
 gw = JavaGateway()
 s = gw.entry_point.getStack()
 s.pop()

 s.push("hi")

# try to crash it
 s.pop()
 s.pop
```

example from official doc [here](https://www.py4j.org/getting_started.html#writing-the-java-program)
