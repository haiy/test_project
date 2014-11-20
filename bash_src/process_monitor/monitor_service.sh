#!/bin/bash
#author:haiy
# Fri Apr 25 13:04:48 CST 2014
#monitor and keep the program running
#用法：
# bash keep_running service_list 10m

DEBUG=false

function restart_program()
{
    if [  $# -lt 3 ];then
        echo $# parameters get!
        echo usage: bash restart_program session_name window_index_number command
        exit
    fi
    session=$1
    window=$2
    command=$3
    #echo "current session is $session.$window_num"
    screen -x -S $session -p $window -X stuff "$command"
}


function single_watch()
{
    if [  $# -lt 2 ];then
        echo $# parameters get!
        echo usage: bash single_watch program_name running_instance_number
        exit
    fi
    program_name=$1
    expected_number=$2
    real_number=$( ps aux | grep "$program_name"$ | grep -v grep | grep -v $0 | grep -v SCREEN | grep -v vim | wc -l )
    if [ ! $real_number = $expected_number ];then
        echo  false
    else
        echo true
    fi
}

function keep_running()
{
    #$1 is the service_list file with service name ,
    #screen session name and window index

    #$2 is the sleep duration
    service_list=$1
    sleep_time=$2

    while true; 
    do
        if [  $# -lt 2 ];then
            echo $# parameters get!
            echo usage: bash check_running_service list_file sleep_time
            exit
        fi

        #read the checked service list from the file
        while read line;
        do
            IFS=';' read -a content <<< "$line"
            session=$(echo "${content[0]}")
            window=$(echo "${content[1]}")
            program=$(echo "${content[2]}")
            if $DEBUG; then
                echo session,$session,
                echo window,$window,
                echo program,$program
            fi

            stat=$(single_watch "$program" 1)
            if [ $stat == "false" ];then
                echo "`date` Gonna restart $program..."
                restart_program $session $window "$program"
                echo "$program ." > mail_content
                #Here you can add the send mail module
                #python gmail_sender.py
            else
                echo "`date` ==> $line ==>Running normally."
            fi
        done < $service_list

        if $DEBUG;then
            exit
        fi

        echo "I'm gonna sleep a while,$2.."
        sleep $sleep_time
    done
}

if $DEBUG;then
    #Here the command should be quoted with double quotes
    restart_program 16902.watch_dog 3 "ls"
    #single_watch
    keep_running $1 $2
    #session_name=16902.watch_dog 
    #window_num=3
    #screen -x -S $session -p $window_num -X stuff $command
fi

if [  $# -lt 2 ];then
    echo usage: bash keep_running list_file sleep_time
    exit
fi

keep_running $1 $2
