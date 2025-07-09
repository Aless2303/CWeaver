#!/bin/bash

run_script() {
    local filename=$1
    if [[ -f "$filename" ]]; then
        ./proiectulmeu < "$filename"  
    else
        echo "NU exista fisierul: '$filename' "
    fi
}


process_command() {
    local command=$1
    echo "$command" | ./proiectulmeu  
}


while true; do
    echo -n "> "
    read user_input

    if [[ "$user_input" == run* ]]; then
        script_file=$(echo "$user_input" | cut -d ' ' -f 2)
        run_script "$script_file"
    else
        process_command "$user_input"
    fi
done