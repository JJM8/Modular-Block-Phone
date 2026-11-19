#!/bin/sh

echo "whats plugged in"
echo ""

n=0
while IFS=: read name slot on; do
	if [ "$on" = "1" ]; then
		echo "$name slot $slot yes"
		n=$((n+1))
	else
		echo "$name no"
	fi
done < /tmp/mbp_modules

echo ""
echo "$n modules on"
