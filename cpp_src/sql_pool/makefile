test:
	g++ -o test  mysql_pool.cpp test_main.cpp -I`mysql_config --cflags --libs` -I/usr/local/Cellar/boost/0.55.0_1/include -lboost_thread-mt -lboost_system -g -Wall 

clean:
	rm -rf test *.o

