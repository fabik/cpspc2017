#!/bin/bash

for input in test/*.in
do
	output=${input/in}out
	echo $input ": "
	(time ./sol < $input > $output) 2>&1 | grep user
done
