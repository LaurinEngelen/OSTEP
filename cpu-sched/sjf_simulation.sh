#!/bin/bash

# Variablen
python_script="./scheduler.py"   # Pfad zum Python-Skript
max_jobs=5                       # Anzahl der Jobs
initial_maxlen=5                 # Startwert der Job-Länge
increment=5                      # Schrittweite, um die Job-Länge zu vergrößern
maxlen_limit=50                  # Obergrenze für die maximale Job-Länge
output_file="sjf_response_times.txt"  # Datei für die Ergebnisse

# Datei für Ergebnisse erstellen
echo "Job Length | Average Response Time" > $output_file

# Schleife, um die Job-Längen zu vergrößern
for (( maxlen=$initial_maxlen; maxlen<=$maxlen_limit; maxlen+=$increment ))
do
    echo "Running SJF with max job length = $maxlen"

    # Python-Skript mit SJF ausführen und Job-Länge variieren
    result=$(python3 $python_script -p SJF -j $max_jobs -m $maxlen -c)

    # Extrahiere die durchschnittliche Response Time aus der Ausgabe
    avg_response_time=$(echo "$result" | grep "Average -- Response" | awk '{print $4}')

    # Schreibe die Job-Länge und die durchschnittliche Response Time in die Datei
    echo "$maxlen | $avg_response_time" >> $output_file
done

echo "Ergebnisse wurden in $output_file gespeichert."