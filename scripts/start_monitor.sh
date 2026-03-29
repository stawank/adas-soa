#!/bin/bash
cd /home/stawan/adas-soa/build

../scripts/start_all_providers.sh

mkdir -p ../reports
sleep 2

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
REPORT_FILE="reports/report_${TIMESTAMP}.txt"


VSOMEIP_CONFIGURATION=../config/monitor.json \
VSOMEIP_APPLICATION_NAME=ServiceMonitor \
./service_monitor > /tmp/monitor_report.txt 2>/tmp/vsomeip_logs.txt
cat /tmp/monitor_report.txt
cat /tmp/vsomeip_logs.txt

cp /tmp/monitor_report.txt ../reports/report_${TIMESTAMP}.txt
cp /tmp/vsomeip_logs.txt ../reports/report_vsomeip_logs_${TIMESTAMP}.txt