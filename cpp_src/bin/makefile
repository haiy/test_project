#pnm is the program name variable,this makefile is 
#suitable for a simple complie situation.
#change "cs" to whatever the file name you want to make
pnm=BankAccountFull

CC=g++
CFLAGS=-g -Wall
FILE_TYPE=cpp

$(pnm):$(pnm).o
	$(CC) $(pnm).o -o $(pnm)
$(pnm).o:$(pnm).$(FILE_TYPE)
	$(CC) -c $(pnm)"."$(FILE_TYPE)
clean:
	  rm *.o $(pnm) 
