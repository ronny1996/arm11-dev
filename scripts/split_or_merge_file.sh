#!/bin/bash

function splitFile() {
	split -b 50m $2 $3
	return 0
}

function mergeFiles() {
	cat $2* > $3
}

echo "README"
